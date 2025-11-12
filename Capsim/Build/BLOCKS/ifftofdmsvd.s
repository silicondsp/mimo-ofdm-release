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

<BLOCK_NAME>
ifftofdmsvd
</BLOCK_NAME> 

<COMMENTS>
<![CDATA[ 

/*
File:                   ifft54.s
Description:
      includes the training sequences, cyclic extention and windowing.
programmer:     Sasan, Ardalan, Bin Huang
date:           10/9/01
revised by:     Bin Huang
date:           7/22/02
Updated for SVD MIMO Sasan Ardalan July 22, 2007
*/
]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 


#include <tcl.h>
//#include <vectors.h>
#include "matrixBuffers.h"

#include "typedef.h"
#include "anisim.h"
#include "ftab_80211a.h"
#include "mimo.h"

]]>
</INCLUDES> 

<DEFINES> 

#define FFTSIZE 64
#define LARGE_NUMBER_SAMPLES 100000000



</DEFINES> 

<DECLARATIONS> 

	int no_samples;
	complex calc;
	int i;
	int j,k;
        complex val;
        int  iTx;
        int minAvailableStreams;
        dsp_cxMatrix_t cxmat;

</DECLARATIONS> 




<STATES>

	<STATE>
		<TYPE>int</TYPE>
		<NAME>numberStreams</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>numberTxAntennas</NAME>
	</STATE>


	<STATE>
		<TYPE> int </TYPE>
		<NAME> doneTraining </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> doneSignal </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> ofdmSymbolCount </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> numSymbols </NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>feedbackState</NAME>
                <VALUE>0</VALUE>
	</STATE>


	<STATE>
		<TYPE> float </TYPE>
		<NAME> norm </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> fftl </NAME>
	</STATE>
	<STATE>
		<TYPE> float* </TYPE>
		<NAME> signalReal </NAME>
	</STATE>
	<STATE>
		<TYPE> float* </TYPE>
		<NAME> signalImag </NAME>
	</STATE>
	<STATE>
		<TYPE> complex* </TYPE>
		<NAME> outBuffer </NAME>
	</STATE>
	<STATE>
		<TYPE> complex* </TYPE>
		<NAME> sig </NAME>
	</STATE>
	<STATE>
		<TYPE> float* </TYPE>
		<NAME> fftreal </NAME>
	</STATE>
	<STATE>
		<TYPE> float* </TYPE>
		<NAME> fftimag </NAME>
	</STATE>
	<STATE>
		<TYPE> float* </TYPE>
		<NAME> fftoutreal </NAME>
	</STATE>
	<STATE>
		<TYPE> float* </TYPE>
		<NAME> fftoutimag </NAME>
	</STATE>
	
	<STATE>
		<TYPE> int </TYPE>
		<NAME> numberOFDMSymbolsToTransmit </NAME>
	</STATE>
	
	<STATE>
		<TYPE> float** </TYPE>
		<NAME> fftreal_P </NAME>
	</STATE>
	<STATE>
		<TYPE> float** </TYPE>
		<NAME> fftimag_P </NAME>
	</STATE>
	<STATE>
		<TYPE> float** </TYPE>
		<NAME> fftoutreal_P </NAME>
	</STATE>
	<STATE>
		<TYPE> float** </TYPE>
		<NAME> fftoutimag_P </NAME>
	</STATE>	
	<STATE>
		<TYPE>dsp_cxMatrix_t**</TYPE>
		<NAME>V_P</NAME>
	</STATE>
	<STATE>
		<TYPE>cxVector_t*</TYPE>
		<NAME>x_P</NAME>
	</STATE>

	<STATE>
		<TYPE>cxVector_t*</TYPE>
		<NAME>xx_P</NAME>
	</STATE>
	
</STATES>



<PARAMETERS>
	<PARAM>
		<DEF>  Cyclic extension samples  </DEF>
		<TYPE> int </TYPE>
		<NAME> cyclicSamples </NAME>
		<VALUE> 16 </VALUE>
	</PARAM>
	<PARAM>
		<DEF>  Include training 1=doit, 0 don't  </DEF>
		<TYPE> int </TYPE>
		<NAME> training </NAME>
		<VALUE> 1 </VALUE>
	</PARAM>
	<PARAM>
		<DEF>  Include SIGNAL field 1=doit, 0 don't  </DEF>
		<TYPE> int </TYPE>
		<NAME> signalField </NAME>
		<VALUE> 1 </VALUE>
	</PARAM>
	<PARAM>
		<DEF>  length of Bytes  </DEF>
		<TYPE> int </TYPE>
		<NAME> length </NAME>
		<VALUE> 100 </VALUE>
	</PARAM>
	<PARAM>
		<DEF>  data rate  </DEF>
		<TYPE> int </TYPE>
		<NAME> rate </NAME>
		<VALUE> 5 </VALUE>
	</PARAM>
	<PARAM>
		<DEF>  Number of packet.At 64QAM number of bits=numberOFDMSymbols*48*6  </DEF>
		<TYPE> int </TYPE>
		<NAME> numberOFDMSymbols </NAME>
		<VALUE> 10 </VALUE>
	</PARAM>
	<PARAM>
		<DEF>  Number of zereos to pad at end of packet </DEF>
		<TYPE> int </TYPE>
		<NAME> padZeroes </NAME>
		<VALUE> 100 </VALUE>
	</PARAM>	
	
</PARAMETERS>




<INIT_CODE>
<![CDATA[ 

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



]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 

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



]]>
</MAIN_CODE> 

<WRAPUP_CODE>
<![CDATA[ 

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
   
]]>
</WRAPUP_CODE> 



</BLOCK> 

