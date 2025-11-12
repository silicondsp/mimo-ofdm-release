 
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

Add short description here. Will appear in HTML documentation.

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



#define STATE_BUFFER_ESTIMATES 0
#define STATE_EQUALIZE 1
#define NPTS_FFT 64


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int   __count;
       complex*   __chEst_P;
       int   __theState;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  count  (state_P->__count)
#define  chEst_P  (state_P->__chEst_P)
#define  theState  (state_P->__theState)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define channEstimates(DELAY) (*(( complex   *)PIN(0,DELAY)))
#define symbols(DELAY) (*(( complex   *)PIN(1,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define equalized(delay) *( complex   *)POUT(0,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define numberOfCarriers (param_P[0]->value.d)
#define doEqualization (param_P[1]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
cxequalizezf
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

   	int i;
   	complex sample;
	complex x,y;
	complex z;
        double tmp;
	float sgn;
        int long_A[NPTS_FFT]={0,1,-1,-1,1,1,-1,1,-1,1,-1,-1,-1,-1,-1,1,1,-1,-1,1,-1,1,-1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,1}; 

switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " Number of Carriers ";
     char   *ptype0 = "int";
     char   *pval0 = "64";
     char   *pname0 = "numberOfCarriers";
     char   *pdef1 = " Do Equalization (1:yes 0:no) ";
     char   *ptype1 = "int";
     char   *pval1 = "1";
     char   *pname1 = "doEqualization";
KrnModelParam(indexModel88,0 ,pdef0,ptype0,pval0,pname0);
KrnModelParam(indexModel88,1 ,pdef1,ptype1,pval1,pname1);

      }
break;
   


/*         
 *    OUTPUT BUFFER SYSTEM  INITS 
 */ 
 case OUTPUT_BUFFER_INIT: 
 {
 int indexOC = block_P->model_index;
     char   *ptypeOut0 = " complex ";
     char   *pnameOut0 = " equalized ";
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
     char   *pnameIn0 = " channEstimates ";
     char   *ptypeIn1 = " complex ";
     char   *pnameIn1 = " symbols ";
KrnModelConnectionInput(indexIC,0 ,pnameIn0,ptypeIn0);
KrnModelConnectionInput(indexIC,1 ,pnameIn1,ptypeIn1);
}
 break;

/*
 *        SYSTEM INITIALIZATION CODE 
 */
case SYSTEM_INIT:
     
	star_P->state_P = (char*)calloc(1,sizeof(state_t));
	state_P = (state_Pt)star_P->state_P;
             count = 0 ;
        chEst_P = 0 ;
        theState = 0 ;



         
   if(NO_OUTPUT_BUFFERS() != 1 ){
       fprintf(stdout,"%s:1 outputs expected; %d connected\n",
              STAR_NAME,NO_OUTPUT_BUFFERS());
	      return(201);
   }

   SET_CELL_SIZE_OUT(0,sizeof( complex ));

         
   if(NO_INPUT_BUFFERS() != 2 ){
       fprintf(stdout,"%s:2 inputs expected; %d connected\n",
              STAR_NAME,NO_INPUT_BUFFERS());
	      return(200);
   }

   SET_CELL_SIZE_IN(0,sizeof( complex ));

   SET_CELL_SIZE_IN(1,sizeof( complex ));

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

chEst_P=(complex*)calloc(numberOfCarriers,sizeof(complex));
if(chEst_P == NULL) {
       fprintf(stderr,"%s could not allocate\n",STAR_NAME);
       return(2);
}
theState=STATE_BUFFER_ESTIMATES;

break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 



if(theState == STATE_BUFFER_ESTIMATES ) {
  while(IT_IN(0)) {
       sample=channEstimates(0);
       chEst_P[count]=sample;
       count++;
       if(count == numberOfCarriers) {
           count=0;
           theState= STATE_EQUALIZE;
	   
	   /*
	    * invert channel
	    */
	   x.re=1.0;
	   x.im=0.0;
	   for(i=0; i<numberOfCarriers; i++) {

               
	       y=chEst_P[i];
               tmp = y.re * y.re + y.im * y.im;
//	       sgn=(mod(i,2))*2-1;   
               sgn=1;
               if (tmp == 0.0) {
                    printf("error, divide by 0.0 in cdiv\n");
                    z.re = 1.0e10 ;
                    z.im = 1.0e10 ;
               }
               else {
	            tmp=1.0/tmp;
                    z.re = ( y.re    ) * tmp*long_A[i]*sgn;
                    z.im = (  -   y.im) * tmp*long_A[i]*sgn;
               }
	       chEst_P[i]=z;
	       // printf("%d\t%f\t%f \n",i,z.re,z.im);
	       if(i==0 || (i>26 && i< 38) ) {
	                chEst_P[i].re=0;
			chEst_P[i].im=0;
	       }
	       
	      	//chEst_P[i].re=1.0;
		 //chEst_P[i].im=i;

	   }
	   
       }

  }
  
}  
if(theState == STATE_EQUALIZE ) { 

  while(IT_IN(1)) {
     x=symbols(0);
     y=chEst_P[count];
     
     count++;
//     count=mod(count,numberOfCarriers);
     count=count%numberOfCarriers;
     if(doEqualization) {
          z.re= x.re*y.re-x.im*y.im;
          z.im= x.re*y.im+x.im*y.re;
     } else {
          z=x;
     }
 
  	   /*
	    * ready output buffer for sample
	    * check for overflow
	    */
	   if(IT_OUT(0)) {
				KrnOverflow("cxequalizezf",0);
				return(99);
	   }                 
	   /*
	    * output the sample
	    */
	   equalized(0)=z; 
   }
}    


break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 
   free(chEst_P);

break;
}
return(0);
}
