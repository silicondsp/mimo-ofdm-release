 
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

#include "typedef.h"
#include "anisim.h"
#include "ftab_80211a.h"


 

#define FFTSIZE 64


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
       int   __doneTraining;
       int   __doneSignal;
       int   __ofdmSymbolCount;
       int   __numSymbols;
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
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define  doneTraining  (state_P->__doneTraining)
#define  doneSignal  (state_P->__doneSignal)
#define  ofdmSymbolCount  (state_P->__ofdmSymbolCount)
#define  numSymbols  (state_P->__numSymbols)
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

/*         
 *    INPUT BUFFER DEFINES 
 */ 
#define x(DELAY) (*(( complex   *)PIN(0,DELAY)))

/*         
 *    OUTPUT BUFFER  DEFINES 
 */ 
#define y(delay) *( complex   *)POUT(0,delay)

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
ifftofdm54
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
	int j;



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


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 



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
