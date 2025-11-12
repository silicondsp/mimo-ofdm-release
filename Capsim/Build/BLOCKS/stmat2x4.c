 
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

Convert two streams to 4 streams using orthogonal steering matrix 

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int   __stateVariable;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  stateVariable  (state_P->__stateVariable)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x1(DELAY) (*(( complex   *)PIN(0,DELAY)))
#define x2(DELAY) (*(( complex   *)PIN(1,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define y1(delay) *( complex   *)POUT(0,delay)
#define y2(delay) *( complex   *)POUT(1,delay)
#define y3(delay) *( complex   *)POUT(2,delay)
#define y4(delay) *( complex   *)POUT(3,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define thisSampleParameter (param_P[0]->value.f)
/*-------------- BLOCK CODE ---------------*/
 int  
stmat2x4
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
        complex xs1,xs2;
        int k;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " Sample Parameter Definition ";
     char   *ptype0 = "float";
     char   *pval0 = "1999.99";
     char   *pname0 = "thisSampleParameter";
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
     char   *pnameOut0 = " y1 ";
     char   *ptypeOut1 = " complex ";
     char   *pnameOut1 = " y2 ";
     char   *ptypeOut2 = " complex ";
     char   *pnameOut2 = " y3 ";
     char   *ptypeOut3 = " complex ";
     char   *pnameOut3 = " y4 ";
KrnModelConnectionOutput(indexOC,0 ,pnameOut0,ptypeOut0);
KrnModelConnectionOutput(indexOC,1 ,pnameOut1,ptypeOut1);
KrnModelConnectionOutput(indexOC,2 ,pnameOut2,ptypeOut2);
KrnModelConnectionOutput(indexOC,3 ,pnameOut3,ptypeOut3);
}
 break;

/*         
 *    INPUT BUFFER SYSTEM  INITS 
 */ 
 case INPUT_BUFFER_INIT:
 {
 int indexIC = block_P->model_index;
     char   *ptypeIn0 = " complex ";
     char   *pnameIn0 = " x1 ";
     char   *ptypeIn1 = " complex ";
     char   *pnameIn1 = " x2 ";
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
             stateVariable = 0 ;



         
   if(NO_OUTPUT_BUFFERS() != 4 ){
       fprintf(stdout,"%s:4 outputs expected; %d connected\n",
              STAR_NAME,NO_OUTPUT_BUFFERS());
	      return(201);
   }

   SET_CELL_SIZE_OUT(0,sizeof( complex ));

   SET_CELL_SIZE_OUT(1,sizeof( complex ));

   SET_CELL_SIZE_OUT(2,sizeof( complex ));

   SET_CELL_SIZE_OUT(3,sizeof( complex ));

         
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

 



break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 



for (k = MIN_AVAIL();k>0; --k) {

       IT_IN(0);
       IT_IN(1);
       xs1=x1(0);
       xs2=x2(0);


   	   /*
	    * ready output buffer for sample
	    * check for overflow
	    */
	   if(IT_OUT(0)) {
				KrnOverflow("stmat2x4",0);
				return(99);
	   }
	   if(IT_OUT(1)) {
				KrnOverflow("stmat2x4",1);
				return(99);
	   }
	   if(IT_OUT(2)) {
				KrnOverflow("stmat2x4",2);
				return(99);
	   }
	   if(IT_OUT(3)) {
				KrnOverflow("stmat2x4",3);
				return(99);
	   }

	   /*
	    * output the sample
	    */
           sample.re= xs1.re-xs2.re;
           sample.im= xs1.im-xs2.im;
	   y1(0)=sample;

           sample.re= -xs1.re-xs2.re;
           sample.im= -xs1.im-xs2.im;

           y2(0)=sample;

           sample.re= -xs1.re+xs2.re;
           sample.im= -xs1.im+xs2.im;

           y3(0)=sample;

           sample.re=  xs1.re+xs2.re;
           sample.im=  xs1.im+xs2.im;

           y4(0)=sample;
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
