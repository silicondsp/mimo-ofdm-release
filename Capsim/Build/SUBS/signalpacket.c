
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



/*
File:             signalPacket.c

Description: 
                this signalPacket.c file is a control code for sending SIGNAL field through
                convolutional coding, puncturing, interleaving and BPSK mapping.

      

<Author>                        Bin Huang
<date created>                   9/25/01 

*/

#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "ftab_80211a.h"
#include "signalpacket.h"

#define  CONV  1
#define  CONVPUNC 24
#define  PUNC 48
#define  PUNCRATE 12
#define  IFFTSWITCH -1
#define  IFFTN 64

void convolution(unsigned long  * input,     // input bit stream formatted as^M
                                                    // 32 bit words with b0 as LSbit (#0) ^M
                         unsigned long  * output_A,  // output bit stream A, format as above^M
                         unsigned long  * output_B,  // output bit stream B, format as above^M
                         int  NUMBER);     // number of input/output words^M
//void fftofdm54( float realInput[], float imagInput[], float realOutput[], float imagOutput[], int fftSize, int fftSwitch); 

void signalPacket(
   Word32 dataRate,                   /* data rate that is included in SIGNAL  */ 
   Word32 ofdmSymbolLength,           /* OFDM symbol length that is included in SIGNAL */
   Word32 resvervedBit,                /* reserved bit that is included in SIGNAL, default is zero */
   Fword ifftOut_re[],
   Fword ifftOut_im[]
)
{
    
         Word32 Signal;
         Word16 i;
	 Word32 output_A[1], output_B[1];
	 Word32 Abits[24], Bbits[24];
	 Word32 Out_punc[48];
	 Word32 PE0[3], PE1[3], PE2[3], PE3[3];
	 Word32 BPSK_input[2];
	 Fword  y_re[48], y_im[48], ifft_re[64],ifft_im[64];
	 Word16 convsize,convpuncsize,puncsize, prate,ifftsize,ifftswitch;
 //        Fword  ifftOut_re[64], ifftOut_im[64];
//	 Fword  cyclicRe[81], cyclicIm[81];
  
   /* generate the SIGNAL   */

    convsize = (Word16) CONV;
    convpuncsize = (Word16) CONVPUNC;
    puncsize = (Word16) PUNC;
    prate = (Word16) PUNCRATE;
    ifftsize = (Word16) IFFTN;
    ifftswitch = (Word16) IFFTSWITCH;

   for(i=0;i<48;i++)
    {
     Out_punc[i]=0;
    }


     signalField(dataRate,ofdmSymbolLength,resvervedBit,&Signal);



   /* SIGNAL goes through convolutional coding   */

     convolution(&Signal,output_A, output_B, convsize);


   /* interface between convolutional coding and puncturing, the output
      of conv. coding are two packed 32-bit integers, the inputs to 
	  puncturing should be a data array and each element only contains value
	  0 or 1, so need a small function to covert packed 32-bit data into
	  parse 0 or 1.  */

     conv_punc(output_A[0],output_B[0],convpuncsize,Abits,Bbits);


   /* goes through Puncturing code  */

     punctureofdm(prate,Abits,Bbits,convpuncsize,puncsize,Out_punc);



   /* goes through interleaver code, the output of puncturing is unpacked
      and the input of interleaving is unpacked, so the interface between 
	  both of these two blocks is match	 */

     interleaver(Out_punc, PE0,PE1,PE2,PE3);

	

   /* interface between interleaving and BPSK  */

    interBPSK_conver(PE0,PE1,PE2,PE3,BPSK_input);



   /* goes through BPSK mapping   */

     BPSK_MAP(BPSK_input,PUNC,y_re,y_im);


   /* pilot insertion, adding zeros, data relocation and polarity control  */


     Pilot_insertion(y_re,y_im,0,ifft_re,ifft_im);



    /* IFFT */

     fftofdm54(ifft_re,ifft_im,ifftOut_re,ifftOut_im,ifftsize,ifftswitch);



    /* cyclic extention and windowing */

   //   SignalCyclic(ifftOut_re, ifftOut_im, cyclicRe, cyclicIm);

}
