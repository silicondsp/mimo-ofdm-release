

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


#define CONSTRAINT_LENGTH 7

static int A[7] = {1, 0, 1, 1, 0, 1, 1};        // code vector A
static int B[7] = {1, 1, 1, 1, 0, 0, 1};        // code vector B

typedef  unsigned long int ULINT;
typedef  unsigned char  UCHAR;


void convenc(ULINT * input, ULINT prev6,
             ULINT * output_A, ULINT * output_B, int length);




void scrambler_216(int * init_seed,           // input, initial seed
                   unsigned char * input,     // input sequence of bytes, LSbit is on/off
                   unsigned char * output,    // output sequence of bytes, all 8 bits
                   int N_INPUT);



void Swap(
complex *x,           /* (i/o)  : vector swap  */
int   m                  /* (i)    : length of vecotr  */
);


void Polarity(
  complex x[],            /* (i/o)  : vector swap  */
  int   index               /* (i):     index for polarity control vector[0~126] */
);


//double ceil(double x);

 void signalPacket(
   Word32 dataRate,                   /* data rate that is included in SIGNAL  */
   Word32 ofdmSymbolLength,           /* OFDM symbol length that is included in SIGNAL */
   Word32 resvervedBit,                /* reserved bit that is included in SIGNAL, default is zero */
   Fword ifftOut_re[],
   Fword ifftOut_im[]
);

// prototype for general IFFT/FFT subroutine:

 void fftofdm54(
	      float realInput[],

	      float imagInput[],

		   float realOutput[],

		   float imagOutput[],

		   int fftSize,

		   int fftSwitch);



double myatan(double arg);
double myatan2(double arg1,double arg2);
float mycos_32(float x);
float mysin_32(float x);
float myfmod(float x,float y);

