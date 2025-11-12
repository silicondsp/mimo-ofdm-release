<BLOCK>
<LICENSE>


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

</LICENSE>

<BLOCK_NAME>
ifftofdm54
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
*/
]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 

#include <math.h>

#include "typedef.h"
#include "anisim.h"
#include "ftab_80211a.h"

]]>
</INCLUDES> 

<DEFINES> 

#define FFTSIZE 64

</DEFINES> 

<DECLARATIONS> 

	int no_samples;
	complex calc;
	int i;
	int j;


</DECLARATIONS> 




<STATES>
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



<INPUT_BUFFERS>
	<BUFFER>
		<TYPE> complex </TYPE>
		<NAME> x </NAME>
	</BUFFER>
</INPUT_BUFFERS>



<OUTPUT_BUFFERS>
	<BUFFER>
		<TYPE> complex </TYPE>
		<NAME> y </NAME>
	</BUFFER>
</OUTPUT_BUFFERS>

<INIT_CODE>
<![CDATA[ 



  if( (outBuffer = (complex*)calloc(FFTSIZE,sizeof(complex))) == NULL ||
   (signalReal = (float*)calloc(FFTSIZE,sizeof(float))) == NULL ||
   (signalImag = (float*)calloc(FFTSIZE,sizeof(float))) == NULL ||
   (sig = (complex*)calloc(FFTSIZE,sizeof(complex))) == NULL ||
   (fftreal = (float*)calloc(FFTSIZE,sizeof(float))) == NULL ||
   (fftimag = (float*)calloc(FFTSIZE,sizeof(float))) == NULL ||
   (fftoutreal = (float*)calloc(FFTSIZE,sizeof(float))) == NULL ||
   (fftoutimag = (float*)calloc(FFTSIZE,sizeof(float))) == NULL) {
   fprintf(stderr,"ifftofdm54: can't allocate work space\n");
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
    SET_CELL_SIZE_IN(0,sizeof(complex));
    SET_CELL_SIZE_OUT(0,sizeof(complex));

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 



for (no_samples = MIN_AVAIL();no_samples>0; --no_samples)
  {

	  if(training && !doneTraining) {
                 doneTraining=1;
                 	
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

                if(IT_OUT(0)) {
                     KrnOverflow("ifftofdm54",0);
                     return(99);
                 }

               calc.re = outBuffer[0].re*norm*0.5;
	       calc.im = outBuffer[0].im*norm*0.5;
	//       printf("short preamble %d %f %f\n",0,calc.re,calc.im);
	       y(0)=calc;
	
	       for (i=1; i<FFTSIZE; i++)
                 {
                     if(IT_OUT(0)) {
                         KrnOverflow("ifftofdm54",0);
                         return(99);
                     }
                     calc.re = outBuffer[i].re*norm;
                     calc.im = outBuffer[i].im*norm;
        //             printf("short preamble %d %f %f\n",i,calc.re,calc.im);
                     y(0)=calc;

                 }
	
	       /*
                * second 64  samples (128)
               */

                 for (i=0; i<FFTSIZE; i++)
                 {
                     if(IT_OUT(0)) {
                         KrnOverflow("ifftofdm54",0);
                         return(99);
                     }
                     calc.re = outBuffer[i].re*norm;
                     calc.im = outBuffer[i].im*norm;
       //               printf("short preamble %d %f %f\n",i,calc.re,calc.im);
                     y(0)=calc;

                 }

               /*
               *  the last 33  samples (161)
               */

               for (i=0; i<32; i++)
                 {
                     if(IT_OUT(0)) {
                         KrnOverflow("ifftofdm54",0);
                         return(99);
                     }
                     calc.re = outBuffer[i].re*norm;
                     calc.im = outBuffer[i].im*norm;
     //                printf("short preamble %d %f %f\n",i,calc.re,calc.im);
                     y(0)=calc;

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
                    of 64 samples at first anf then put two 64 samples
                */

                for (i=0; i<32; i++)
                 {
                    if(IT_OUT(0)) {
                       KrnOverflow("ifftofdm54",0);
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
                    y(0)=calc;

                   }

                /*
                 *  now add first 64 samples
                */



                 for (i=0; i<FFTSIZE; i++)
                 {
                    if(IT_OUT(0)) {
                       KrnOverflow("ifftofdm54",0);
                       return(99);
                    }
                    calc.re = outBuffer[i].re*norm;
                    calc.im = outBuffer[i].im*norm;
       //             printf("long preamble %d %f %f\n",i,calc.re,calc.im);
                    y(0)=calc;

                 }

                /*
                 *  now add second 64 samples  (160)
                */

                for (i=0; i<FFTSIZE; i++)
                 {
                    if(IT_OUT(0)) {
                       KrnOverflow("ifftofdm54",0);
                       return(99);
                    }
                    calc.re = outBuffer[i].re*norm;
                    calc.im = outBuffer[i].im*norm;
       //             printf("long preamble %d %f %f\n",i,calc.re,calc.im);
                    y(0)=calc;

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

                  if(IT_OUT(0)) {
                       KrnOverflow("ifftofdm54",0);
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
                    y(0) = calc;
                }

              /* add 64 more complex samples  */

               for(i=0; i<FFTSIZE; i++)
                {
                   if(IT_OUT(0)) {
                       KrnOverflow("ifftofdm54",0);
                       return(99);
                    }
                    calc.re = sig[i].re;
                    calc.im = sig[i].im;
    //                printf("signal %d %f %f\n",i,calc.re,calc.im);
                    y(0)=calc;

                }

                  calc.re = sig[0].re*0.5;
                  calc.im = sig[0].im*0.5;        /* this will overlap with the first sample in data field   */


       }  /* end of SIGNAL field   */

          /*
           * now data field  after SIGNAL
          */

   //        calc.re = 0.0;
   //        calc.im = 0.0;        /* these two lines will be removed when the SIGNAL is added  */

           IT_IN(0);
 
             fftreal[numSymbols] = x(0).re;
			 fftimag[numSymbols] = x(0).im; 
           
              numSymbols++;
           if (numSymbols == FFTSIZE)
             {

                numSymbols = 0;

              /* perform the inverse FFT  */
     //         printf("IFFT54 performing IFFF\n");
     

	           
                fftofdm54(fftreal,fftimag,fftoutreal,fftoutimag,fftl,-1);

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
                          if(IT_OUT(0)) {
	                      KrnOverflow("ifftofdm54",0);
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
	               y(0) = calc;

	               }
                 }

              /*
               * then 64 output samples (80 samples)
              */

              for (i=0; i<FFTSIZE; i++)
	       {
	          if(IT_OUT(0)) {
	             KrnOverflow("ifftofdm54",0);
	             return(99);
	            }

	          calc.re = outBuffer[i].re*norm;
	          calc.im = outBuffer[i].im*norm;
	
//	          printf("IFFTOUTPUT %d %f %f\n",i,calc.re,calc.im);
	          y(0) = calc;

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
	  
             for (i=0; i<padZeroes; i++)
	     {
	          if(IT_OUT(0)) {
	             KrnOverflow("ifftofdm54",0);
	             return(99);
	            }

	          calc.re = 0;
	          calc.im = 0;
	
	          y(0) = calc;

	     }	  
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

