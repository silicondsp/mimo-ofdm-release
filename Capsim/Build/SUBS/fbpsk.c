

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




/*   ***********************************************************************

                 FBPSK()

   Description: 
 
     floating point 802.11a BPSK mapping, total number of input bits is 48.
	 The output should be 48 complex symbols(Q15)

      

<Author>                        Bin Huang
<date created>                  7/19/01

    ************************************************************************
*/


#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "ftab_80211a.h"

/* this BPSK Mapping function is based on Q31 data formats  
   if we make Q47 data format, this routine can be simplified
   but will make other modulation functions complicated   */


void BPSK_MAP(
  Word32 x[],            /*  (i):     input bits: x[0--1]  */
  Word16 M,              /*  (i):     the length of input bits: 48  */
  Fword y_real[],       /*  (o):     output symbol, real aprt: y_real[48]  */
  Fword y_imag[]        /*  (o):     output symbol, imaginary part:y_imag[48] */
)


{

  Word16 i, j=0;
  Word32 L_bpsk, L_bpsk0;

  
  L_bpsk=x[0]; 

  for(i=0; i<M-16; i++)                 /* mapping the first 32 bits  */
   {
    
     L_bpsk0=L_bpsk & (Word32)0X00000001;
      
     y_real[j]=BPSK_MAPTable[0][L_bpsk0];
     y_imag[j]=BPSK_MAPTable[1][L_bpsk0];     
     j++;
	 L_bpsk = L_bpsk >> 1;
    } 

 
  L_bpsk=x[1];

  for(i=0; i<M-32; i++)                 /* mapping the last 16 bits  */
   {
     L_bpsk0=L_bpsk & (Word32)0X00000001;
      
     y_real[j]=BPSK_MAPTable[0][L_bpsk0];
     y_imag[j]=BPSK_MAPTable[1][L_bpsk0];
     j++;
	 L_bpsk = L_bpsk >> 1;
    } 

  
}








