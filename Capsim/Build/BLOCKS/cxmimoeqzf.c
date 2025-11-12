 
#ifdef LICENSE


/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 2007-2017   Silicon DSP  Corporation

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



 

#include <tcl.h>
//#include <vectors.h>
#include "mimo.h"



 


#define MAX_TAPS 1024


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
      int  __Ndiv2;
      int  __nTaps;
      int  __numberStreams;
      int  __numberRxAntennas;
      complex***  __h_P;
      cxVector_t*  __x_P;
      cxVector_t*  __y_P;
      int  __count;
      dsp_cxMatrix_t**  __W_P;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define Ndiv2 (state_P->__Ndiv2)
#define nTaps (state_P->__nTaps)
#define numberStreams (state_P->__numberStreams)
#define numberRxAntennas (state_P->__numberRxAntennas)
#define h_P (state_P->__h_P)
#define x_P (state_P->__x_P)
#define y_P (state_P->__y_P)
#define count (state_P->__count)
#define W_P (state_P->__W_P)

/*         
 *    PARAMETER DEFINES 
 */ 
#define numberTxAntennas (param_P[0]->value.d)
#define lengthFFT (param_P[1]->value.d)
#define HMatrixFileName (param_P[2]->value.s)
/*-------------- BLOCK CODE ---------------*/
 int  cxmimoeqzf(int run_state,block_Pt block_P)

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

        float xre,xim;

        float *xre_P,*xim_P,*yre_P,*yim_P;

        int iRx, iTx;
        int nTx,nRx;
        complex val;
       
        dsp_cxMatrix_t* H_P;
        dsp_cxMatrix_t* HT_P;
        dsp_cxMatrix_t* A_P;	
        dsp_cxMatrix_t* Ai_P;	
	

switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = "Number of Transmit Antennas";
     char   *ptype0 = "int";
     char   *pval0 = "2";
     char   *pname0 = "numberTxAntennas";
     char   *pdef1 = "FFT Length";
     char   *ptype1 = "int";
     char   *pval1 = "64";
     char   *pname1 = "lengthFFT";
     char   *pdef2 = "File Name with Channel H Matrix";
     char   *ptype2 = "file";
     char   *pval2 = "cxmimoch0.taps";
     char   *pname2 = "HMatrixFileName";
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
	if((numberRxAntennas = NO_INPUT_BUFFERS()) < 1) {
                fprintf(stderr,"cxmimoch: no input buffers\n");
		return(2);
	}
	if((numberStreams = NO_OUTPUT_BUFFERS()) < 1) {
              fprintf(stderr,"cxmimoch: no output buffers\n");
		return(3);
	}


        if(numberStreams != numberTxAntennas) {
               fprintf(stderr,"cxmimoch: output streams must match number Tx antennas fo now.\n");
		return(4);


        }

        fp=fopen(HMatrixFileName,"r");
        if(!fp) {
            fprintf(stderr,"cxmimoch: Could not open H Matrix file %s.\n",HMatrixFileName);
                return(5);
        }

        fscanf(fp,"%d %d %d",&nTx,&nRx, &nTaps);

        if(nTx != numberTxAntennas ) {
            fprintf(stderr,"cxmimoch: Param Tx Antenna does not match in H Matrix file s.\n");
                return(6);

        }

        if(nRx != numberRxAntennas ) {
            fprintf(stderr,"cxmimoch: Rx paths do  not match number of Rx antennas in  H Matrix file s.\n");
                return(7);

        }
        xre_P=(float *)calloc(lengthFFT,sizeof(float));
        xim_P=(float *)calloc(lengthFFT,sizeof(float));

        yre_P=(float *)calloc(lengthFFT,sizeof(float));
        yim_P=(float *)calloc(lengthFFT,sizeof(float));

        if(!xre_P || !xim_P || !yre_P || !yim_P ) {
            fprintf(stderr,"cxmimoch: Could not allocate space.\n");
                return(8);

        }
	for (i=0; i<numberRxAntennas; i++) 
		SET_CELL_SIZE_IN(i,sizeof(complex));
	for (i=0; i<numberStreams; i++) 
		SET_CELL_SIZE_OUT(i,sizeof(complex));





/*
 * Allocate H matrix Time Domain
 */
h_P=(complex ***) calloc(numberRxAntennas,sizeof(complex**));
if(h_P==NULL) {
           fprintf(stderr,"cxmimoeqzf could not allocate H matrix\n");
	   return(8);

}
for(i=0; i<numberRxAntennas; i++) {

    h_P[i]=(complex **) calloc(numberTxAntennas,sizeof(complex*));
    if(h_P[i]==NULL) {
           fprintf(stderr,"cxmimoeqzf could not allocate H matrix\n");
	   return(9);
    }
    for(j=0; j<numberTxAntennas; j++) {
         h_P[i][j]=(complex *) calloc(lengthFFT,sizeof(complex));
         if(h_P[i]==NULL) {
              fprintf(stderr,"cxmimoeqzf could not allocate H matrix\n");
	     return(10);

         }
    }
}



H_P= Dsp_AllocateCxMatrix(numberRxAntennas,numberTxAntennas);
if(H_P==NULL) {
              fprintf(stderr,"cxmimoeqzf could not allocate single  H matrix\n");
	     return(11);

}
HT_P= Dsp_AllocateCxMatrix(numberTxAntennas,numberRxAntennas);
if(HT_P==NULL) {
              fprintf(stderr,"cxmimoeqzf could not allocate single  HT matrix\n");
	     return(11);

}
A_P= Dsp_AllocateCxMatrix(numberTxAntennas,numberTxAntennas);
if(A_P==NULL) {
              fprintf(stderr,"cxmimoeqzf could not allocate single  A matrix\n");
	     return(11);

}
Ai_P= Dsp_AllocateCxMatrix(numberTxAntennas,numberTxAntennas);
if(Ai_P==NULL) {
              fprintf(stderr,"cxmimoeqzf could not allocate single  A matrix\n");
	     return(11);

}

W_P=(dsp_cxMatrix_t **)calloc(lengthFFT,sizeof(dsp_cxMatrix_t *));
if(W_P==NULL) {
              fprintf(stderr,"cxmimoeqzf could not allocate Equalizer Matrix W\n");
	     return(12);

}
for(i=0; i<lengthFFT; i++) {
    W_P[i]=Dsp_AllocateCxMatrix(numberTxAntennas,numberRxAntennas);
    if(W_P[i]==NULL) {
              fprintf(stderr,"cxmimoeqzf could not allocate Equalizer Matrix W\n");
	     return(13);

    }
}

x_P=Dsp_AllocateCxVector(numberStreams);
y_P=Dsp_AllocateCxVector(numberRxAntennas);

if(!x_P || !y_P) {
              fprintf(stderr,"cxmimoeqzf could not allocate space \n");
	     return(14);

}



/*
 * Read in H matrix (time domain complex impulse responses
 * Take FFT convert to frequency domain.
 */

for(i=0; i<numberTxAntennas; i++) {
           for(j=0; j<numberRxAntennas; j++) {


                 for(k=0; k<nTaps; k++) {
                    
                      fscanf(fp,"%f %f", &xre_P[k],&xim_P[k]);
                      if(k >= lengthFFT) continue;
                      
                    
                         
                 }
                 fft2s(xre_P,xim_P,yre_P,yim_P,lengthFFT,1);
                 for(k=0; k<lengthFFT; k++) {
                     h_P[j][i][k].re=yre_P[k];
                     h_P[j][i][k].im=yim_P[k];
                     printf("%d %f %f %f\n",k,yre_P[k],yim_P[k],sqrt(yre_P[k]*yre_P[k]+yim_P[k]*yim_P[k]));
                 }

           }
}
fclose(fp);

free(xre_P);
free(xim_P);
free(yre_P);
free(yim_P);

for(k=0; k< lengthFFT; k++) {
    // if(k==0 || k >40) continue;
    if(k==0 || (k >26 && k<38) ) continue;
     for(i=0; i< numberRxAntennas; i++) {
           for(j=0; j< numberTxAntennas; j++) {

                H_P->matrix_PP[i][j].re=h_P[i][j][k].re;
                H_P->matrix_PP[i][j].im=h_P[i][j][k].im;
           }
     }
     for(i=0; i<numberTxAntennas ; i++) {
           for(j=0; j< numberRxAntennas; j++) {

                HT_P->matrix_PP[i][j].re=h_P[j][i][k].re;
                HT_P->matrix_PP[i][j].im= -h_P[j][i][k].im;
           }
     }
     Dsp_MultiplyComplexMatrices(HT_P, H_P,A_P);
     Krn_ComputeInverseCxMatrix(A_P, Ai_P);

     Dsp_MultiplyComplexMatrices(Ai_P, HT_P,W_P[k]);


#ifdef REPORT
printf("H_P\n");
Krn_PrintCxMatrix(H_P, "f", stdout);
printf("HT_P\n");
Krn_PrintCxMatrix(HT_P, "f", stdout);
printf("A_P\n");
Krn_PrintCxMatrix(A_P, "f", stdout);
printf("Ai_P\n");
Krn_PrintCxMatrix(Ai_P, "f", stdout);
printf("W_P[%d]\n",k);
Krn_PrintCxMatrix(W_P[k], "f", stdout);
printf("+++++++++++++++++++++++++++++++++\n");
#endif

//

}


//TODO Free up H_P,HT_P,A_P,Ai_P




   

        count=0;


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 




   for(samples = MIN_AVAIL(); samples >0; --samples) {
          for(iRx=0; iRx<numberRxAntennas; iRx++) {
                 IT_IN(iRx);
                 val = INCX(iRx,0);
                 y_P->vector_P[iRx].re=val.re;
                 y_P->vector_P[iRx].im=val.im;

          }
          k=count;
          if(!(k==0 || (k >26 && k<38) )) {
           
          
               Dsp_MultiplyComplexMatricesComplexVector(W_P[count],y_P,x_P);

               for(iTx=0; iTx<numberStreams; iTx++) {
                    if(IT_OUT(iTx)) {
                         KrnOverflow("cxmimoch",iTx);
                                return(99);
                    }
                    val.re=x_P->vector_P[iTx].re;
                    val.im=x_P->vector_P[iTx].im;
                    OUTCX(iTx,0) = val;
               }

          }
          count++;
          count = count % lengthFFT;

    } // end samples


break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 

for(i=0;i<lengthFFT; i++) {
      Dsp_FreeCpxMatrix((dsp_cpxMatrix_t*)W_P[i]);
}



break;
}
return(0);
}
