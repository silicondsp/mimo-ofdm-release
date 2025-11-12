

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
based on Sasan Ardalan's modifications of vdsim.h
Function sdvd_parms declaration modified to match the added parameters.

*/


#if 000
#define K 7              /* constraint length */
#define TWOTOTHEM 64      /* 2^(K - 1) -- change as required */
#endif

#define PI 3.141592654   /* circumference of circle divided by diameter */

#define MSG_LEN 100000l  /* how many bits in each test message */


#undef DOENC            /* test with convolutional encoding/Viterbi decoding */
#define  DONOENC          /* test with no coding */



#define LOESN0 0.0       /* minimum Es/No at which to test */
#define HIESN0 3.5       /* maximum Es/No at which to test */
#define ESN0STEP 0.5     /* Es/No increment for test driver */


#define MAXINT 2147483647


#define K_MAX 11
#define TWOTOTHEM_MAX 1024  /* 2^(K_MAX-1) */

extern void sdvd_parms(int K,int **g, float es_ovr_n0, long channel_length,
            float *channel_output_vector, int *decoder_output_matrix, int quantizerType,
            int bitsPerSoftValue,int tracebackDepthFactor, int **input);

extern void sdvd_parms_54(int K,int **g, float es_ovr_n0, long channel_length,
            float *channel_output_vector, int *decoder_output_matrix, int quantizerType,
            int bitsPerSoftValue,int tracebackDepthFactor);


