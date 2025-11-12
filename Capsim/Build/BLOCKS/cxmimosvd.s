<BLOCK>
<LICENSE>

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


</LICENSE>

<BLOCK_NAME>cxmimosvd</BLOCK_NAME> 

<COMMENTS>
<![CDATA[ 

/* cxmimosvd.s */
/***********************************************************************
                             cxmimosvd()
************************************************************************
T
<NAME>
cxmimosvd
</NAME>
<DESC_SHORT>
This block implements a mimo  decoder using SVD. Output V matrix and Singular Values on buffers.
</DESC_SHORT>
<DESCRIPTION>
</DESCRIPTION>
<PROGRAMMERS>
Date:  June 30, 2007 
Programmer: Sasan Ardalan
Modified: Sasan Ardalan July 21, 2007
</PROGRAMMERS>
*/

]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 

#include <tcl.h>
//#include <vectors.h>
#include "matrixBuffers.h"
#include "mimo.h"


]]>
</INCLUDES> 

<DEFINES> 


#define MAX_TAPS 1024

</DEFINES> 


<PARAMETERS>
<PARAM>
	<DEF>Number of Transmit Antennas</DEF>
	<TYPE>int</TYPE>
	<NAME>numberTxAntennas</NAME>
	<VALUE>2</VALUE>
</PARAM>
<PARAM>
	<DEF>FFT Length</DEF>
	<TYPE>int</TYPE>
	<NAME>lengthFFT</NAME>
	<VALUE>64</VALUE>
</PARAM>
<PARAM>
	<DEF>File Name with Channel H Matrix</DEF>
	<TYPE>file</TYPE>
	<NAME>HMatrixFileName</NAME>
	<VALUE>cxmimosvd0.taps</VALUE>
</PARAM>
</PARAMETERS>
     

<STATES>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>Ndiv2</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>nTaps</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>numberStreams</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>numberRxAntennas</NAME>
	</STATE>
	<STATE>
		<TYPE>complex***</TYPE>
		<NAME>h_P</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>feedbackState</NAME>
                <VALUE>0</VALUE>
	</STATE>

	<STATE>
		<TYPE>cxVector_t*</TYPE>
		<NAME>x_P</NAME>
	</STATE>
	<STATE>
		<TYPE>cxVector_t*</TYPE>
		<NAME>xx_P</NAME>
	</STATE>



	<STATE>
		<TYPE>cxVector_t*</TYPE>
		<NAME>y_P</NAME>
	</STATE>

	<STATE>
		<TYPE>int</TYPE>
		<NAME>count</NAME>
	</STATE>
	<STATE>
		<TYPE>dsp_cxMatrix_t**</TYPE>
		<NAME>U_P</NAME>
	</STATE>
	<STATE>
		<TYPE>doubleVector_t**</TYPE>
		<NAME>Sigma_P</NAME>
	</STATE>
	<STATE>
		<TYPE>dsp_cxMatrix_t**</TYPE>
		<NAME>V_P</NAME>
	</STATE>

	
</STATES>
 
<DECLARATIONS> 

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
 	
</DECLARATIONS> 

       


    


 
<INIT_CODE>
<![CDATA[ 

        printf("Initializing %s\n",STAR_NAME);
	/* store as state the number of input/output buffers */
	if((numberRxAntennas = NO_INPUT_BUFFERS()) < 1) {
                fprintf(stderr,"cxmimosvd: no input buffers\n");
		return(2);
	}
	if((numberStreams = NO_OUTPUT_BUFFERS()) < 1) {
              fprintf(stderr,"cxmimosvd: no output buffers\n");
		return(3);
	}

	if(numberStreams < 2) {
              fprintf(stderr,"cxmimosvd: Minimum 2 output Buffers required\n");
		return(3);
	}
        
        /*
         * First output buffer is V matrix feedback
         */
        numberStreams--;

#if 0000
        if(numberStreams != numberTxAntennas) {
               fprintf(stderr,"cxmimosvd: output streams must match number Tx antennas fo now.\n");
		return(4);


        }
#endif
 

       fp=fopen(HMatrixFileName,"r");
        if(!fp) {
            fprintf(stderr,"cxmimosvd: Could not open H Matrix file %s.\n",HMatrixFileName);
                return(5);
        }

        fscanf(fp,"%d %d %d",&nTx,&nRx, &nTaps);


        if(nTx != numberTxAntennas ) {
            fprintf(stderr,"cxmimosvd: Param Tx Antenna does not match in H Matrix file s.\n");
                return(6);

        }

        if(nRx != numberRxAntennas ) {
            fprintf(stderr,"cxmimosvd: Rx paths do  not match number of Rx antennas in  H Matrix file s.\n");
                return(7);

        }
        xre_P=(float *)calloc(lengthFFT,sizeof(float));
        xim_P=(float *)calloc(lengthFFT,sizeof(float));

        yre_P=(float *)calloc(lengthFFT,sizeof(float));
        yim_P=(float *)calloc(lengthFFT,sizeof(float));

        if(!xre_P || !xim_P || !yre_P || !yim_P ) {
            fprintf(stderr,"cxmimosvd: Could not allocate space.\n");
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
           fprintf(stderr,"cxmimosvd could not allocate H matrix\n");
	   return(8);

}
for(i=0; i<numberRxAntennas; i++) {

    h_P[i]=(complex **) calloc(numberTxAntennas,sizeof(complex*));
    if(h_P[i]==NULL) {
           fprintf(stderr,"cxmimosvd could not allocate H matrix\n");
	   return(9);
    }
    for(j=0; j<numberTxAntennas; j++) {
         h_P[i][j]=(complex *) calloc(lengthFFT,sizeof(complex));
         if(h_P[i]==NULL) {
              fprintf(stderr,"cxmimosvd could not allocate H matrix\n");
	     return(10);

         }
    }
}



H_P= Dsp_AllocateCxMatrix(numberRxAntennas,numberTxAntennas);
if(H_P==NULL) {
              fprintf(stderr,"cxmimosvd could not allocate single  H matrix\n");
	     return(11);

}




U_P=(dsp_cxMatrix_t **)calloc(lengthFFT,sizeof(dsp_cxMatrix_t *));
if(U_P==NULL) {
              fprintf(stderr,"cxmimosvd could not allocate  Matrix U\n");
	     return(15);
}

for(i=0; i<lengthFFT; i++) {
    U_P[i]=Dsp_AllocateCxMatrix(numberRxAntennas,numberRxAntennas);
    if(U_P[i]==NULL) {
              fprintf(stderr,"cxmimosvd could not allocate Matrix U\n");
	     return(16);

    }
}

V_P=(dsp_cxMatrix_t **)calloc(lengthFFT,sizeof(dsp_cxMatrix_t *));
if(V_P==NULL) {
              fprintf(stderr,"cxmimosvd could not allocate  Matrix U\n");
	     return(17);
}

for(i=0; i<lengthFFT; i++) {
    V_P[i]=Dsp_AllocateCxMatrix(numberTxAntennas,numberTxAntennas);
    if(V_P[i]==NULL) {
              fprintf(stderr,"cxmimosvd could not allocate Matrix V\n");
	     return(18);

    }
}
      if(numberRxAntennas > numberTxAntennas)
               len=numberTxAntennas;
           else
               len=numberRxAntennas;




Sigma_P=(doubleVector_t **)calloc(lengthFFT,sizeof(doubleVector_t *));
if(Sigma_P==NULL) {
              fprintf(stderr,"cxmimosvd could not allocate  Matrix Sigma\n");
	     return(19);
}

for(i=0; i<lengthFFT; i++) {
    Sigma_P[i]=Dsp_AllocateDoubleVector(len);
    if(Sigma_P[i]==NULL) {
              fprintf(stderr,"cxmimosvd could not allocate vector Sigma\n");
	     return(20);

    }
}





x_P=Dsp_AllocateCxVector(numberStreams);
y_P=Dsp_AllocateCxVector(numberRxAntennas);
xx_P=Dsp_AllocateCxVector(numberRxAntennas);

if(!x_P || !y_P || !xx_P) {
              fprintf(stderr,"cxmimosvd could not allocate space \n");
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

#if 111

free(xre_P);
free(xim_P);
free(yre_P);
free(yim_P);

#endif
 


svr_F=fopen("svr.dat","w");
if(!svr_F) {
            fprintf(stderr,"cxmimosvd: Could not open  file svr.dat.\n");
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
 
     Krn_ComputeSVDCxMatrix(H_P, Sigma_P[k],U_P[k],V_P[k]);
     
     printf("SVD  H\n");
     PrintCxMatrix(H_P);
     printf("SVD FXP  %f    %f\n\n", Sigma_P[k]->vector_P[0], Sigma_P[k]->vector_P[len-1]);
     printf("SVD  U\n");
     PrintCxMatrix(U_P[k]);
     printf("SVD  V\n");
     PrintCxMatrix(V_P[k]);
     

     Krn_TransposeConjugateMatrix(U_P[k]);

     Krn_TransposeConjugateMatrix(V_P[k]);


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

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 

   if(feedbackState==0) {
        feedbackState=1;
        for(i=0; i<lengthFFT; i++) {
                   if(IT_OUT(0)) {
                         KrnOverflow("cxmimosvd",0);
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
                         KrnOverflow("cxmimosvd",iTx+1);
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

]]>
</MAIN_CODE> 

<WRAPUP_CODE>
<![CDATA[ 
#if 00
for(i=0;i<lengthFFT; i++) {
      Dsp_FreeCpxMatrix((dsp_cpxMatrix_t*)U_P[i]);
      Dsp_FreeCpxMatrix((dsp_cpxMatrix_t*)V_P[i]);
      free(Sigma_P[i]->vector_P);
      free(Sigma_P[i]);
}

#endif

]]>
</WRAPUP_CODE> 



</BLOCK> 

