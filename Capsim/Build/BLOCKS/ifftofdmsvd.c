 
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

#include "typedef.h"
#include "anisim.h"
#include "ftab_80211a.h"
#include "mimo.h"


 

#define FFTSIZE 64
#define LARGE_NUMBER_SAMPLES 100000000




/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
      int  __numberStreams;
      int  __numberTxAntennas;
       int   __doneTraining;
       int   __doneSignal;
       int   __ofdmSymbolCount;
       int   __numSymbols;
      int  __feedbackState;
       float   __norm;
       int   __fftl;
       float*   __signalReal;
       float*   __signalImag;
       complex*   __outBuffer;
       complex*   __sig;
       float*   __fftreal;
       float*   __fftimag;
       float*   __fftoutreal;
       float*   __fftoutimag;
       int   __numberOFDMSymbolsToTransmit;
       float**   __fftreal_P;
       float**   __fftimag_P;
       float**   __fftoutreal_P;
       float**   __fftoutimag_P;
      dsp_cxMatrix_t**  __V_P;
      cxVector_t*  __x_P;
      cxVector_t*  __xx_P;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define numberStreams (state_P->__numberStreams)
#define numberTxAntennas (state_P->__numberTxAntennas)
#define  doneTraining  (state_P->__doneTraining)
#define  doneSignal  (state_P->__doneSignal)
#define  ofdmSymbolCount  (state_P->__ofdmSymbolCount)
#define  numSymbols  (state_P->__numSymbols)
#define feedbackState (state_P->__feedbackState)
#define  norm  (state_P->__norm)
#define  fftl  (state_P->__fftl)
#define  signalReal  (state_P->__signalReal)
#define  signalImag  (state_P->__signalImag)
#define  outBuffer  (state_P->__outBuffer)
#define  sig  (state_P->__sig)
#define  fftreal  (state_P->__fftreal)
#define  fftimag  (state_P->__fftimag)
#define  fftoutreal  (state_P->__fftoutreal)
#define  fftoutimag  (state_P->__fftoutimag)
#define  numberOFDMSymbolsToTransmit  (state_P->__numberOFDMSymbolsToTransmit)
#define  fftreal_P  (state_P->__fftreal_P)
#define  fftimag_P  (state_P->__fftimag_P)
#define  fftoutreal_P  (state_P->__fftoutreal_P)
#define  fftoutimag_P  (state_P->__fftoutimag_P)
#define V_P (state_P->__V_P)
#define x_P (state_P->__x_P)
#define xx_P (state_P->__xx_P)

/*         
 *    PARAMETER DEFINES 
 */ 
#define cyclicSamples (param_P[0]->value.d)
#define training (param_P[1]->value.d)
#define signalField (param_P[2]->value.d)
#define length (param_P[3]->value.d)
#define rate (param_P[4]->value.d)
#define numberOFDMSymbols (param_P[5]->value.d)
#define padZeroes (param_P[6]->value.d)
/*-------------- BLOCK CODE ---------------*/
 int  
ifftofdmsvd
(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

	int no_samples;
	complex calc;
	int i;
	int j,k;
        complex val;
        int  iTx;
        int minAvailableStreams;
        dsp_cxMatrix_t cxmat;


switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = "  Cyclic extension samples  ";
     char   *ptype0 = "int";
     char   *pval0 = "16";
     char   *pname0 = "cyclicSamples";
     char   *pdef1 = "  Include training 1=doit, 0 don't  ";
     char   *ptype1 = "int";
     char   *pval1 = "1";
     char   *pname1 = "training";
     char   *pdef2 = "  Include SIGNAL field 1=doit, 0 don't  ";
     char   *ptype2 = "int";
     char   *pval2 = "1";
     char   *pname2 = "signalField";
     char   *pdef3 = "  length of Bytes  ";
     char   *ptype3 = "int";
     char   *pval3 = "100";
     char   *pname3 = "length";
     char   *pdef4 = "  data rate  ";
     char   *ptype4 = "int";
     char   *pval4 = "5";
     char   *pname4 = "rate";
     char   *pdef5 = "  Number of packet.At 64QAM number of bits=numberOFDMSymbols*48*6  ";
     char   *ptype5 = "int";
     char   *pval5 = "10";
     char   *pname5 = "numberOFDMSymbols";
     char   *pdef6 = "  Number of zereos to pad at end of packet ";
     char   *ptype6 = "int";
     char   *pval6 = "100";
     char   *pname6 = "padZeroes";
KrnModelParam(indexModel88,0 ,pdef0,ptype0,pval0,pname0);
KrnModelParam(indexModel88,1 ,pdef1,ptype1,pval1,pname1);
KrnModelParam(indexModel88,2 ,pdef2,ptype2,pval2,pname2);
KrnModelParam(indexModel88,3 ,pdef3,ptype3,pval3,pname3);
KrnModelParam(indexModel88,4 ,pdef4,ptype4,pval4,pname4);
KrnModelParam(indexModel88,5 ,pdef5,ptype5,pval5,pname5);
KrnModelParam(indexModel88,6 ,pdef6,ptype6,pval6,pname6);

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

 

	/* store as state the number of input/output buffers */
	if(( numberStreams= NO_INPUT_BUFFERS()) < 1) {
                fprintf(stderr,"ifftofdmsvd: no input buffers\n");
		return(2);
	}
	if((numberTxAntennas = NO_OUTPUT_BUFFERS()) < 1) {
              fprintf(stderr,"ifftofdmsvd: no output buffers\n");
		return(3);
	}

	if(numberStreams < 2) {
              fprintf(stderr,"ifftofdmsvd: Minimum 2 output Buffers required\n");
		return(3);
	}
    
    
        /*
         * First input buffer is V matrix feedback
         */
         numberStreams--;

        if(numberStreams != numberTxAntennas) {
               fprintf(stderr,"ifftofdmsvd: output streams must match number Tx antennas for now.\n");
		return(4);


        }

  
   fftreal_P=(float **)calloc(numberTxAntennas,sizeof(float*));
   fftimag_P=(float **)calloc(numberTxAntennas,sizeof(float*));
   if(!fftreal_P || ! fftimag_P) {
              fprintf(stderr,"ifftofdmsvd: Could not allocate space\n");
		return(55);

   }
   for(i=0; i<numberTxAntennas; i++) {

       fftreal_P[i]=(float *)calloc(FFTSIZE,sizeof(float));
       if(!fftreal_P[i]) {
              fprintf(stderr,"ifftofdmsvd: Could not allocate space\n");
		return(56);
       }
   }
   for(i=0; i<numberTxAntennas; i++) {

       fftimag_P[i]=(float *)calloc(FFTSIZE,sizeof(float));
       if(!fftimag_P[i]) {
              fprintf(stderr,"ifftofdmsvd: Could not allocate space\n");
		return(57);
       }
   }

   


  if( (outBuffer = (complex*)calloc(FFTSIZE,sizeof(complex))) == NULL ||
   (signalReal = (float*)calloc(FFTSIZE,sizeof(float))) == NULL ||
   (signalImag = (float*)calloc(FFTSIZE,sizeof(float))) == NULL ||
   (sig = (complex*)calloc(FFTSIZE,sizeof(complex))) == NULL ||
   (fftreal = (float*)calloc(FFTSIZE,sizeof(float))) == NULL ||
   (fftimag = (float*)calloc(FFTSIZE,sizeof(float))) == NULL ||
   (fftoutreal = (float*)calloc(FFTSIZE,sizeof(float))) == NULL ||
   (fftoutimag = (float*)calloc(FFTSIZE,sizeof(float))) == NULL) {
           fprintf(stderr,"ifftofdmsvd: can't allocate work space\n");
           return(4);
   }
   numberOFDMSymbolsToTransmit=(int)((float)length/216.+0.5); //54 Mbps
   numberOFDMSymbolsToTransmit=(int)ceil((float)length/216.); //54 Mbps
    doneTraining=0;
    doneSignal=0;
    ofdmSymbolCount=0;
    numSymbols=0;
    norm = 1.0;                   //  /((float)FFTSIZE);
    fftl = FFTSIZE;	
    for(i=0; i<FFTSIZE; i++)
     {
       signalReal[i]=0.0;
       signalImag[i]=0.0;
     }

V_P=(dsp_cxMatrix_t **)calloc(FFTSIZE,sizeof(dsp_cxMatrix_t *));
if(V_P==NULL) {
              fprintf(stderr,"ifftofdmsvd could not allocate  Matrix U\n");
	     return(17);
}

for(i=0; i<FFTSIZE; i++) {
    V_P[i]=Dsp_AllocateCxMatrix(numberTxAntennas,numberTxAntennas);
    if(V_P[i]==NULL) {
              fprintf(stderr,"ifftofdmsvd could not allocate Matrix V\n");
	     return(18);

    }
}

x_P=Dsp_AllocateCxVector(numberTxAntennas);
xx_P=Dsp_AllocateCxVector(numberTxAntennas);

     feedbackState=0;

     SET_CELL_SIZE_IN(0,sizeof(dsp_cxMatrix_t));

	for (i=0; i<numberStreams; i++) 
		SET_CELL_SIZE_IN(i+1,sizeof(complex));
	for (i=0; i< numberTxAntennas; i++) 
		SET_CELL_SIZE_OUT(i,sizeof(complex));




break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 

if(!feedbackState) {
   
   k=0;
   while(IT_IN(0)) {
        cxmat=INCXMAT(0,0);
        
        printf("FEEDBACK sample number=%d\n",k);
        feedbackState=1;
        Krn_PrintCxMatrix(&cxmat,"f", stdout);
        if(k >= FFTSIZE)continue;
                           V_P[k]->type=cxmat.type;
                           V_P[k]->width=cxmat.width;
                           V_P[k]->height=cxmat.height;
                           V_P[k]->matrix_PP=cxmat.matrix_PP;
        k++;
   }
}
if(!feedbackState) return(0);

minAvailableStreams=LARGE_NUMBER_SAMPLES;
for (i=0; i<numberStreams; i++) {
          k=AVAIL(i+1);
          if (k<minAvailableStreams) minAvailableStreams=k;
//          printf("minAvailableStreams=%d\n",minAvailableStreams);
}
for (no_samples = minAvailableStreams; no_samples>0; --no_samples)
// for (no_samples = MIN_AVAIL();no_samples>0; --no_samples)
{

  

           


   if(training && !doneTraining) {
        doneTraining=1;
        for(iTx=0; iTx<numberTxAntennas; iTx++) {


                 
                 	
              for(i=0; i<FFTSIZE; i++) {          /* load short training sequence  */
    
			        fftreal[i] = shortTrain_TableRe[i];
					fftimag[i] = shortTrain_TableIm[i]; 
               }

            /* End of short training sequence */
            /*
             * perform inverse fft calculation
            */



          

                 fftofdm54(fftreal,fftimag,fftoutreal,fftoutimag,fftl,-1);  

				 for(i=0; i<fftl; i++)
						  {
						   outBuffer[i].re = fftoutreal[i];
						   outBuffer[i].im = fftoutimag[i];
						  }

             /*
             *  output data first 64 points then repeat until 160 samples (8 microseconds at 20 Ms/s)
             */

             /*
             * first 64 samples
             */

             /*
             * apply window  : w(k) = 0.5(k==0);1(1<=k<160);0.5(k==160)
             */

                if(IT_OUT(iTx)) {
                     KrnOverflow("ifftofdmsvd",0);
                     return(99);
                 }

               calc.re = outBuffer[0].re*norm*0.5;
	       calc.im = outBuffer[0].im*norm*0.5;
	//       printf("short preamble %d %f %f\n",0,calc.re,calc.im);
	       OUTCX(iTx,0)=calc;
	
	       for (i=1; i<FFTSIZE; i++)
                 {
                     if(IT_OUT(iTx)) {
                         KrnOverflow("ifftofdmsvd",0);
                         return(99);
                     }
                     calc.re = outBuffer[i].re*norm;
                     calc.im = outBuffer[i].im*norm;
        //             printf("short preamble %d %f %f\n",i,calc.re,calc.im);
                     OUTCX(iTx,0)=calc;

                 }
	
	       /*
                * second 64  samples (128)
               */

                 for (i=0; i<FFTSIZE; i++)
                 {
                     if(IT_OUT(iTx)) {
                         KrnOverflow("ifftofdmsvd",0);
                         return(99);
                     }
                     calc.re = outBuffer[i].re*norm;
                     calc.im = outBuffer[i].im*norm;
       //               printf("short preamble %d %f %f\n",i,calc.re,calc.im);
                     OUTCX(iTx,0)=calc;

                 }

               /*
               *  the last 33  samples (161)
               */

               for (i=0; i<32; i++)
                 {
                     if(IT_OUT(iTx)) {
                         KrnOverflow("ifftofdmsvd",0);
                         return(99);
                     }
                     calc.re = outBuffer[i].re*norm;
                     calc.im = outBuffer[i].im*norm;
     //                printf("short preamble %d %f %f\n",i,calc.re,calc.im);
                     OUTCX(iTx,0)=calc;

                 }

               /*
                * apply window to the 161th sample.
               */
              /*   if(IT_OUT(0)) {
                         KrnOverflow("ifft",0);
                         return(99);
                 }

               */
                 calc.re = outBuffer[0].re*norm*0.5;
                 calc.im = outBuffer[0].im*norm*0.5;


                /*
                 * now create the long training sequence and overlapping the last sample of
                   short training sequence with the first sample of long training sequence
                */

                for(i=0; i< FFTSIZE; i++) {
  
			          fftreal[i] = longTrain_TableRe[i];
					  fftimag[i] = longTrain_TableIm[i];
                }

                /*
                 * perform inverse fft calculation for long sequence
                */

             

			     fftofdm54(fftreal,fftimag,fftoutreal,fftoutimag,fftl,-1);


                for(i=0; i<fftl; i++)
		{
						   outBuffer[i].re = fftoutreal[i];
						   outBuffer[i].im = fftoutimag[i];
		}
                /*
                 *  output cyclic prefix for long training sequence: put the last 32 samples
                    of 64 samples at first and then put two 64 samples
                */

                for (i=0; i<32; i++)
                {
                    if(IT_OUT(iTx)) {
                       KrnOverflow("ifftofdmsvd",0);
                       return(99);
                    }

                    j = FFTSIZE + i - 32;

                    if(i==0) {
                        calc.re = calc.re + 0.5*outBuffer[j].re*norm;
                        calc.im = calc.im + 0.5*outBuffer[j].im*norm;

                       }
                    else {
                        calc.re = outBuffer[j].re*norm;
                        calc.im = outBuffer[j].im*norm;
                       }
         //           printf("long preamble %d %f %f\n",i,calc.re,calc.im);
                    OUTCX(iTx,0)=calc;

                   }

                /*
                 *  now add first 64 samples
                */



                 for (i=0; i<FFTSIZE; i++)
                 {
                    if(IT_OUT(iTx)) {
                       KrnOverflow("ifftofdmsvd",0);
                       return(99);
                    }
                    calc.re = outBuffer[i].re*norm;
                    calc.im = outBuffer[i].im*norm;
       //             printf("long preamble %d %f %f\n",i,calc.re,calc.im);
                    OUTCX(iTx,0)=calc;

                 }

                /*
                 *  now add second 64 samples  (160)
                */

                for (i=0; i<FFTSIZE; i++)
                 {
                    if(IT_OUT(iTx)) {
                       KrnOverflow("ifftofdmsvd",0);
                       return(99);
                    }
                    calc.re = outBuffer[i].re*norm;
                    calc.im = outBuffer[i].im*norm;
       //             printf("long preamble %d %f %f\n",i,calc.re,calc.im);
                    OUTCX(iTx,0)=calc;

                 }

               /*
                *   apply the window to the 161th sample
               */
              /*    if(IT_OUT(0)) {
                         KrnOverflow("ifft",0);
                         return(99);
                 }

               */

                   calc.re = outBuffer[0].re*norm*0.5;
                   calc.im = outBuffer[0].im*norm*0.5;        /* this will overlap with the first sample in SIGNAL field   */


          }   /* end training */

          /* add SIGNAL filed here, we temporarily skip over SIGNAL field  */

          if(signalField && !doneSignal)
           {
              doneSignal=1;

              signalPacket(rate,length,0,signalReal,signalImag);

              for (i=0; i<FFTSIZE; i++)
               {
                 sig[i].re = signalReal[i];
                 sig[i].im = signalImag[i];
               }



            /* do the cyclic extention  */

               for (i=0; i<cyclicSamples; i++)
                {
                  j = FFTSIZE + i - 16;

                  if(IT_OUT(iTx)) {
                       KrnOverflow("ifftofdmsvd",0);
                       return(99);
                    }

                  if(i==0)
                   {
                     calc.re = calc.re + 0.5*sig[j].re;
                     calc.im = calc.im + 0.5*sig[j].im;

                    }
                  else
                    {
                     calc.re = sig[j].re;
                     calc.im = sig[j].im;
                    }
    //               printf("signal %d %f %f\n",i,calc.re,calc.im);
                    OUTCX(iTx,0) = calc;
                }

              /* add 64 more complex samples  */

               for(i=0; i<FFTSIZE; i++)
                {
                   if(IT_OUT(iTx)) {
                       KrnOverflow("ifftofdmsvd",0);
                       return(99);
                    }
                    calc.re = sig[i].re;
                    calc.im = sig[i].im;
    //                printf("signal %d %f %f\n",i,calc.re,calc.im);
                    OUTCX(iTx,0)=calc;

                }

                  calc.re = sig[0].re*0.5;
                  calc.im = sig[0].im*0.5;        /* this will overlap with the first sample in data field   */


       }  /* end of SIGNAL field   */



    } // end iteration over iTx

          /*
           * now data field  after SIGNAL
          */

   //        calc.re = 0.0;
   //        calc.im = 0.0;        /* these two lines will be removed when the SIGNAL is added  */

           

//HHHHHHHEEEEEERRRRRRR

    for(iTx=0; iTx<numberTxAntennas; iTx++) {
             IT_IN(iTx+1);
             val=INCX(iTx+1,0);
             fftreal_P[iTx][numSymbols] = val.re;
	     fftimag_P[iTx][numSymbols] = val.im; 
//  printf("INPUTING iTx=%d\n",iTx);           
    }          
    numSymbols++;          

    if (numSymbols == FFTSIZE)
    {
              printf("SYMBOL numSymbols=%d  symbolCount=%d\n",numSymbols,ofdmSymbolCount);
              numSymbols = 0;

              /*
               * Do Beam Forming xx=Vx
               */
              for(i=0; i<fftl; i++) {
                    for(k=0; k<numberTxAntennas; k++) {
                                 x_P->vector_P[k].re=fftreal_P[k][i];
                                 x_P->vector_P[k].im=fftimag_P[k][i];
                    }
                    Dsp_MultiplyComplexMatricesComplexVector(V_P[i],x_P,xx_P);

                    for(k=0; k<numberTxAntennas; k++) {
                                 fftreal_P[k][i]=xx_P->vector_P[k].re;
                                 fftimag_P[k][i]=xx_P->vector_P[k].im;
                    }
  

              }




              for(iTx=0; iTx<numberTxAntennas; iTx++) {

 printf("Computing iTx=%d\n",iTx);                 

              /* perform the inverse FFT  */
     //         printf("IFFT54 performing IFFF\n");
     



	           
                fftofdm54(fftreal_P[iTx],fftimag_P[iTx],fftoutreal,fftoutimag,fftl,-1);

                 for(i=0; i<fftl; i++)
		{
				outBuffer[i].re = fftoutreal[i];
				outBuffer[i].im = fftoutimag[i];
		}


              /*
               *  output data, the first sample should overlap with the last
                  sample of SIGNAL. Since we skip over the SIGNAL part, we
                  don't do overlap at the first sample of OFDM symbols. The
                  overlap will be done later. Just don't forget to add theis
                  overlap once the SIGNAL is added here.
               */
          /*      for(i=0;i <FFTSIZE; i++) {

		   printf("IFFTOUTPUT %d %f %f\n",i, outBuffer[i].re,outBuffer[i].im);
		 }
		
          */		

               if(cyclicSamples) {
                   for (i=0; i<cyclicSamples; i++)
	           {
                          if(IT_OUT(iTx)) {
	                      KrnOverflow("ifftofdmsvd",0);
	                      return(99);
                             }
                       j = FFTSIZE + i - cyclicSamples;

                       if (i==0)
                       {
                          calc.re = calc.re + outBuffer[j].re*norm*0.5;
	                      calc.im = calc.im + outBuffer[j].im*norm*0.5;
                         }
                       else
                         {
	                   calc.re = outBuffer[j].re*norm;
	                   calc.im = outBuffer[j].im*norm;
	                 }
	
	//               printf("IFFTOUTPUT %d %f %f\n",i,calc.re,calc.im);

                       OUTCX(iTx,0)=calc;
	               

	            }
                 }

              /*
               * then 64 output samples (80 samples)
              */

              for (i=0; i<FFTSIZE; i++)
	       {
	          if(IT_OUT(iTx)) {
	             KrnOverflow("ifftofdmsvd",0);
	             return(99);
	            }

	          calc.re = outBuffer[i].re*norm;
	          calc.im = outBuffer[i].im*norm;
	
//	          printf("IFFTOUTPUT %d %f %f\n",i,calc.re,calc.im);
                  OUTCX(iTx,0)=calc;
	          

	        }
	
	       /*
	        *  apply the window to the 81th sample and the 81th sample will
	           overlap with the first sample of next OFDM symbol(80 samples)
	       */
	    /*      if(IT_OUT(0)) {
	             KrnOverflow("ifft",0);
	             return(99);
	            }
             */
	          calc.re = outBuffer[0].re*norm*0.5;
	          calc.im = outBuffer[0].im*norm*0.5;
	
	     } // end iTx for output
	
	        ofdmSymbolCount++;
	        if(ofdmSymbolCount == numberOFDMSymbols) {
                  /*
                   * start another packet and the training preambles
                  */
                             ofdmSymbolCount=0;
                             doneTraining=0;
                             doneSignal=0;
                  }
           

    } /* end of symbol */
	  
	  if(ofdmSymbolCount >= numberOFDMSymbolsToTransmit) {
             for(iTx=0; iTx<numberTxAntennas; iTx++) {	  
                for (i=0; i<padZeroes; i++)
	        {
	             if(IT_OUT(iTx)) {
	                 KrnOverflow("ifftofdmsvd",0);
	                 return(99);
	             }

	             calc.re = 0;
	             calc.im = 0;
	             OUTCX(iTx,0)=calc;
	          

	        }
             } // iTx	  
	  }
       
      
    }

    return(0);




break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 

	/*
	 * free up allocated space
 	 */
	 
   free(outBuffer);
   free(signalReal);
   free(sig);
   free(fftreal);
   free(fftimag);
   free(fftoutreal);
   free(fftoutimag);
   

break;
}
return(0);
}
