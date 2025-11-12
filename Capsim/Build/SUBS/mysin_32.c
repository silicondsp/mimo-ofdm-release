

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

               mysin_32 compute sin()

         The sine function is just cosine function shifted by PI/2, so we will
         adjust the input arguement and call the mycos_32.c.

         Algorithm:   sin(x) = cos(PI/2 -x).

     
         Author:     Bin Huang
         Date:       10/13/02




*/

#include "mycos.h"



float mycos_32(float x);


float mysin_32(float x)

{
  double  halfPI = PI/2.0;
  return mycos_32(halfPI - x);

}


