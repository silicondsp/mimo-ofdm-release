
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



/*      *********************************************************************

                   interBPSK_conver()
 
          interface between interleaving coding and BPSK mapping, the output
          of interleaving coding are distributed in three 32-bit registers in 
          for PEs. the inputs to BPSK mapping should be packed data. So the
          data conversion between interleaving and BPSK mapping is needed.
	 

     

programmer                        Bin Huang
date:                             9/25/01 

       **********************************************************************

*/


#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "ftab_80211a.h"


void interBPSK_conver(
  Word32 x_PE0[],            /* input integers  */
  Word32 x_PE1[],
  Word32 x_PE2[],
  Word32 x_PE3[],
  Word32 y[]                 /* output integer total 48 bits included in two 32-bit registers */
)
{

  Word32 temp0, temp1, temp2;

   temp0 = x_PE0[0];
   temp1 = x_PE1[0] << 12;
   temp2 = x_PE2[0] << 24;
   y[0] = temp0 + temp1 + temp2;
   temp0 = x_PE2[0] >> 8;
   temp1 = x_PE3[0] << 4;
   y[1] = temp0 + temp1;

}
   
