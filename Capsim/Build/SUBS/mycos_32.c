

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

                       mycos_32 compute cosine in any radians

        This is the main cosine approximation. It reduces the input arguement's range
        to [0, PI/2] and then call the cos_32s.c.

        Author:      Bin Huang
		Date:        10/13/02

*/

#include <math.h>
#include <stdio.h>
#include "mycos.h"



float mycos_32s(float x);


float mycos_32 (float x)

{

  double   twoPI = 2.0*PI; 
  double   halfPI = PI/2.0;
  int quadr;
 
//  x = (float) fmod ((double) x,twoPI);

  if (x<0.0) 
	   x = -x;

  quadr = (int) floor(((double) x)/halfPI);         // choose the quadrant

  switch (quadr) {

   case 0:

     return mycos_32s(x);
     break;

   case 1:
 
     return -mycos_32s((float)PI-x);
     break;

   case 2:

     return -mycos_32s(x-(float)PI);
     break;

   case 3:

     return  mycos_32s((float)twoPI-x);
     break;

  }

}
