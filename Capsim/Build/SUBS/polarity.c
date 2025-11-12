

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
   ***************************************************************************

               polarity()

  perform the polarity to the inserted pilots

  programmer:     Bin Huang
  date:           7/31/02 


   ***************************************************************************
*/

#include <math.h>
#include "complex.h"
#include "typedef.h"
#include "anisim.h"

#include "ftable_80211a.h"
#include "ftab_80211a.h"

void Polarity(
  complex x[],            /* (i/o)  : vector swap  */
  int   index               /* (i):     index for polarity control vector[0~126] */
)
{
	float  temp, k1=-1.0;

	temp = Polarity_control[index];
        x[7].re = temp;
	x[21].re = k1 * temp;
	x[43].re = temp;
	x[57].re = temp;

	

}

	
    
