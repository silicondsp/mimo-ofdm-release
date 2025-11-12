 
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

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



 

#include "fftdef.h"



/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int   __count;
       float*   __real_P;
       float*   __imag_P;
       float*   __realOut_P;
       float*   __imagOut_P;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  count  (state_P->__count)
#define  real_P  (state_P->__real_P)
#define  imag_P  (state_P->__imag_P)
#define  realOut_P  (state_P->__realOut_P)
#define  imagOut_P  (state_P->__imagOut_P)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define X(DELAY) (*(( complex   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define Y(delay) *( complex   *)POUT(0,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define fftLength (param_P[0]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
fwfft
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

   	int i,k;
   	complex sample;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " FFT Length ";
     char   *ptype0 = "int";
     char   *pval0 = "64";
     char   *pname0 = "fftLength";
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
     char   *pnameOut0 = " Y ";
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
     char   *pnameIn0 = " X ";
KrnModelConnectionInput(indexIC,0 ,pnameIn0,ptypeIn0);
}
 break;

/*
 *        SYSTEM INITIALIZATION CODE 
 */
case SYSTEM_INIT:
     
	star_P->state_P = (char*)calloc(1,sizeof(state_t));
	state_P = (state_Pt)star_P->state_P;
             count = 0 ;



         
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

 

  SET_CELL_SIZE_IN (0, sizeof(complex));
  SET_CELL_SIZE_OUT (0, sizeof(complex));
real_P=(float*)calloc(fftLength,sizeof(float));
if(!real_P) {
    fprintf(stderr,"fwfft:Could not allocate space\n");
	return(2);
}
imag_P=(float*)calloc(fftLength,sizeof(float));
if(!imag_P) {
    fprintf(stderr,"fwfft:Could not allocate space\n");
	return(2);
}
realOut_P=(float*)calloc(fftLength,sizeof(float));
if(!realOut_P) {
    fprintf(stderr,"fwfft:Could not allocate space\n");
	return(2);
}
imagOut_P=(float*)calloc(fftLength,sizeof(float));
if(!imagOut_P) {
    fprintf(stderr,"fwfft:Could not allocate space\n");
	return(2);
}


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 


for(i = MIN_AVAIL(); i>0; i--) {

	   IT_IN(0);
       sample = INCX(0,0);
	   real_P[count]=sample.re;
	   imag_P[count]=sample.im;

	   count++;
       if(count == fftLength) {

           count = 0; 
           fft2s(real_P,imag_P,realOut_P,imagOut_P,fftLength,1);

		   for(k=0; k<fftLength; k++) {
  
		   	   /*
			    * ready output buffer for sample
			    * check for overflow
			    */
			   if(IT_OUT(0)) {
					KrnOverflow("fwfft",0);
					return(99);
			   }

			   /*
			    * output the sample
			    */
			   sample.re=realOut_P[k];
			   sample.im=imagOut_P[k];
			   OUTCX(0,0) = sample;
			}

	   }

}


break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 

  free(real_P);
  free(imag_P);
  free(realOut_P);
  free(imagOut_P);


break;
}
return(0);
}
