

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

                          mycos_32s computes cosine (x)

  Accurate to about 3.2 decimal digits over the period [0, PI/2].
  The input arguement is in radians.

  Algorithm:

   cos(x) = c0+c1*x**2+c2*x**4.

  Author:     Bin Huang
  Date:       10/13/02

*/


float mycos_32s(float x)

{

  const float c0 = 0.99940307;
  const float c1 = -0.49558072;
  const float c2 = 0.03679168;

  float tmp;

  tmp = x*x;
  return (c0+tmp*(c1+c2*tmp));

}
  
