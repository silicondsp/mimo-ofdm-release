 
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



 

#include <math.h>
#include <stdio.h>


 


#define RAND_LARGE 0x7fffffff
#define DEC

#define MAX_TAPS 1024


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
      complex*  __x_P;
      complex*  __h_P;
      int  __Ndiv2;
      int  __NTaps;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define x_P (state_P->__x_P)
#define h_P (state_P->__h_P)
#define Ndiv2 (state_P->__Ndiv2)
#define NTaps (state_P->__NTaps)

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*((complex  *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define y(delay) *(complex  *)POUT(0,delay)

/*         
 *    PARAMETER DEFINES 
 */ 
#define sampRateMHz (param_P[0]->value.f)
#define delaySprdNsec (param_P[1]->value.f)
#define seedParam (param_P[2]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  cxchmodel(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

 	complex tmp1,tmp2;
        complex  sum;
        complex tmp;
	FILE *fp;
	char fileName[256];

        float taps_r[MAX_TAPS];
        float taps_i[MAX_TAPS];
        float vark[MAX_TAPS];

       
        float sampTimeNsec;
        float var0;
        int Kmax;
        int i,j,k;
        double s,t,u,v,w,x;
        float y1,y2;
        int trouble;
        long 	seed=775499;
        float std=1.0;
	
	
	

switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = "Sampling Rate (MHz)";
     char   *ptype0 = "float";
     char   *pval0 = "200";
     char   *pname0 = "sampRateMHz";
     char   *pdef1 = "Delay Spread (ns)";
     char   *ptype1 = "float";
     char   *pval1 = "50";
     char   *pname1 = "delaySprdNsec";
     char   *pdef2 = "Seed";
     char   *ptype2 = "int";
     char   *pval2 = "725443";
     char   *pname2 = "seedParam";
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
     char   *ptypeOut0 = "complex";
     char   *pnameOut0 = "y";
KrnModelConnectionOutput(indexOC,0 ,pnameOut0,ptypeOut0);
}
 break;

/*         
 *    INPUT BUFFER SYSTEM  INITS 
 */ 
 case INPUT_BUFFER_INIT:
 {
 int indexIC = block_P->model_index;
     char   *ptypeIn0 = "complex";
     char   *pnameIn0 = "x";
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

   SET_CELL_SIZE_OUT(0,sizeof(complex));

         
   if(NO_INPUT_BUFFERS() != 1 ){
       fprintf(stdout,"%s:1 inputs expected; %d connected\n",
              STAR_NAME,NO_INPUT_BUFFERS());
	      return(200);
   }

   SET_CELL_SIZE_IN(0,sizeof(complex));

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

//+++++++++++
// function [taps] = ExpChanTaps(sampRateMHz, delaySprdNsec)
sprintf(fileName,"%s.taps",STAR_NAME);
fp=fopen(fileName,"w");
if(!fp) {printf("%s could not open file.\n",STAR_NAME); return(100);}

sampTimeNsec = 1000.00 / sampRateMHz;
printf("fs(MHz)=%f delay spread (ns) =%f \n",sampRateMHz,delaySprdNsec);
if (delaySprdNsec == 0) {
   Kmax = 0;
   vark[0] = 1;
} else {
   Kmax = ceil( 10 * delaySprdNsec/sampTimeNsec );
   printf("Kmax=%d\n",Kmax);
  // fprintf(fp,"%d\n",Kmax);
   if(Kmax > MAX_TAPS) {
        fprintf(stderr,"cxchmodel too many Taps Kmax=%d \n",Kmax);
	return(101);
   }
   var0 = (1 - exp( -1*(sampTimeNsec)/delaySprdNsec ))/(1 - exp( -1*((Kmax+1)* sampTimeNsec)/delaySprdNsec ));

   for(k=0; k<Kmax; k++) {
        vark[k] = var0 * exp( - k*sampTimeNsec/delaySprdNsec );       
   }
 }
for(k=0; k<Kmax; k++) {
        vark[k] = sqrt(vark[k]/2);       
}
seed=seedParam;
#ifdef DEC
srandom(seed);
#else
srand48((long int)seed);
#endif
/*
 * calculate the taps
 */
for(k=0; k<Kmax; k++) {


/****************************************************************/
/* 		gauss						*/
/* code written by Prayson Pate					*/
/* This code generates two random variables that are normally 	*/
/* distributed with mean 0 and variance 1 i.e N(0,1).	 	*/
/* The polar method is used to generate normally distributed    */
/* samples from a sequence that is uniform on (-1,1).  The      */
/* resulting distribution is described exactly by N(0,1).       */
/* This method is based	on the inverse distribution function.   */
/****************************************************************/
trouble = 0;
do {
	if(++trouble > 100) {
		fprintf(stderr,"gauss: problem with random number\
			 generator\n");
		return(2);
	}
	/* 
 	 * get two random numbers in the interval (-1,1) 
	 */
#ifdef DEC
	s = (double)random()/RAND_LARGE;
#else
	s = drand48();
#endif
	u = -1.0 + 2.0*s;
#ifdef DEC
	t = (double)random()/RAND_LARGE;
#else
	t = drand48();
#endif
	v = -1.0 + 2.0*t;
	w = u*u + v*v;
	/* 
	 * is point (u,v) in the unit circle? 
	 */
} while (w >= 1.0 || w == 0.0);

x = sqrt((-2.0 * log(w))/w);
/* 
 * find two independent values of y	
 */
y1 = std * u * x;
y2 = std * v * x;

taps_r[k]=vark[k]*y1;
taps_i[k]=vark[k]*y2;

//printf("%d\t%f\t%f\n",k,taps_r[k],taps_i[k]);
//// printf("%d\t%f\t%f\n",k,y1,y2);

fprintf(fp,"%f\t%f\n",taps_r[k],taps_i[k]);

} // end for loop for k

fclose(fp);

//+++++++++++

NTaps=Kmax;

        Ndiv2=NTaps/2;
	/*
	 * Allocate memory and return pointers for tapped delay line x_P and
	 * array containing impulse response samples, h_P.
	 *
	 */
	if( (x_P = (complex*)calloc(NTaps,sizeof(complex))) == NULL ||
	    (h_P = (complex*)calloc(NTaps,sizeof(complex))) == NULL ) {
	   	fprintf(stderr,"cxchmodel: can't allocate work space\n");
		return(103);
	}
	/*
	 * Read in the impulse response samples into the array
	 * and initialize the tapped delay line to zero.
	 *
	 */
	for (i=0; i<NTaps; i++) {
		x_P[i].re= 0.0;   x_P[i].im= 0.0;
		h_P[i].re=taps_r[i];
		h_P[i].im=taps_i[i];
		
	}
          
	SET_CELL_SIZE_IN(0,sizeof(complex));
	SET_CELL_SIZE_OUT(0,sizeof(complex));


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 




	while(IT_IN(0)){
		/*
		 * Shift input sample into tapped delay line
		 */
		tmp2=x(0);
		for(i=0; i<NTaps; i++) {
			tmp1=x_P[i];
			x_P[i]=tmp2;
			tmp2=tmp1;
		}
		/*
		 * Compute inner product
		 */
                sum.re = 0.0; sum.im=0.0;
		for (i=0; i<NTaps; i++) {

                     sum.re += x_P[i].re*h_P[i].re+x_P[i].im*h_P[i].im;
                     sum.im += x_P[i].im*h_P[i].re-x_P[i].re*h_P[i].im;

		}
		if(IT_OUT(0)) {
			KrnOverflow("cxchmodel",0);
			return(99);
		}
		/*
	  	 * set output buffer to response result
		 */
		y(0) = sum;
	}


break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 

	free(x_P); free(h_P); 


break;
}
return(0);
}
