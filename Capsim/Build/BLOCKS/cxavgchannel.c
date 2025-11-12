 
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

Input the two LTS and average them in the time domain. Then output.

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



#define STATE_BUFFERING 0
#define STATE_AVERAGING 1
#define STATE_DONE 2

/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int    __count;
       complex*    __buffer_P;
       int    __theState;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  count  (state_P->__count)
#define  buffer_P  (state_P->__buffer_P)
#define  theState  (state_P->__theState)

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
#define numberOfCarriers (param_P[0]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
cxavgchannel
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
	complex average;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " Number of Carriers ";
     char   *ptype0 = "int";
     char   *pval0 = "64";
     char   *pname0 = "numberOfCarriers";
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
             count = 0 ;
        buffer_P = 0 ;
        theState = 0 ;



         
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

 
    buffer_P=(complex *)calloc(numberOfCarriers,sizeof(complex));
    if(buffer_P==NULL) {
        fprintf(stderr,"%s could not allocate space\n",STAR_NAME);
	return(2);
    }
    count=0;
    theState=STATE_BUFFERING;


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 




while(IT_IN(0)) {
       if(theState==STATE_DONE) return(0);
       sample=x(0);
       if(theState== STATE_BUFFERING) {
          buffer_P[count]=sample;
          count++;
       }
       
       if(count == numberOfCarriers) {
           theState=STATE_AVERAGING;
	   count=0;
	   return(0);
	  
       
       }
       if(theState == STATE_AVERAGING) {
           average.re=(sample.re+buffer_P[count].re)*.5;
           average.im=(sample.im+buffer_P[count].im)*.5;

   	   /*
	    * ready output buffer for sample
	    * check for overflow
	    */
	   if(IT_OUT(0)) {
				KrnOverflow("cxavgchannel",0);
				return(99);
	   }
	   /*
	    * output the sample
	    */
	   y(0)=average;
	   count++;
           if(count == numberOfCarriers) {
              theState=STATE_DONE;
	      count=0;
           }   
       }

}
    


break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 

free(buffer_P);


break;
}
return(0);
}
