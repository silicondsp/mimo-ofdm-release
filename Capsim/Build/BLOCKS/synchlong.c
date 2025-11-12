 
#ifdef LICENSE
o

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

Add short description here. Will appear in HTML documentation.

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
       int   __count;
       int   __detect;
       int   __longCount;
       int   __outputOFDMSyms;
       int   __skipSF;
       int   __countSF;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  count  (state_P->__count)
#define  detect  (state_P->__detect)
#define  longCount  (state_P->__longCount)
#define  outputOFDMSyms  (state_P->__outputOFDMSyms)
#define  skipSF  (state_P->__skipSF)
#define  countSF  (state_P->__countSF)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*(( complex   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define ofdmsym(delay) *( complex   *)POUT(0,delay)
#define longsym(delay) *( complex   *)POUT(1,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define skipCount (param_P[0]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
synchlong
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


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " Samples to Skip ";
     char   *ptype0 = "int";
     char   *pval0 = "160";
     char   *pname0 = "skipCount";
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
     char   *pnameOut0 = " ofdmsym ";
     char   *ptypeOut1 = " complex ";
     char   *pnameOut1 = " longsym ";
KrnModelConnectionOutput(indexOC,0 ,pnameOut0,ptypeOut0);
KrnModelConnectionOutput(indexOC,1 ,pnameOut1,ptypeOut1);
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
        detect = 0 ;
        longCount = 0 ;
        outputOFDMSyms = 0 ;
        skipSF = 0 ;
        countSF = 0 ;



         
   if(NO_OUTPUT_BUFFERS() != 2 ){
       fprintf(stdout,"%s:2 outputs expected; %d connected\n",
              STAR_NAME,NO_OUTPUT_BUFFERS());
	      return(201);
   }

   SET_CELL_SIZE_OUT(0,sizeof( complex ));

   SET_CELL_SIZE_OUT(1,sizeof( complex ));

         
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

 
   detect=0;
   count=0;
   longCount=0;
   outputOFDMSyms=0;
   skipSF=0;
   countSF=0;

break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 




while(IT_IN(0)) {
       sample=x(0);
       count++;
       if(count == skipCount) { 
             detect=1;
	     countSF=0;
       }
       if(detect) longCount++;
       if(outputOFDMSyms) countSF++;
       if(countSF ==80) skipSF=1;
       
       
       if(outputOFDMSyms && detect ) { 
   	   /*
	    * ready output buffer for sample
	    * check for overflow
	    */
	   if(IT_OUT(0)) {
				KrnOverflow("synchlong",0);
				return(99);
	   }
	   /*
	    * output the sample
	    */
	   ofdmsym(0)=sample;
        }
	if(outputOFDMSyms ==0 && detect==1  ) {
	   if(IT_OUT(1)) {
				KrnOverflow("synchlong",1);
				return(99);
	   }
	   /*
	    * output the sample
	    */
	   longsym(0)=sample;

        }
        if(longCount ==2*64) {
                    outputOFDMSyms=1;	
		    countSF=0;
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
