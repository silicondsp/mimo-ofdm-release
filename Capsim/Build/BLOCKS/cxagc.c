 
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



/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       float   __gain;
       int   __count;
       int   __totalCount;
       float   __sum;
       int   __freezeAGC;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  gain  (state_P->__gain)
#define  count  (state_P->__count)
#define  totalCount  (state_P->__totalCount)
#define  sum  (state_P->__sum)
#define  freezeAGC  (state_P->__freezeAGC)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*(( complex   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define y(delay) *( complex   *)POUT(0,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define targetRMS (param_P[0]->value.f)
#define skip (param_P[1]->value.d)
#define agcWindowSize (param_P[2]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
cxagc
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

	int i,j;
	float xSample;	/* current sample of input signal	*/
	float xr,xi;
	float mag,rmsVal;
	complex val;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " Target rms ";
     char   *ptype0 = "float";
     char   *pval0 = "0.08";
     char   *pname0 = "targetRMS";
     char   *pdef1 = " Points to skip ";
     char   *ptype1 = "int";
     char   *pval1 = "0";
     char   *pname1 = "skip";
     char   *pdef2 = " Window size ";
     char   *ptype2 = "int";
     char   *pval2 = "32";
     char   *pname2 = "agcWindowSize";
KrnModelParam(indexModel88,0 ,pdef0,ptype0,pval0,pname0);
KrnModelParam(indexModel88,1 ,pdef1,ptype1,pval1,pname1);
KrnModelParam(indexModel88,2 ,pdef2,ptype2,pval2,pname2);

      }
break;
   


/*         
 *    OUTPUT BUFFER SYSTEM  INITS 
 */ 
 case OUTPUT_BUFFER_INIT: 
 {
 int indexOC = block_P->model_index;
     char   *ptypeOut0 = " complex ";
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
             gain = 1.0 ;
        count = 0 ;
        totalCount = 0 ;
        sum = 0.0 ;
        freezeAGC = 0 ;



         
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

 
         gain=1.0;
         freezeAGC=0;
	 count=0;
	 totalCount=0;

break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 


	/* note the minimum number of samples on the input 	*/
	/* buffers and iterate that many times 			*/
	for(i=MIN_AVAIL();i>0; --i) {
    	     IT_IN(0);
	  
			if(IT_OUT(0)) {
				KrnOverflow("cxagc",0);
				return(99);
			}
			val=x(0);
			val.re= val.re*gain;
			val.im= val.im*gain;
			y(0) = val;
	     if(freezeAGC==0) {
//              printf("x=%f+j%f\n",x(0).re,x(0).im);
	        if(++totalCount > skip) {

			if (count<agcWindowSize){
				count++;
				xr = x(0).re;		

				xi = x(0).im;		
                                sum +=  xr*xr+xi*xi;
				

	      	        }

			if (count==agcWindowSize){
			        rmsVal=sqrt(sum/(float)agcWindowSize);
				gain=targetRMS/rmsVal;
				printf("cxagc rmsVal=%f gain=%f \n",rmsVal, gain);
				freezeAGC=1;
			
			
			}

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
