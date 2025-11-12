

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
File:                unpackDeinter6.c

Description: 

     fixed point 802.11a Deinterleaver for rate=6,9 Mbps, total number of 
     input bits is 48 in float format. 
	


<Author>                        Bin Huang
<date created>                  11/09/01 
*/

#include <stdio.h>
#include <stdlib.h>
//#include "typedef.h"
#include "deinter6.h"
#include "deintertable6.h"


void unpackDeinter6(
  float x[],            /*  (i):     input: x[48] */
  int length,        /*  (i):    the length :48  */
  float y[]             /*  (o):     output 48 float numbers    */
)
{
	int i, index;

	for (i=0; i<length; i++)
	{
       index = unpackIndexTable6[i];
	   y[index] = x[i];
	}
}
 

