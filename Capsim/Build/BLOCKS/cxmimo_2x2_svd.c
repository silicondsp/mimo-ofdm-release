 
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
#include "matrixBuffers.h"
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
      int  __feedbackState;
      cxVector_t*  __x_P;
      cxVector_t*  __xx_P;
      cxVector_t*  __y_P;
      int  __count;
      dsp_cxMatrix_t**  __U_P;
      doubleVector_t**  __Sigma_P;
      dsp_cxMatrix_t**  __V_P;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define Ndiv2 (state_P->__Ndiv2)
#define nTaps (state_P->__nTaps)
#define numberStreams (state_P->__numberStreams)
#define numberRxAntennas (state_P->__numberRxAntennas)
#define h_P (state_P->__h_P)
#define feedbackState (state_P->__feedbackState)
#define x_P (state_P->__x_P)
#define xx_P (state_P->__xx_P)
#define y_P (state_P->__y_P)
#define count (state_P->__count)
#define U_P (state_P->__U_P)
#define Sigma_P (state_P->__Sigma_P)
#define V_P (state_P->__V_P)

/*         
 *    PARAMETER DEFINES 
 */ 
#define numberTxAntennas (param_P[0]->value.d)
#define lengthFFT (param_P[1]->value.d)
#define HMatrixFileName (param_P[2]->value.s)
/*-------------- BLOCK CODE ---------------*/
 int  cxmimo_2x2_svd(int run_state,block_Pt block_P)

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

        int len;
        float svr;

        FILE *svr_F;
       
        dsp_cxMatrix_t* H_P;
        dsp_cxMatrix_t  cxmat;
 	

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
     char   *pval2 = "cxmimo_2x2_svd0.taps";
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
            feedbackState=0;

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

        printf("Initializing %s\n",STAR_NAME);
	/* store as state the number of input/output buffers */
	if((numberRxAntennas = NO_INPUT_BUFFERS()) < 1) {
                fprintf(stderr,"cxmimo_2x2_svd: no input buffers\n");
		return(2);
	}
	if((numberStreams = NO_OUTPUT_BUFFERS()) < 1) {
              fprintf(stderr,"cxmimo_2x2_svd: no output buffers\n");
		return(3);
	}

	if(numberStreams < 2) {
              fprintf(stderr,"cxmimo_2x2_svd: Minimum 2 output Buffers required\n");
		return(3);
	}
        
        /*
         * First output buffer is V matrix feedback
         */
        numberStreams--;

#if 0000
        if(numberStreams != numberTxAntennas) {
               fprintf(stderr,"cxmimo_2x2_svd: output streams must match number Tx antennas fo now.\n");
		return(4);


        }
#endif
 

       fp=fopen(HMatrixFileName,"r");
        if(!fp) {
            fprintf(stderr,"cxmimo_2x2_svd: Could not open H Matrix file %s.\n",HMatrixFileName);
                return(5);
        }

        fscanf(fp,"%d %d %d",&nTx,&nRx, &nTaps);


        if(nTx != numberTxAntennas ) {
            fprintf(stderr,"cxmimo_2x2_svd: Param Tx Antenna does not match in H Matrix file s.\n");
                return(6);

        }

        if(nRx != numberRxAntennas ) {
            fprintf(stderr,"cxmimo_2x2_svd: Rx paths do  not match number of Rx antennas in  H Matrix file s.\n");
                return(7);

        }
        xre_P=(float *)calloc(lengthFFT,sizeof(float));
        xim_P=(float *)calloc(lengthFFT,sizeof(float));

        yre_P=(float *)calloc(lengthFFT,sizeof(float));
        yim_P=(float *)calloc(lengthFFT,sizeof(float));

        if(!xre_P || !xim_P || !yre_P || !yim_P ) {
            fprintf(stderr,"cxmimo_2x2_svd: Could not allocate space.\n");
                return(8);

        }
	for (i=0; i<numberRxAntennas; i++) 
		SET_CELL_SIZE_IN(i,sizeof(complex));

        SET_CELL_SIZE_OUT(0,sizeof(dsp_cxMatrix_t )); //V Matrix Feedback

	for (i=0; i<numberStreams; i++) 
		SET_CELL_SIZE_OUT(i+1,sizeof(complex));



        feedbackState=0;

/*
 * Allocate H matrix Time Domain
 */
h_P=(complex ***) calloc(numberRxAntennas,sizeof(complex**));
if(h_P==NULL) {
           fprintf(stderr,"cxmimo_2x2_svd could not allocate H matrix\n");
	   return(8);

}
for(i=0; i<numberRxAntennas; i++) {

    h_P[i]=(complex **) calloc(numberTxAntennas,sizeof(complex*));
    if(h_P[i]==NULL) {
           fprintf(stderr,"cxmimo_2x2_svd could not allocate H matrix\n");
	   return(9);
    }
    for(j=0; j<numberTxAntennas; j++) {
         h_P[i][j]=(complex *) calloc(lengthFFT,sizeof(complex));
         if(h_P[i]==NULL) {
              fprintf(stderr,"cxmimo_2x2_svd could not allocate H matrix\n");
	     return(10);

         }
    }
}



H_P= Dsp_AllocateCxMatrix(numberRxAntennas,numberTxAntennas);
if(H_P==NULL) {
              fprintf(stderr,"cxmimo_2x2_svd could not allocate single  H matrix\n");
	     return(11);

}




U_P=(dsp_cxMatrix_t **)calloc(lengthFFT,sizeof(dsp_cxMatrix_t *));
if(U_P==NULL) {
              fprintf(stderr,"cxmimo_2x2_svd could not allocate  Matrix U\n");
	     return(15);
}

for(i=0; i<lengthFFT; i++) {
    U_P[i]=Dsp_AllocateCxMatrix(numberRxAntennas,numberRxAntennas);
    if(U_P[i]==NULL) {
              fprintf(stderr,"cxmimo_2x2_svd could not allocate Matrix U\n");
	     return(16);

    }
}

V_P=(dsp_cxMatrix_t **)calloc(lengthFFT,sizeof(dsp_cxMatrix_t *));
if(V_P==NULL) {
              fprintf(stderr,"cxmimo_2x2_svd could not allocate  Matrix U\n");
	     return(17);
}

for(i=0; i<lengthFFT; i++) {
    V_P[i]=Dsp_AllocateCxMatrix(numberTxAntennas,numberTxAntennas);
    if(V_P[i]==NULL) {
              fprintf(stderr,"cxmimo_2x2_svd could not allocate Matrix V\n");
	     return(18);

    }
}
      if(numberRxAntennas > numberTxAntennas)
               len=numberTxAntennas;
           else
               len=numberRxAntennas;




Sigma_P=(doubleVector_t **)calloc(lengthFFT,sizeof(doubleVector_t *));
if(Sigma_P==NULL) {
              fprintf(stderr,"cxmimo_2x2_svd could not allocate  Matrix Sigma\n");
	     return(19);
}

for(i=0; i<lengthFFT; i++) {
    Sigma_P[i]=Dsp_AllocateDoubleVector(len);
    if(Sigma_P[i]==NULL) {
              fprintf(stderr,"cxmimo_2x2_svd could not allocate vector Sigma\n");
	     return(20);

    }
}





x_P=Dsp_AllocateCxVector(numberStreams);
y_P=Dsp_AllocateCxVector(numberRxAntennas);
xx_P=Dsp_AllocateCxVector(numberRxAntennas);

if(!x_P || !y_P || !xx_P) {
              fprintf(stderr,"cxmimo_2x2_svd could not allocate space \n");
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


svr_F=fopen("svr.dat","w");
if(!svr_F) {
            fprintf(stderr,"cxmimo_2x2_svd: Could not open  file svr.dat.\n");
                return(25);
}
for(k=0; k< lengthFFT; k++) {
    // if(k==0 || k >40) continue;
    if(k==0 || (k >26 && k<38) ) continue;
     for(i=0; i< numberRxAntennas ; i++) {
           for(j=0; j<  numberTxAntennas; j++) {

                H_P->matrix_PP[i][j].re=h_P[i][j][k].re;
                H_P->matrix_PP[i][j].im=h_P[i][j][k].im;
           }
     }
 
     Krn_Compute2x2SVDCxMatrix(H_P, Sigma_P[k],U_P[k],V_P[k]);

  //    Krn_TransposeConjugateMatrix(U_P[k]);

 //     Krn_TransposeConjugateMatrix(V_P[k]);


     svr=Sigma_P[k]->vector_P[0]/Sigma_P[k]->vector_P[len-1];

     fprintf(svr_F,"%f\n",svr);
printf("-------------------------------------------------\n");
printf("Singular values for k=%d\n",k);
     Krn_PrintVector(Sigma_P[k],"f", stdout, 0) ;   
printf("-------------------------------------------------\n");
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
fclose(svr_F);

//TODO Free up H_P,HT_P,A_P,Ai_P




   

        count=0;


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 

   if(feedbackState==0) {
        feedbackState=1;
        for(i=0; i<lengthFFT; i++) {
                   if(IT_OUT(0)) {
                         KrnOverflow("cxmimo_2x2_svd",0);
                                return(99);
                    }



                    cxmat.type=V_P[i]->type;
                    cxmat.width=V_P[i]->width;
                    cxmat.height=V_P[i]->height;
                    cxmat.matrix_PP=V_P[i]->matrix_PP;

                    OUTCXMAT(0,0)=cxmat;
        }
   }
 
   for(samples = MIN_AVAIL(); samples >0; --samples) {
          for(iRx=0; iRx<numberRxAntennas; iRx++) {
                 IT_IN(iRx);
                 val = INCX(iRx,0);
                 y_P->vector_P[iRx].re=val.re;
                 y_P->vector_P[iRx].im=val.im;

          }
          k=count;
          if(!(k==0 || (k >26 && k<38) )) {
           
          
               Dsp_MultiplyComplexMatricesComplexVector(U_P[k],y_P,xx_P);

               for(iTx=0; iTx<numberStreams; iTx++) {
                    if(IT_OUT(iTx+1)) {
                         KrnOverflow("cxmimo_2x2_svd",iTx+1);
                                return(99);
                    }
                    val.re=xx_P->vector_P[iTx].re*(1.0/Sigma_P[k]->vector_P[iTx]);
                    val.im=xx_P->vector_P[iTx].im*(1.0/Sigma_P[k]->vector_P[iTx]);
                    OUTCX(iTx+1,0) = val;
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
      Dsp_FreeCpxMatrix((dsp_cpxMatrix_t*)U_P[i]);
      Dsp_FreeCpxMatrix((dsp_cpxMatrix_t*)V_P[i]);
      free(Sigma_P[i]->vector_P);
      free(Sigma_P[i]);

}



break;
}
return(0);
}
