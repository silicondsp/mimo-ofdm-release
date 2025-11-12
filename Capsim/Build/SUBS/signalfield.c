

/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 1989-2017   Silicon DSP  Corporation

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
File:                         signalField.c

Description: 

     fixed point 802.11a signal field, total number of signal bits are 24.
     The input 'rate' should be 0(6),1(9),2(12),3(18),4(24),5(36),6(48),7(54)
	 respectively. The input 'length' should be any number between 1--4095.
     
      

<Author>                        Bin Huang
<date created>                  9/17/01 
*/


#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "ftab_80211a.h"


void signalField(
  Word32  rate,                  /* [i]: data rate  */
  Word32  length,                /* [i]: length of OFDM symbols    */
  Word32  r,                     /* [i]: the reserved bit, only 1 or 0 */
  Word32  *signal                 /* [o]: 24 bits output            */
)

{

   Word32   Lp0, Lp1, Lp2;

    Lp0 = rateTable[rate];
    Lp1 = length & (Word32) 0x00000fff;     /* clean upper bits of length */
    Lp1 = Lp1 << 5;                         /* put length(12 bits) into 5th--16th place */
    Lp2 = r << 4;                           /* put the reserved bit in 4th place */
    *signal = Lp0 + Lp1 + Lp2;               /* create 24 bits signal     */

}
   

