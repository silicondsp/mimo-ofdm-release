

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

      swap()

   perform the data swap in order to come up with the IFFT input requirment

   porgrammer:     Bin Huang
   date:           7/5/02 

     ********************************************************************
*/


#include <math.h>
#include "complex.h"
#include "typedef.h"
#include "anisim.h"




void  Swap(
  complex *x,           /* (i/o)  : vector swap  */
  int   m                  /* (i)    : length of vecotr  */
)

{
   int i;
   float  pReal, pImag;

 for (i=0; i<m; i++)
  {

       pReal=x[i].re;
       pImag=x[i].im;
       x[i].re=x[32+i].re;
       x[i].im=x[32+i].im;
       x[32+i].re=pReal;
       x[32+i].im=pImag;
 }
   
}
