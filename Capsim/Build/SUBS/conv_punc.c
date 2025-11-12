
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
File:                      conv_punc.c

Description: 
      interface between convolutional coding and puncturing, the output
      of conv. coding are two packed 32-bit integers, the inputs to 
	  puncturing should be a data array and each element only contains value
	  0 or 1, so need a small function to covert packed 32-bit data into
	  parse 0 or 1.  

     

<Author>                        Bin Huang
<date created>                  9/25/01 

*/


#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "ftab_80211a.h"

void conv_punc(
  Word32 out_A,      /* [i]: stream A   */
  Word32 out_B,      /* [i]: stream B   */
  Word16 len,        /* [i]: length of the streams  */
  Word32 Abits[],    /* [o]: Abits[len], each element should be either 0 or 1  */
  Word32 Bbits[]
)
{

  Word16 i;	 
  Word32 temp_A, temp_B;

   for (i=0; i<len; i++)
    {
      temp_A = out_A >> i;
      Abits[i] = temp_A & (Word32) 0x00000001;
      temp_B = out_B >>i;
      Bbits[i] = temp_B & (Word32) 0x00000001;
    }
}
 
