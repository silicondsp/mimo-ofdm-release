

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


/*   ********************************************************************

                   puncture()

   perform puncturing in order to come up different coding rate after
   convolution encoding with coding rate of 1/2 and constraint length
   of 7.

  Programmer:      Bin Huang
  date:            6/31/02

   **********************************************************************
*/

//local headers
#include "punctureofdm.h"
#include "typedef.h"


/*
Function:		puncture
Description:	performs the actual puncture operation
Inputs:
	codingRate	one of RATE_xxx .
	bitstreamA	array of streamA input bits. Each bit is one of value:0,1.
	bitstreamB	array of streamB input bits, Each bit is one of value:0,1.
	insize		# of bits in each input stream
	outsize		# of bits in the output.
Outputs:
	outbuf_p	where to put the output, Each bit is one of value:0,1.


*/




void punctureofdm(
  Word16 codingRate,
  Word32 ABits[],
  Word32 BBits[],
  Word16 insize,
  Word16 outsize,
  Word32* outbuf_p
)
{
//	unsigned long BitStolenOutputBits[288];
	Word32 *Ap,*Bp;
	Word32 *BSOp;
	Word16 count;
	
	//create the bit-stolen output,
	Ap=ABits;
	Bp=BBits;
	BSOp=outbuf_p;
	
	
	switch (codingRate)
	{
		case RATE_12:  //just copy input to output, alternating A, then B

			count=0;
			do
			{
				*BSOp++ = *Ap++; count++;
				*BSOp++ = *Bp++; count++;
			} while (count<outsize);
			break;

		case RATE_34:  //create pattern: A0,B0,A1,B2
			count=0;
			do
			{
				*BSOp++ = *Ap++; count++;
				*BSOp++ = *Bp++; count++; Bp++;//skip B1
				*BSOp++ = *Ap++; count++; Ap++;//skip A2
				*BSOp++ = *Bp++; count++;
			} while (count<outsize);
			break;
		case RATE_23:  //create pattern: A0,B0,A1
			count=0;
			do
			{
				*BSOp++ = *Ap++; count++;
				*BSOp++ = *Bp++; count++; Bp++;//skip B1
				*BSOp++ = *Ap++; count++; 
			} while (count<outsize);
			break;

	} //end switch

}
