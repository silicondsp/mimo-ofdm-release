

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
File:                   signalPacket.h

Description:           802_11a C prototype files    */


void signalField(
  Word32  rate,                  /* [i]: data rate  */
  Word32  length,                /* [i]: length of OFDM symbols    */
  Word32  r,                     /* [i]: the reserved bit, only 1 or 0 */
  Word32  *signal                 /* [o]: 24 bits output            */
);

void convolution(unsigned long * input,     // input bit stream formatted as 
			                            // 32 bit words with b0 as LSbit (#0) 
			 unsigned long * output_A,  // output bit stream A, format as above
			 unsigned long * output_B,  // output bit stream B, format as above
			           int  NUMBER);     // number of input/output words
void conv_punc(
  Word32 out_A,      /* [i]: stream A   */
  Word32 out_B,      /* [i]: stream B   */
  Word16 len,        /* [i]: length of the streams  */
  Word32 Abits[],    /* [o]: Abits[len], each element should be either 0 or 1  */
  Word32 Bbits[]
);

/*
void punctureofdm(

 int codingRate,
 unsigned long ABits[],
 unsigned long BBits[],
 int insize,
 int outsize,
 unsigned long* outbuf_p

);

*/

void punctureofdm(
  Word16 codingRate,
  Word32 ABits[],
  Word32 BBits[],
  Word16 insize,
  Word16 outsize,
  Word32* outbuf_p
);


void interleaver(
 unsigned long inputBits[],        /*[i]: input data bits   */
 unsigned long outPE0[],           /*[o]: first 1/4 output bits, total 3 32-bit numbers  */
 unsigned long outPE1[],           /*[o]: second 1/4 output bits, total 3 32-bit numbers  */
 unsigned long outPE2[],           /*[o]: third 1/4 output bits, total 3 32-bit numbers  */
 unsigned long outPE3[]            /*[o]:  fourth 1/4 output bits, total 3 32-bit numbers  */
 ); 

void interBPSK_conver(
  Word32 x_PE0[],            /* input integers  */
  Word32 x_PE1[],
  Word32 x_PE2[],
  Word32 x_PE3[],
  Word32 y[]                 /* output integer total 48 bits included in two 32-bit registers */
);

void BPSK_MAP(
  Word32 x[],            /*  (i):     input bits: x[0--1]  */
  Word16 M,              /*  (i):     the length of input bits: 48  */
  Fword y_real[],       /*  (o):     output symbol, real aprt: y_real[48]  */
  Fword y_imag[]        /*  (o):     output symbol, imaginary part:y_imag[48] */
);

void Pilot_insertion(
  Fword xReal[],       /* (i)    : real part    */
  Fword xImag[],       /* (i)    : imaginary part    */
  Word16 pilotCount,   /* (i)    : index polarity control vector for pilot subcarriers */
  Fword yiReal[],       /* (o)    : real part    */
  Fword yiImag[]        /* (o)    : imaginary part    */
 
);


void fftofdm54(
  const float *realInput,
  const float *imagInput,
  float *realOutput,
  float *imagOutput,
  int fftSize,
  int fftSwitch
);



