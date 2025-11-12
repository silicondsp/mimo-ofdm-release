 
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

scramble

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



/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int   __count;
       int*   __seed;
       char*   __x_in;
       char*   __x_out;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  count  (state_P->__count)
#define  seed  (state_P->__seed)
#define  x_in  (state_P->__x_in)
#define  x_out  (state_P->__x_out)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*(( int   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define y(delay) *( int   *)POUT(0,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define N (param_P[0]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
scramble
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

	int i,j;
	char  xval;	
	int temp;
	int ed[7] = {1, 0, 1, 1, 1, 0, 1};	


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = " Number of bytes to input ";
     char   *ptype0 = "int";
     char   *pval0 = "216";
     char   *pname0 = "N";
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

   SET_CELL_SIZE_IN(0,sizeof( int ));

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

         x_in=(char*)calloc(N,sizeof(char));
         x_out=(char*)calloc(N/8,sizeof(char));
         seed = (int*)calloc(7, sizeof(int));
         for(i=0; i<7; i++)
         {
               seed[i] = ed[i];
         }
         if(x_in == NULL || x_out == NULL)  {
             fprintf(stderr,"scrambler:Could not allocate space\n");
             return(3);
         }
/*         SET_CELL_SIZE_OUT(0, sizeof(ULINT) );  */


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 

        while(IT_IN(0))
	{
		xval = (char)x(0);
		x_in[count]=xval;
		count++;
	        if(count == N)
	        {
	              scrambler_216(seed, (unsigned char *)x_in, (unsigned char *)x_out, N);
	              count = 0;
                      for(i=0; i<7; i++)
                      {

                            seed[i] = 0;
                      }	
	
	              for(j=0; j<N/8; j++)
	              {
	                     IT_OUT(0);
	                     temp = (int) 0;
	                     temp += x_out[j];
	                     y(0) = temp;
                      }
	
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
