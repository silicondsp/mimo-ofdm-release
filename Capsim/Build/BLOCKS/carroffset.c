 
#ifdef LICENSE


/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 2001-2017   Silicon DSP  Corporation

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

Adds carrier offset to complex input stream.

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>


 

#define PI 3.1415926535898


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int   __numOutBuffers;
       int   __k;
       double   __angle;
       float   __delta;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  numOutBuffers  (state_P->__numOutBuffers)
#define  k  (state_P->__k)
#define  angle  (state_P->__angle)
#define  delta  (state_P->__delta)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*(( complex   *)PIN(0,DELAY)))

/*         
 *    PARAMETER DEFINES 
 */ 
#define offset (param_P[0]->value.f)
#define fs (param_P[1]->value.f)
/*-------------- BLOCK CODE ---------------*/
 int  
carroffset
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

	int numberOfSamples;
	int i;
	complex val;
	complex calc;
        float sinang;
        float cosang;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " Carrier offset ";
     char   *ptype0 = "float";
     char   *pval0 = "0.0";
     char   *pname0 = "offset";
     char   *pdef1 = " Sampling Rate ";
     char   *ptype1 = "float";
     char   *pval1 = "20000000";
     char   *pname1 = "fs";
KrnModelParam(indexModel88,0 ,pdef0,ptype0,pval0,pname0);
KrnModelParam(indexModel88,1 ,pdef1,ptype1,pval1,pname1);

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
             k = 0 ;
        angle = 0 ;


         
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

 

        delta=PI*2*offset/fs;
	/* note and store the number of output buffers */
	if((numOutBuffers = NO_OUTPUT_BUFFERS() ) <= 0) {
		fprintf(stdout,"node: no output buffers\n");
		return(1); /* no output buffers */
	}
	SET_CELL_SIZE_IN(0,sizeof(complex));
	for (i=0; i<numOutBuffers; i++)
		SET_CELL_SIZE_OUT(i,sizeof(complex));


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 


	for(numberOfSamples=MIN_AVAIL();numberOfSamples >0; --numberOfSamples) {
		IT_IN(0);
		for(i=0;i<numOutBuffers;++i) {
			if(IT_OUT(i)) {
				KrnOverflow("carroffset",i);
				return(99);
			}
			val=x(0);

                        angle=fmod(angle+delta,PI*2);
                        cosang=cos(angle);
                        sinang= -sin(angle);
                        calc.re= val.re*cosang-val.im*sinang;

			calc.im = val.re*sinang+val.im*cosang;
			OUTCX(i,0) = calc;
		}
	}

    	return(0);  /* input buffer empty */



break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 



break;
}
return(0);
}
