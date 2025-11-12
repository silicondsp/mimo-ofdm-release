 
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

Data Field 802.11a

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



 

#include <math.h>
#include "typedef.h"
#include "anisim.h"


 

#define N_DBPS54 216              /* for 54 Mbps */
#define SERVICE  16               /* the number of service bits */
#define TAIL 6                    /* number of tail bits */
#define N  32832                  /* the max number of bits in DATA field: N_data */


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       float*   __interX;
       int*   __interY;
       int   __numBits;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  interX  (state_P->__interX)
#define  interY  (state_P->__interY)
#define  numBits  (state_P->__numBits)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*(( float   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define y(delay) *( int   *)POUT(0,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define numPSDU (param_P[0]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
dataField
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

double temp;
double Lp;
int nData, nPad,i;
int nSym;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = "  the  number of PSDU(data bits)  ";
     char   *ptype0 = "int";
     char   *pval0 = "64";
     char   *pname0 = "numPSDU";
KrnModelParam(indexModel88,0 ,pdef0,ptype0,pval0,pname0);

      }
break;
   


/*         
 *    OUTPUT BUFFER SYSTEM  INITS 
 */ 
 case OUTPUT_BUFFER_INIT: 
 {
 int indexOC = block_P->model_index;
     char   *ptypeOut0 = " int ";
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
     char   *ptypeIn0 = " float ";
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

   SET_CELL_SIZE_OUT(0,sizeof( int ));

         
   if(NO_INPUT_BUFFERS() != 1 ){
       fprintf(stdout,"%s:1 inputs expected; %d connected\n",
              STAR_NAME,NO_INPUT_BUFFERS());
	      return(200);
   }

   SET_CELL_SIZE_IN(0,sizeof( float ));

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

 /* allocate memory and return pointers for internal states interX */
 if((interX = (float*)calloc(numPSDU,sizeof(float))) == NULL ||
   (interY = (int*)calloc(numPSDU+SERVICE+TAIL+N_DBPS54,sizeof(int))) == NULL) {
   fprintf(stderr,"Datafield: can't allocate work space\n");
   return(4);
   }
 numBits = 0;


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 


   while(IT_IN(0))
    {
      interX[numBits] = x(0);
      numBits++;

      if (numBits == numPSDU)
       {
        numBits = 0;
        temp = (double) (SERVICE + numPSDU + TAIL)/N_DBPS54;

        Lp = ceil(temp);
        nSym = (int) Lp;

        /* number of bits in DATA field  */

        nData = nSym * N_DBPS54;

        /* number of Pad bits  */

        nPad = nData - (SERVICE + numPSDU + TAIL);

        /* outdata with 16 service bits and 6 tail bits and pad zeros   */

         for (i=0; i<SERVICE; i++)            /* add service bits total 16 bits */
            interY[i] = 0;


         for (i=0; i< numPSDU; i++)           /* add PSDU */
            interY[i+SERVICE] = (int) interX[i];

         for (i=0; i<nPad+6; i++)      /* add tail bits and pad bits   */
	    interY[i+SERVICE+numPSDU] = 0;
	
	 for (i=0;i<nData;i++)
           {
             if(IT_OUT(0)){
	          KrnOverflow("dataField",0);
	          return(99);
	          }
	
	    // y(0) = interY[i];
	 //   printf("dataField y=%d\n",  interY[i]);
	
	     OUTI(0,0)=   interY[i];
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
