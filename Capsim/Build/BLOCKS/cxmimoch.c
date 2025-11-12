 
#ifdef LICENSE


/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 2000-2017   Silicon DSP  Corporation

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



 



 


#define RAND_LARGE 0x7fffffff
#define DEC

#define MAX_TAPS 1024


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
      int  __Ndiv2;
      int  __NTaps;
      int  __numberTxAntennas;
      int  __numberRxAntennas;
      complex***  __h_P;
      complex**  __x_P;
      complex**  __sum_P;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define Ndiv2 (state_P->__Ndiv2)
#define NTaps (state_P->__NTaps)
#define numberTxAntennas (state_P->__numberTxAntennas)
#define numberRxAntennas (state_P->__numberRxAntennas)
#define h_P (state_P->__h_P)
#define x_P (state_P->__x_P)
#define sum_P (state_P->__sum_P)

/*         
 *    PARAMETER DEFINES 
 */ 
#define sampRateMHz (param_P[0]->value.f)
#define delaySprdNsec (param_P[1]->value.f)
#define seedParam (param_P[2]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  cxmimoch(int run_state,block_Pt block_P)

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

        double taps_r[MAX_TAPS];
        double taps_i[MAX_TAPS];
        double vark[MAX_TAPS];

       
        float sampTimeNsec;
        float var0;
        int Kmax;
        int i,j,k;
        int samples;
        double s,t,u,v,w,x;
        float y1,y2;
        int trouble;
        long 	seed=775499;
        float std=1.0;


        int iRx, iTx;
        complex val;
       
	
	
	

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
 *        SYSTEM INITIALIZATION CODE 
 */
case SYSTEM_INIT:
     
	star_P->state_P = (char*)calloc(1,sizeof(state_t));
	state_P = (state_Pt)star_P->state_P;
     
break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

        printf("Initializing %s\n",STAR_NAME);


	/* store as state the number of input/output buffers */
	if((numberTxAntennas = NO_INPUT_BUFFERS()) < 1) {
		fprintf(stderr,"cxmimoch: no input buffers\n");
		return(2);
	}
	if((numberRxAntennas = NO_OUTPUT_BUFFERS()) < 1) {
		fprintf(stderr,"cxmimoch: no output buffers\n");
		return(3);
	}
	for (i=0; i<numberTxAntennas; i++) 
		SET_CELL_SIZE_IN(i,sizeof(complex));
	for (i=0; i<numberRxAntennas; i++) 
		SET_CELL_SIZE_OUT(i,sizeof(complex));

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
        fprintf(stderr,"cxmimoch too many Taps Kmax=%d \n",Kmax);
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


/*
 * Allocate H matrix Time Domain
 */
h_P=(complex ***) calloc(numberTxAntennas,sizeof(complex**));
if(h_P==NULL) {
           fprintf(stderr,"cxmimoch could not allocate H matrix\n");
	   return(4);

}
for(i=0; i<numberTxAntennas; i++) {

    h_P[i]=(complex **) calloc(numberRxAntennas,sizeof(complex*));
    if(h_P[i]==NULL) {
           fprintf(stderr,"cxmimoch could not allocate H matrix\n");
	   return(5);
    }
    for(j=0; j<numberRxAntennas; j++) {
         h_P[i][j]=(complex *) calloc(Kmax,sizeof(complex));
         if(h_P[i]==NULL) {
              fprintf(stderr,"cxmimoch could not allocate H matrix\n");
	     return(6);

         }
    }
}

NTaps=Kmax;

/*
 * Allocate tapped delay lines
 */
x_P=(complex **) calloc(numberTxAntennas,sizeof(complex*));
if(x_P==NULL) {
           fprintf(stderr,"cxmimoch could not allocate tapped delay line \n");
	   return(7);

}
for(i=0; i<numberTxAntennas; i++) {

    x_P[i]=(complex *) calloc(NTaps,sizeof(complex));
    if(x_P[i]==NULL) {
           fprintf(stderr,"cxmimoch could not allocate tapped delay line \n");
	   return(8);
    }
 
}



/*
 * Allocate individual convolution results to each receive antenna from tx antenna
 */
sum_P=(complex **) calloc(numberTxAntennas,sizeof(complex*));
if(sum_P==NULL) {
           fprintf(stderr,"cxmimoch could not allocate sum\n");
	   return(9);

}
for(i=0; i<numberTxAntennas; i++) {

    sum_P[i]=(complex *) calloc(numberRxAntennas,sizeof(complex));
    if(sum_P[i]==NULL) {
           fprintf(stderr,"cxmimoch could not allocate sum\n");
	   return(10);
    }
}

fprintf(fp,"%d %d %d\n",numberTxAntennas,numberRxAntennas,Kmax);


seed=seedParam;
#ifdef DEC
srandom(seed);
#else
srand48((long int)seed);
#endif

for(iTx=0; iTx<numberTxAntennas; iTx++) {
    for(iRx=0; iRx<numberRxAntennas; iRx++) {
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
		          fprintf(stderr,"cxmimoch: problem with random number\
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
// printf("%d\t%f\t%f\n",k,y1,y2);

            fprintf(fp,"%lf\t%lf\n",taps_r[k],taps_i[k]);

            h_P[iTx][iRx][k].re=taps_r[k];
            h_P[iTx][iRx][k].im=taps_i[k];



        } // end for loop for k

   } // end iRx
}   // end iTx

fclose(fp);

//+++++++++++


        Ndiv2=NTaps/2;


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 




   for(samples = MIN_AVAIL(); samples >0; --samples) {
          for(iTx=0; iTx<numberTxAntennas; ++iTx) {
                 IT_IN(iTx);
                 val = INCX(iTx,0);

		/*
		 * Shift input sample into tapped delay line
		 */
		tmp2=val;
		for(i=0; i<NTaps; i++) {
			tmp1=x_P[iTx][i];
			x_P[iTx][i]=tmp2;
			tmp2=tmp1;
		}
                for(iRx=0; iRx<numberRxAntennas; ++iRx) {
		   /*
		    * Compute inner product from iTx to iRx
		    */
                   sum_P[iTx][iRx].re = 0.0; sum_P[iTx][iRx].im=0.0;
		   for (i=0; i<NTaps; i++) {

                     sum_P[iTx][iRx].re += x_P[iTx][i].re*h_P[iTx][iRx][i].re-x_P[iTx][i].im*h_P[iTx][iRx][i].im;
                     sum_P[iTx][iRx].im += x_P[iTx][i].im*h_P[iTx][iRx][i].re+x_P[iTx][i].re*h_P[iTx][iRx][i].im;

		   }
               }  // end iRx

         }  //end iTx

         for(iRx=0; iRx<numberRxAntennas; ++iRx) {
              sum.re = 0.0; sum.im=0.0;
              for(iTx=0; iTx<numberTxAntennas; ++iTx) {
                    sum.re += sum_P[iTx][iRx].re;
                    sum.im += sum_P[iTx][iRx].im;

              }
              if(IT_OUT(iRx)) {
                         KrnOverflow("cxmimoch",iRx);
                                return(99);
              }
              OUTCX(iRx,0) = sum;


         }

    } // end samples


break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 
for(i=0;i<numberTxAntennas; i++) {
       for(j=0;j<numberRxAntennas; j++) {
              free(h_P[i][j]);
       }
       free(h_P[i]);
}
free(h_P);
for(i=0;i<numberTxAntennas; i++) {
        free(x_P[i]);
}
free(x_P);

for(i=0;i<numberTxAntennas; i++) {
        free(sum_P[i]);
}
free(sum_P);	


break;
}
return(0);
}
