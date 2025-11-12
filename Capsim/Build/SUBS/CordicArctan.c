/**************************************************************************************************
 *                                                                                                *
 *   Cordic Arctangent                                                                            *
 *                                                                                                *
 **************************************************************************************************
 *                                               *                                                *
 *     File name:    CordicArctan.c              *                                                *
 *     Programmers:  R.Maslennikov, A.Khoryaev   *                                                *
 *     Date:         October 5, 2003             *                                                *
 *                                               *                                                *
 **************************************************************************************************/


#include "CordicArctan.h"
#include <math.h>


/**************************************************************************************************
 *     CORDIC ARCTANGENT                                                                          *       
 **************************************************************************************************/


INT32S CordicArctan(INT32S x,
	                INT32S y, INT32S *r_P)

{
    INT16S i;
    INT32S thetha;
    INT32S xInt, yInt, xTemp;        /* Internal and temporary variables */
    INT32S pi;
    INT32S arctan_A[NUMBER_ITER];



    /*
     * Clipping
     */
    if (x == -32768)
        x = -32767;

    if (y == -32768)
        y = -32767;

   /*
    * Force inputs to INPUT_WL bits
    */
    x <<= (32 - INPUT_WL);         
    x >>= (32 - INPUT_WL);
    y <<= (32 - INPUT_WL);
    y >>= (32 - INPUT_WL);


   /*
    * Generate Arctan Table
    */
	ArctanTable(arctan_A);         /* Generate arctangent table */
	pi  = 1 << (ANG_WL - 1);       /* Integer PI     */
	thetha = 0;                    /* set angle to zero */
	
    
   /*
    * Preprocessor
    */

    if (x < 0) {
        if (y > 0) {        /* if x > 0 and y >0 rotate by PI CW and add PI to thetha */
            x = -x;
            y = -y;
            thetha += pi;
        } else {            /* if x > 0 and y <= 0 rotate by PI CCW and subtract PI from thetha */
            x = -x;
            y = -y;
            thetha -= pi;
        }
    }


    xInt = x << G_LSB;    	/* Extend variables by introducing G_LSB guard bits  */
    yInt = y << G_LSB;      /* 2 MSB guard bits are required for x               */
                            /* and no MSB guard bits are required for y          */


   /*
    * Main CORDIC cycle
    */
    for (i = 0; i < NUMBER_ITER; i++) {
		if (yInt >= 0) {
			xTemp   = xInt + (yInt >> i); 
			yInt    = yInt - (xInt >> i); 
			xInt    = xTemp;
			thetha += arctan_A[i];
		} else {
			xTemp   = xInt - (yInt >> i); 
			yInt    = yInt + (xInt >> i); 
			xInt    = xTemp;
			thetha -= arctan_A[i];
		}
	}
    	
    *r_P=xInt;
    return thetha;
}
			
			
/**************************************************************************************************
 *     ARCTANGENT TABLE GENERATION                                                                *       
 **************************************************************************************************/


void ArctanTable(INT32S *atI_P)
{
    INT16S i;
    FP64   fTemp,iTemp;
    FP64   atF_A[NUMBER_ITER];           /* float-point atan table */
    
    	
	for (i = 0; i < NUMBER_ITER; i++) {
		atF_A[i] = atan(ldexp(1., -i));
		atF_A[i] = ldexp(atF_A[i] / PI, ANG_WL - 1);
		fTemp = modf(atF_A[i], &iTemp);                  /*  rounding  */
		modf(atF_A[i] + fTemp, atF_A + i);
		atI_P[i] = (INT32S)atF_A[i];
	}


}
	    
