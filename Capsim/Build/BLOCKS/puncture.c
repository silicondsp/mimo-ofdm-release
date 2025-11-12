 
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

puncture

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



 

#include "math.h"
#include <stdio.h>


 

#define N 216
#define N54  288
#define RATE_12 12
#define RATE_34 34
#define RATE_23 23


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int*   __stateA;
       int*   __stateB;
       int   __numBits;
       int*   __punctureBuff;
       int*   __Ap;
       int*   __Bp;
       int*   __BSOp;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  stateA  (state_P->__stateA)
#define  stateB  (state_P->__stateB)
#define  numBits  (state_P->__numBits)
#define  punctureBuff  (state_P->__punctureBuff)
#define  Ap  (state_P->__Ap)
#define  Bp  (state_P->__Bp)
#define  BSOp  (state_P->__BSOp)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define dataA(DELAY) (*(( int   *)PIN(0,DELAY)))
#define dataB(DELAY) (*(( int   *)PIN(1,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define BitStolen(delay) *( int   *)POUT(0,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define codingRate (param_P[0]->value.d)
#define dataRate (param_P[1]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
puncture
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

	int count;
	int maxBits;
	int tempA,tempB;
	int insize,outsize;
	int i;
	int no_samples;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " codingRates are 12 23 34. ";
     char   *ptype0 = "int";
     char   *pval0 = "RATE_34";
     char   *pname0 = "codingRate";
     char   *pdef1 = " dataRate=54 ";
     char   *ptype1 = "int";
     char   *pval1 = "54";
     char   *pname1 = "dataRate";
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
     char   *ptypeOut0 = " int ";
     char   *pnameOut0 = " BitStolen ";
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
     char   *pnameIn0 = " dataA ";
     char   *ptypeIn1 = " int ";
     char   *pnameIn1 = " dataB ";
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
     


         
   if(NO_OUTPUT_BUFFERS() != 1 ){
       fprintf(stdout,"%s:1 outputs expected; %d connected\n",
              STAR_NAME,NO_OUTPUT_BUFFERS());
	      return(201);
   }

   SET_CELL_SIZE_OUT(0,sizeof( int ));

         
   if(NO_INPUT_BUFFERS() != 2 ){
       fprintf(stdout,"%s:2 inputs expected; %d connected\n",
              STAR_NAME,NO_INPUT_BUFFERS());
	      return(200);
   }

   SET_CELL_SIZE_IN(0,sizeof( int ));

   SET_CELL_SIZE_IN(1,sizeof( int ));

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

 /* allocate memory and return pointers for internal states*/
 if((stateA= (int*)calloc(N,sizeof(int))) == NULL ||
   (stateB = (int*)calloc(N,sizeof(int))) == NULL ||
    (punctureBuff = (int*)calloc(N54,sizeof(int))) == NULL ||
    (Ap = (int*)calloc(N54,sizeof(int))) == NULL ||
    (Bp = (int*)calloc(N54,sizeof(int))) == NULL ||
    (BSOp = (int*)calloc(N54,sizeof(int))) == NULL ) {
   fprintf(stderr,"puncture: can't allocate work space\n");
   return(4);
   }
   numBits=0;


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 



for (no_samples = MIN_AVAIL();no_samples>0; --no_samples)
  {

  IT_IN(0);        /*read input from buffer*/
  IT_IN(1);
  tempA=dataA(0);
  tempB=dataB(0);

  switch (dataRate)
 	{
 	default:
 	case 54:
 	   insize=216;
 	   outsize=288;
 	//   numBytes=insize/8;
 	   break;

 	}

  /*convert from 8 bits per input value coming from conv. coder to 1 bit per element in the array*/
  for (i=0;i<8;i++)
  	{
  	stateA[numBits]=tempA&1;  tempA=tempA>>1;
  	stateB[numBits]=tempB&1;  tempB=tempB>>1;
  	numBits++;
  	}
  if (numBits ==insize)
  {/*once you get enough bits for a symbol, do puncture work here*/
	//create the bit-stolen output,
	numBits = 0;
	Ap=stateA;
	Bp=stateB;
	BSOp=punctureBuff;
	
	switch (codingRate)
	{
		case RATE_12:  //just copy input to output, alternating A, then B

			count=0;
			do
			{
				*BSOp++ = *Ap++; count++;
				*BSOp++ = *Bp++; count++;
			} while (count<outsize);
			break;

		case RATE_34:  //create pattern: A0,B0,A1,B2
			count=0;
			do
			{
				*BSOp++ = *Ap++; count++;
				*BSOp++ = *Bp++; count++; Bp++;//skip B1
				*BSOp++ = *Ap++; count++; Ap++;//skip A2
				*BSOp++ = *Bp++; count++;
		//	 printf("puncture   %d\n",i,  *--BSOp);
			} while (count<outsize);
			break;
		case RATE_23:  //create pattern: A0,B0,A1
			count=0;
			do
			{
				*BSOp++ = *Ap++; count++;
				*BSOp++ = *Bp++; count++; Bp++;//skip B1
				*BSOp++ = *Ap++; count++;
			} while (count<outsize);
			break;

	} //end switch
	
	
 /*now do the CAPSIM-specific processing for output buffer*/



     for (i=0;i<outsize;i++)
    	{
     	
     	 if(IT_OUT(0)){
	          KrnOverflow("puncture",0);
	          return(99);
	          }
  //      printf("puncture %d  %d\n",i, punctureBuff[i]);	
        BitStolen(0) = punctureBuff[i];


     	}
  }/*end of if clause which really proceses a symbol*/

}  /*end outer for loop*/


break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 



break;
}
return(0);
}
