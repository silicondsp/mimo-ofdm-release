/**************************************************************************************************
 *                                                                                                *
 *   Rotational Cordic with 16-bit Input & 17-bit Output precision                                *
 *                                                                                                *
 *                                                                                                *
 **************************************************************************************************
 *                                               *                                                *
 *     File name:    CordicRotate16.h            *                                                *
 *     Programmers:  R.Maslennikov, A.Khoryaev   *                                                *
 *	   Date:         September 15, 2003      *                                                *
 *												  *
 **************************************************************************************************/
#include <stdio.h>
#include "CordicRotate.h"

void CordicRotate(INT32S *x_P,
                  INT32S *y_P,
                  INT32S thetha)
{
    INT16S i;
    INT32S xInt,yInt,xTemp;   /* Internal and temporary variables */
    INT32S arctan_A[NUMBER_ITER] = {32768, 19344, 10221, 5188,
                                     2604,  1303,   652,  326,
                                      163,    81,    41,   20,
                                       10,     5};
	
   /*
    *        Clipping 
    */ 
    *x_P = (*x_P == -32768)?-32767:*x_P;
    *y_P = (*y_P == -32768)?-32767:*y_P;

   /*
    *        Preprocessor 
    */
    if (thetha >=  PI_2) {            /* if thetha > PI/2 rotate by PI CW */
		*x_P = - (*x_P);
		*y_P = - (*y_P);
    } else if (thetha < -PI_2) {      /* if thetha < -PI/2 rotate by PI CCW */
		*x_P = - (*x_P);
		*y_P = - (*y_P);
	}

    thetha = (thetha << 15)>>15;      /* bring angle to [-pi/2 pi/2) */


	xInt = ((INT32S)(*x_P)) << 3;    	/* Extend variables to 21-bit wordlength by introducing */
	yInt = ((INT32S)(*y_P)) << 3;       /* 2 MSB guard bit and 3 LSB guard bits                 */


   /*
    *  Main CORDIC cycle 
    */
	for (i = 0; i < NUMBER_ITER; i++) { 
		if (thetha < 0) {
			xTemp = xInt + (yInt >> i);
			yInt  = yInt - (xInt >> i);
			xInt  = xTemp;
			thetha += arctan_A[i];

		} else {
			xTemp = xInt - (yInt >> i); 
			yInt  = yInt + (xInt >> i); 
			xInt  = xTemp;
			thetha -= arctan_A[i];
		}
	}

	
	*x_P = (INT32S) ((xInt >> 4) + ((xInt & ROUND_MASK) >> 3));    /* bring back to 16-bit    */
	*y_P = (INT32S) ((yInt >> 4) + ((yInt & ROUND_MASK) >> 3));    /* wordlength by rounding */

}
