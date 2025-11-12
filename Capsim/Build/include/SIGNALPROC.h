

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



#define fac   	2
#define K   	7
#define frameLength   	18
#define es_ovr_n0   	0
#define quantizerType   2
#define bitsPerSoftValue   	3
#define tracebackDepthFactor   	7
#define simplified   	1
#define m 6


//#define SAMPLES_PER_INPUT 80
//#define SAMPLES_PER_OUTPU_BUFFER 128

#define N1 80
#define N2 64

//#define TRUE 1
//#define FALSE 0


//#define USER_INIT 1
//#define MAIN_CODE 2
//#define WRAPUP 3
#define RATE54 54
#define RATE48 48
#define RATE36 36
#define RATE24 24
#define RATE18 18
#define RATE12 12
#define RATE9 9
#define RATE6 6

/*
int signalprocessing(
 int run_state,
// state_Pt pstate,
 complex* in_P,
 complex* ch_P,
 int* dataRate, 
 int* dataLength);

void fft_fpsim(float realInput[],
	           float imagInput[],
		   float realOutput[], 
		   float imagOutput[],
		   int fftSize,
		   int fftSwitch);

  */

void unpackDeinter6(
  float x[],            /*  (i):     input: x[48] */
  int length,        /*  (i):    the length :48  */
  float y[]             /*  (o):     output 48 float numbers    */
);


void DataSelect(
  float * x_re,         /* real part of input data[64] */
  float * x_im,         /* imag part of input data[64] */
  float * yy_re,        /* real part of rearranged data[48] */
  float * yy_im,        /* imag part of rearranged data[48] */
  float * pilo_re,    /* real part of pilots[4] */
  float * pilo_im
);                     /* imag part of pilots[4] -supposed to be 0 */



void BPSK_soft_demap(
// performs QAM64 demapping using floating point soft decisions
				float * input_x,   // input array pointer
				float * output,    // output array pointer
				float fac0);         // additional scale to be removed after
