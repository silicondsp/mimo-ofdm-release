
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

/* *****************************************************************

        BPSKDemapping()

  perform soft decision BPSK demapping scheme. This routine is used
  in SIGNAL field.

  Programmer:     Bin Huang
  date:           8/11/02


   *****************************************************************
 */




#define N 48

void BPSK_soft_demap(
// performs QAM64 demapping using floating point soft decisions
				float * input_x,   // input array pointer
				float * output,    // output array pointer
				float fac0)         // additional scale to be removed after
{
	float in_dx;
	float * outd;
	int k;

	outd = output;
	for(k=0; k<N; k++)
	{
		in_dx = input_x[k];
		if(in_dx > 1.0) in_dx = 1.0;
		if(in_dx <-1.0) in_dx =-1.0;		
                *outd = -fac0*in_dx;
                outd++;
	}
	return;
}

