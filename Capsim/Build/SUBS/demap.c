

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

/*  ********************************************************************

         modulationDemapping()

    perform both soft decision and hard decision modulation demapping
	with quantization on 64 QAM. Will add some other demapping schemes 
	based on different data rates later.

    Programmer:      Bin Huang
    Date:            8/7/02


    ********************************************************************
 */




#include "demap.h"
			         							        							         							         							
void soft_demap(
// performs QAM64 demapping using floating point soft decisions
				float * input_x,   // input array pointer 
				float * input_y,   // input array pointer 
				float * output)    // output array pointer				
{
	float in_dx, in_dy;
	float * outd;
	int k;

	outd = output;
	for(k=0; k<N; k++)
	{
		in_dx = input_x[k];
                quant(in_dx, outd);
		outd += 3;
		in_dy = input_y[k];
                quant(in_dy, outd);
		outd += 3;
	}
	
	// renormalization to make output within -128 ... 127
	outd = output;
	for(k=0; k<6*N; k++)
	{
		/* output[k] = -16.0*(*outd);    Experiment */
		output[k] = -2.0*(*outd);	 /* Experiment */	
		outd++;
	}
	return;
}

void hard_demap(
// performs QAM64 demapping using hard decision
				float * input_x,   // input array pointer
				float * input_y,   // input array pointer
				float * output)    // output array pointer				
{
	float in_dx, in_dy;
	float * outd;
	int k;

	outd = output;
	for(k=0; k<N; k++)
	{
		in_dx = input_x[k];
                quant(in_dx, outd);
		outd += 3;
		in_dy = input_y[k];
                quant(in_dy, outd);
		outd += 3;
	}
	
	// change quantization to hard decision
	outd = output;
	for(k=0; k<6*N; k++)
	{
	        if(*outd > 0)
	        {
	             output[k] = -128.0;
	        }
	        else
	        {
	             output[k] = 127.0;
	        }
		outd++;
	}
	return;
}


void quant(float actinp,     // input value to be mapped as float
               float * out)  // pointer to 3 consequtive outputs
{
        float inp;
	float * outp;
	
	inp = actinp;
	outp = out;	
		// Mapping of the first bit b0
		// clip off if outside of -8.0... 8.0
        if( inp < -8.0 )
        {
              inp = -7.9375;      // -7.9375 = -127/16
        }
        if( inp > 8.0 )
        {
              inp = 8.0;
        }
        *outp = inp;
	outp++;

		// Mapping of the second bit b1
        if( inp <= 0.0 )
        {
              *outp = 1*(4.0+inp);
        }
        else
        {
              *outp = 1*(4.0-inp);
        }		
        outp++;

		// Mapping of the third bit b2
        if( inp <= 0.0 )
        {
               if( inp <= -4.0 )
               {
                      *outp = 1*(6.0+inp);
               }
               else
               {
                      *outp = 1*(-2.0-inp);
               }
        }
        else
        {
               if( inp <= 4.0 )
               {
                      *outp = 1*(-2.0+inp);
               }
               else
               {
                      *outp = 1*(6.0-inp);
               }
        }
        return;
}

// function to quantize QAM64_demap using 3 bits per soft value	
void quant3bit(float inp,        // input value to be quantized
		   float * out)  // pointer to 3 consequtive outputs
{
		// Quantization of the first bit b0
		if( inp < -6.0)
			*out = 0x00;
		else if ( inp < -4.0)
			*out = 0x01;
		else if ( inp < -2.0)
			*out = 0x02;
		else if ( inp < 0.0)
			*out = 0x03;
		else if ( inp < 2.0)
			*out = 0x04;
		else if ( inp < 4.0)
			*out = 0x05;
		else if ( inp < 6.0)
			*out = 0x06;
		else if ( inp >= 6.0)
			*out = 0x07;
		out++;

		// Quantization of the second bit b1
		if( inp < -6.0)
			*out = 0x00;
		else if ( inp < -4.0)
			*out = 0x01;
		else if ( inp < -2.0)
			*out = 0x02;
		else if ( inp < 0.0)
			*out = 0x03;
		else if ( inp < 2.0)
			*out = 0x03;
		else if ( inp < 4.0)
			*out = 0x02;
		else if ( inp < 6.0)
			*out = 0x01;
		else if ( inp >= 6.0)
			*out = 0x00;
		out++;

		// Quantization of the third bit b2
		if( inp < -6.0)
			*out = 0x00;
		else if ( inp < -2.0)
			*out = 0x01;
		else if ( inp < +2.0)
			*out = 0x00;
		else if ( inp < 6.0)
			*out = 0x01;
		else if ( inp >= 6.0)
			*out = 0x00;

		return;
}

void soft_demap_54(
// performs QAM64 demapping using 3 bit soft decision table SOFT_Q64 table
				float * input_x,   // input array pointer
				float * input_y,   // input array pointer
				float * output)    // output array pointer				
{
	float in_dx, in_dy;
	float * outd;
	int k;

	outd = output;
	for(k=0; k<N; k++)
	{
		in_dx = input_x[k];
                quant(in_dx, outd);
		outd += 3;
		in_dy = input_y[k];
                quant(in_dy, outd);
		outd += 3;
	}
	
	// renormalization and shift to make output within 0 ... 7
	outd = output;
	for(k=0; k<6*N; k++)
	{
	        output[k] = 32*(*outd);
		/* output[k] = 2.0*(6.0+ (*outd));	  Experiment */
		if( output[k] <= 0.0 ) output[k] = 0.0;			
		if( output[k] > 7.0 ) output[k] = 7.0; 	
		outd++;
	}
	return;
}
	
