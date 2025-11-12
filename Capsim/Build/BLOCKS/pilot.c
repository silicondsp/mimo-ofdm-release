 
#ifdef LICENSE



/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 2002-2017   Silicon DSP  Corporation

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    http://www.silicondsp.com
*/


#endif
 
#ifdef SHORT_DESCRIPTION

pilot

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



 

#include "typedef.h"
#include "anisim.h"
#include "ftab_80211a.h"


 

#define N 64
#define M54 216
#define Sym 48


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       complex*   __xi;
       complex*   __yi;
       int   __pointCount;
       int   __pilotIndex;
       int   __numberOfSym;
       int   __numberOfSam;
       int   __cntOfSym;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  xi  (state_P->__xi)
#define  yi  (state_P->__yi)
#define  pointCount  (state_P->__pointCount)
#define  pilotIndex  (state_P->__pilotIndex)
#define  numberOfSym  (state_P->__numberOfSym)
#define  numberOfSam  (state_P->__numberOfSam)
#define  cntOfSym  (state_P->__cntOfSym)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*(( complex   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define yout(delay) *( complex   *)POUT(0,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define numOfBits (param_P[0]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
pilot
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

 int i,j=0,k;
 int no_samples;
 int index;
 complex  xx, tem;
 double tmp;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " number of input bits per packet ";
     char   *ptype0 = "int";
     char   *pval0 = "0";
     char   *pname0 = "numOfBits";
KrnModelParam(indexModel88,0 ,pdef0,ptype0,pval0,pname0);

      }
break;
   


/*         
 *    OUTPUT BUFFER SYSTEM  INITS 
 */ 
 case OUTPUT_BUFFER_INIT: 
 {
 int indexOC = block_P->model_index;
     char   *ptypeOut0 = " complex ";
     char   *pnameOut0 = " yout ";
KrnModelConnectionOutput(indexOC,0 ,pnameOut0,ptypeOut0);
}
 break;

/*         
 *    INPUT BUFFER SYSTEM  INITS 
 */ 
 case INPUT_BUFFER_INIT:
 {
 int indexIC = block_P->model_index;
     char   *ptypeIn0 = " complex ";
     char   *pnameIn0 = " x ";
KrnModelConnectionInput(indexIC,0 ,pnameIn0,ptypeIn0);
}
 break;

/*
 *        SYSTEM INITIALIZATION CODE 
 */
case SYSTEM_INIT:
     
	star_P->state_P = (char*)calloc(1,sizeof(state_t));
	state_P = (state_Pt)star_P->state_P;
             pointCount = 0 ;
        pilotIndex = 1 ;
        cntOfSym = 0 ;



         
   if(NO_OUTPUT_BUFFERS() != 1 ){
       fprintf(stdout,"%s:1 outputs expected; %d connected\n",
              STAR_NAME,NO_OUTPUT_BUFFERS());
	      return(201);
   }

   SET_CELL_SIZE_OUT(0,sizeof( complex ));

         
   if(NO_INPUT_BUFFERS() != 1 ){
       fprintf(stdout,"%s:1 inputs expected; %d connected\n",
              STAR_NAME,NO_INPUT_BUFFERS());
	      return(200);
   }

   SET_CELL_SIZE_IN(0,sizeof( complex ));

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

    tmp = (double) (16 + numOfBits + 6)/M54;
    numberOfSym = (int) ceil(tmp);                   // number of data symbols
    numberOfSam= numberOfSym * Sym;                   // number of data symbols
 /* allocate memory and return pointers for internal states xi and yi */
 if((xi = (complex*)calloc(N,sizeof(complex))) == NULL ||
   (yi = (complex*)calloc(N,sizeof(complex))) == NULL) {
   fprintf(stderr,"pilot: can't allocate work space\n");
   return(4);
   }
  /* initialize the internal states to be zeros  */
    SET_CELL_SIZE_IN(0,sizeof(complex));
    SET_CELL_SIZE_OUT(0,sizeof(complex));


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 


 for (no_samples = MIN_AVAIL();no_samples>0; --no_samples)
  {
         IT_IN(0);
         index = pilotMapping[pointCount];
         xx.re = x(0).re;
         xx.im = x(0).im;
         xi[index] = xx;
         pointCount++;             /* read in all input into internal buffer */
		 cntOfSym++;               // count all symbols and then set pilot index zero

  /* once 48 complex samples have been read in, process them */

    if ( pointCount == 48){

      pointCount = 0;

      xi[5].re = 1.0;              /* insert pilot   */
      xi[5].im = 0.0;
      xi[19].re = 1.0;
      xi[19].im = 0.0;
      xi[32].re = 1.0;
      xi[32].im = 0.0;
      xi[46].re = -1.0;
      xi[46].im = 0.0;

     /* adding zeros  */

     for (i=0; i<6; i++)
       {
         yi[i].re = 0.0;
         yi[i].im = 0.0;
       }

     for (i=0; i<26; i++)
      {
         yi[i+6].re = xi[i].re;
         yi[i+6].im = xi[i].im;
       }

       yi[32].re = 0.0;
       yi[32].im = 0.0;

     for(i=26; i<52; i++)
       {
         yi[i+7].re = xi[i].re;
         yi[i+7].im = xi[i].im;
       }

     for(i=0;i<5;i++)
       {
         yi[i+59].re = 0.0;
         yi[i+59].im = 0.0;
       }


	/* need to swap first -26 to -1 with last 1 to 26  in order to come up with
           input to IFFT   */


          Swap(yi,32);

    //      for(i=0; i<N;i++)
    //       {
    //        printf("pilotInput %d %f %f\n",i, yi[i].re,yi[i].im);
    //       }
	
	/*  add polarity control for pilot subcarriers   */

            Polarity(yi, pilotIndex);

            pilotIndex++;

            if (pilotIndex == 127)
             {
               pilotIndex = 0;
             }

	
	  for (i=0;i<N;i++)
	    {
	       if(IT_OUT(0)){
	          KrnOverflow("pilot",0);
	          return(99);
	       }
	
	       tem.re = yi[i].re;
	       tem.im = yi[i].im;
	       yi[i].re = 0.0;          /* yi[i] needs to be cleared  */
	       yi[i].im = 0.0;
	//        printf("pilot   %d  %f  %f\n",i,tem.re,tem.im );
	       yout(0) = tem;
	     }
       }

	   if(cntOfSym == numberOfSam)      // for multi-packet usage
	    {
		  cntOfSym = 0;
		  pilotIndex = 0;
	//	  fprintf(stderr,"%d \n",pilotIndex); 
         }
   }	
	
	







break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 



break;
}
return(0);
}
