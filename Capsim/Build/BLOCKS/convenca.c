 
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

COnvolutional ENcoder 802.11a

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



 

#include "typedef.h"
#include "anisim.h"



/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int   __count;
       ULINT*   __x_P;
       ULINT*   __a_P;
       ULINT*   __b_P;
       ULINT   __prev6;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  count  (state_P->__count)
#define  x_P  (state_P->__x_P)
#define  a_P  (state_P->__a_P)
#define  b_P  (state_P->__b_P)
#define  prev6  (state_P->__prev6)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*(( int   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define achan(delay) *( int   *)POUT(0,delay)
#define bchan(delay) *( int   *)POUT(1,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define NWORDS (param_P[0]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
convenca
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

	int i,j, k;
	unsigned long int  xval;
	unsigned long int  yval;
	int N1;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " Number of words to input ";
     char   *ptype0 = "int";
     char   *pval0 = "7";
     char   *pname0 = "NWORDS";
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
     char   *pnameOut0 = " achan ";
     char   *ptypeOut1 = " int ";
     char   *pnameOut1 = " bchan ";
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
     char   *ptypeIn0 = " int ";
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



         
   if(NO_OUTPUT_BUFFERS() != 2 ){
       fprintf(stdout,"%s:2 outputs expected; %d connected\n",
              STAR_NAME,NO_OUTPUT_BUFFERS());
	      return(201);
   }

   SET_CELL_SIZE_OUT(0,sizeof( int ));

   SET_CELL_SIZE_OUT(1,sizeof( int ));

         
   if(NO_INPUT_BUFFERS() != 1 ){
       fprintf(stdout,"%s:1 inputs expected; %d connected\n",
              STAR_NAME,NO_INPUT_BUFFERS());
	      return(200);
   }

   SET_CELL_SIZE_IN(0,sizeof( int ));

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

         x_P=(ULINT*)calloc(NWORDS,sizeof(ULINT));
         a_P=(ULINT*)calloc(NWORDS,sizeof(ULINT));
         b_P=(ULINT*)calloc(NWORDS,sizeof(ULINT));
         if(x_P == NULL || a_P ==NULL || b_P==NULL)  {
             fprintf(stderr,"convenca:Could not allocate space\n");
             return(3);
         }
         prev6 = 0;


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 


	for(i=MIN_AVAIL();i>0; --i) {
                x_P[count] = (unsigned long int) 0;
		IT_IN(0);
		xval = x(0);		
		x_P[count] += (xval&0xFF);
				
		IT_IN(0);
		xval = x(0);				
		x_P[count]+= ((xval&0xFF)<<8);
		i--;		
                		
		IT_IN(0);		
		xval = x(0);		
		x_P[count]+= ((xval&0xFF)<<16);		
                i--;
                		
		if( (i-1) - 27*floor((i-1)/27) != 0 )
		{			
		     IT_IN(0);	
		     xval = x(0);		
		     x_P[count]+= ((xval&0xFF)<<24);					
		     i--;
		}			
		count++;
		if(count == NWORDS)
		{
              //        fprintf(stdout, " x_P[5] is = %d \n", x_P[count-2]);		
              //        fprintf(stdout, " x_P[6] is = %d \n", x_P[count-1]);		
		      convenc(x_P, prev6, a_P, b_P, NWORDS);
		      prev6 = (x_P[6])<<8;
		      N1 = 4;
		      for(j=0; j<NWORDS; j++) {
		                xval = a_P[j];		
		                yval = b_P[j];
		                if(j==NWORDS-1)
		                {
		                    N1 = 3;
		                }
		                for(k=0; k<N1; k++){
		                         if(IT_OUT(0)) {
					          KrnOverflow("operate",0);
					          return(99);
				         }
				         achan(0)=(int) (xval&0x00FF);
				         xval = (xval>>8);
				         if(IT_OUT(1)) {
					          KrnOverflow("operate",0);
					          return(99);
				         }
				   //      printf("conv   %d  %d\n",k, yval&0x00FF );
				         bchan(0)=(int) (yval&0x00FF);
				         yval = (yval>>8);
		                }
							
		       }
		       count=0;		
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
