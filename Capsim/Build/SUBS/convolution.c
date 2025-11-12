
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

/* **********************************************************
       convolution()

 industial standard convolution encoding with coding rate of 1/2
 and constraint length of 7. The generator polynomials are (177,133).


programmer:    Bin Huang
date:          6/1/02

  ***********************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "ftab_80211a.h"


#define CONSTRAINT_LENGTH 7


static int A[7] = {1, 0, 1, 1, 0, 1, 1};
static int B[7] = {1, 1, 1, 1, 0, 0, 1};


void convolution(unsigned long  * input,     // input bit stream formatted as
			                            // 32 bit words with b0 as LSbit (#0) 
			 unsigned long  * output_A,  // output bit stream A, format as above
			 unsigned long  * output_B,  // output bit stream B, format as above
                         int  NUMBER)     // number of input/output words
{

	Word32 temp_A, temp_B;
	Word32 prev_A, prev_B;
        Word16 k, l;

	prev_A = 0;
	prev_B = 0;
	for(k=0; k<NUMBER; k++, output_A++, output_B++)
	{
		temp_A =  input[k];
		*output_A = input[k];

		for(l=1; l< CONSTRAINT_LENGTH; l++)
		{
			temp_A = temp_A<<1;
		    temp_A = temp_A + ((prev_A&0x80000000)>>31);
		    prev_A = prev_A<<1;
		    if(A[l] == 1)
			     *output_A = *output_A ^ temp_A;
		}
		prev_A = input[k];

		temp_B =  input[k];
		*output_B = input[k];
		for(l=1; l<CONSTRAINT_LENGTH; l++)
		{
			temp_B = temp_B<<1;
		    temp_B = temp_B + ((prev_B&0x80000000)>>31);
		    prev_B = prev_B<<1;
		    if(B[l] == 1)
			     *output_B = *output_B ^ temp_B;
		}
		prev_B = input[k];

	}
}

