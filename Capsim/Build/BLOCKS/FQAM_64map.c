 
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

 Floating point 802.11a 64-QAM mapping function

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



 

#include <math.h>
#include "ftab_80211a.h"


 

#define  NBITS 288
#define  NSIZE 48


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int   __numberBits;
       int*   __qaminput;
       complex*   __qam;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  numberBits  (state_P->__numberBits)
#define  qaminput  (state_P->__qaminput)
#define  qam  (state_P->__qam)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*(( int   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define output(delay) *( complex   *)POUT(0,delay)
/*-------------- BLOCK CODE ---------------*/
 int  
FQAM_64map
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

  int tableIndex,i,j;
  float  real, imag;
  complex cl;


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
     char   *ptypeOut0 = " complex ";
     char   *pnameOut0 = " output ";
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

   SET_CELL_SIZE_IN(0,sizeof( int ));

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

   if((qaminput = (int*)calloc(NBITS,sizeof(int))) == NULL ||
       (qam = (complex*)calloc(NSIZE,sizeof(complex))) == NULL) {
   fprintf(stderr,"QAM: can't allocate work space\n");
   return(4);
   }
   numberBits = 0;
   SET_CELL_SIZE_OUT(0,sizeof(complex));


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 


 while(IT_IN(0))
    {
       qaminput[numberBits] = x(0);
       numberBits++;
       if (numberBits == NBITS)
         {
           numberBits = 0;
           j = 0;
           for (i=0; i<NBITS; i+=6)
             {
               tableIndex = qaminput[i]+2*qaminput[i+1]+4*qaminput[i+2]+8*qaminput[i+3]+16*qaminput[i+4]+32*qaminput[i+5];
        //       printf("QAM   %d\n", tableIndex);
               real = QAM_64MAPTable[0][tableIndex];
               imag = QAM_64MAPTable[1][tableIndex];
               qam[j].re = real;
               qam[j].im = imag;
               j++;
             }

          for (i=0; i<NSIZE; i++)
           {
           if (IT_OUT(0))
            {
              KrnOverflow("FQAM_64map", 0);
              return(99);
            }

           cl.re = qam[i].re;
           cl.im = qam[i].im;
  //          printf("QAM   %f  %f\n", cl.re,cl.im);
           output(0) = cl;

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
