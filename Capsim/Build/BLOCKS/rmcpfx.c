 
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
       complex*   __buffer_P;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  count  (state_P->__count)
#define  buffer_P  (state_P->__buffer_P)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define X(DELAY) (*(( complex   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define y(delay) *( complex   *)POUT(0,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define symbolLength (param_P[0]->value.d)
#define cycPrefixLength (param_P[1]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
rmcpfx
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

   	int i,k;
   	complex sample;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = "Symbol  Length ";
     char   *ptype0 = "int";
     char   *pval0 = "80";
     char   *pname0 = "symbolLength";
     char   *pdef1 = "Cyclic Prefix  Length ";
     char   *ptype1 = "int";
     char   *pval1 = "16";
     char   *pname1 = "cycPrefixLength";
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
     char   *pnameIn0 = " X ";
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

 

  SET_CELL_SIZE_IN (0, sizeof(complex));
  SET_CELL_SIZE_OUT (0, sizeof(complex));


buffer_P=(complex*)calloc(symbolLength,sizeof(complex));
if(!buffer_P) {
    fprintf(stderr,"rmcpfx:Could not allocate space\n");
	return(2);
}


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 


for(i = MIN_AVAIL(); i>0; i--) {

       IT_IN(0);
       sample = INCX(0,0);
       buffer_P[count]=sample;
       count++;
       if(count == symbolLength) {

           count = 0; 

           for(k=cycPrefixLength; k<symbolLength; k++) {
  
		   	   /*
			    * ready output buffer for sample
			    * check for overflow
			    */
			   if(IT_OUT(0)) {
					KrnOverflow("rmcpfx",0);
					return(99);
			   }

			   /*
			    * output the sample
			    */
			   sample=buffer_P[k];

			   y(0) = sample;
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
