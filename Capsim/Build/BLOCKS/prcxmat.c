 
#ifdef LICENSE


/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 2006-2017   Silicon DSP  Corporation

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

Print the complex matrix samples.

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



 

#include <tcl.h>
//#include <vectors.h>
#include "matrixBuffers.h"
#include "mimo.h"




/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int   __numberInputBuffers;
       int   __numberOutputBuffers;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  numberInputBuffers  (state_P->__numberInputBuffers)
#define  numberOutputBuffers  (state_P->__numberOutputBuffers)

/*         
 *    PARAMETER DEFINES 
 */ 
#define printControl (param_P[0]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
prcxmat
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

	int i,j,k;
	int ii,jj;
	float fpixel;
	dsp_cxMatrix_t cxmat;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " Print Control (0=off, 1=on) ";
     char   *ptype0 = "int";
     char   *pval0 = "1";
     char   *pname0 = "printControl";
KrnModelParam(indexModel88,0 ,pdef0,ptype0,pval0,pname0);

      }
break;
   


/*
 *        SYSTEM INITIALIZATION CODE 
 */
case SYSTEM_INIT:
     
	star_P->state_P = (char*)calloc(1,sizeof(state_t));
	state_P = (state_Pt)star_P->state_P;
     
break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

   /*
    * Get the number of input buffers.
    * return if none connected with an error
    */
   if((numberInputBuffers = NO_INPUT_BUFFERS()) <= 0) {
	   fprintf(stderr,"prcxmat: no input buffers\n");
	   return(1);
   }
   /*
    * Get the number of output buffers.
    * return if greater then number of input buffers with an error
    */
   if((numberOutputBuffers = NO_OUTPUT_BUFFERS()) > numberInputBuffers) {
	  fprintf(stderr,"prcxmat: more output than input buffers\n");
	  return(2);
   }
   /*
    * set buffer sizes to dsp_cxMatrix_t
    */
   for(i=0; i< numberInputBuffers; i++)
			SET_CELL_SIZE_IN(i,sizeof(dsp_cxMatrix_t));
   for(i=0; i< numberOutputBuffers; i++)
			SET_CELL_SIZE_OUT(0,sizeof(dsp_cxMatrix_t));


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 

	
	/* 
	 * This mode synchronizes all input buffers 
	 */
	for(i = MIN_AVAIL(); i>0; i--) {
		for(j=0; j<numberInputBuffers; ++j) {
		
		    /*
		     * point to input sample
		     */
			IT_IN(j);
			
			if(j < numberOutputBuffers) {
			    /*
			     * just send samples from input to output buffers
			     */
				if(IT_OUT(j)) {
					KrnOverflow("prcxmat",j);
					return(99);
				}
                            cxmat=INCXMAT(j,0);
			    OUTCXMAT(j,0) = cxmat;

			}
			
			cxmat=INCXMAT(j,0);
                        Krn_PrintCxMatrix(&cxmat,"f", stdout);
       		 


		}
		    
	}


    return(0);



break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 



break;
}
return(0);
}
