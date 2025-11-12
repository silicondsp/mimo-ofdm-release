 
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

interlr

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



 

#include <math.h>
#include <stdio.h>
#include "ftab_80211a.h"


 

#define NUMOFBITS   288


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int*   __interX;
       int*   __interY;
       int   __numBits;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  interX  (state_P->__interX)
#define  interY  (state_P->__interY)
#define  numBits  (state_P->__numBits)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*(( int   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define y(delay) *( int   *)POUT(0,delay)
/*-------------- BLOCK CODE ---------------*/
 int  
interlr
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

   int i;
   int Lp;


switch (run_state) {


 /********* PARAMETER INITIALIZATION CODE ************/
case PARAM_INIT:

        {
        int indexModel88 = block_P->model_index;

        KrnModelParam(indexModel88,-1,"","","","");
        }

break;
   
          
 
/*         
 *    OUTPUT BUFFER SYSTEM  INITS 
 */ 
 case OUTPUT_BUFFER_INIT: 
 {
 int indexOC = block_P->model_index;
     char   *ptypeOut0 = " int ";
     char   *pnameOut0 = " y ";
KrnModelConnectionOutput(indexOC,0 ,pnameOut0,ptypeOut0);
}
 break;

/*         
 *    INPUT BUFFER SYSTEM  INITS 
 */ 
 case INPUT_BUFFER_INIT:
 {
 int indexIC = block_P->model_index;
     char   *ptypeIn0 = " int ";
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
             numBits = 0 ;



         
   if(NO_OUTPUT_BUFFERS() != 1 ){
       fprintf(stdout,"%s:1 outputs expected; %d connected\n",
              STAR_NAME,NO_OUTPUT_BUFFERS());
	      return(201);
   }

   SET_CELL_SIZE_OUT(0,sizeof( int ));

         
   if(NO_INPUT_BUFFERS() != 1 ){
       fprintf(stdout,"%s:1 inputs expected; %d connected\n",
              STAR_NAME,NO_INPUT_BUFFERS());
	      return(200);
   }

   SET_CELL_SIZE_IN(0,sizeof( int ));

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

 /* allocate memory and return pointers for internal states bx */
 if((interX = (int*)calloc(NUMOFBITS,sizeof(int))) == NULL ||
   (interY = (int*)calloc(NUMOFBITS,sizeof(int))) == NULL) {
   fprintf(stderr,"interleaver: can't allocate work space\n");
   return(4);
   }


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 


 while(IT_IN(0))
    {
      interX[numBits] = x(0);
      numBits++;                   /* read all 288 bits into internal buffer */

       if (numBits == NUMOFBITS){

        numBits = 0;
        for (i=0;i<NUMOFBITS;i++)
          {
            Lp = interlrIndexTable[i];
            interY[Lp] = interX[i];
          }

        for (i=0;i<NUMOFBITS;i++)
           {
             if(IT_OUT(0)){
	          KrnOverflow("interleaver",0);
	          return(99);
	          }
	  //    printf("interleaver   %d  %d\n",i,  interY[i]);
	     y(0) = interY[i];
	    }
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
