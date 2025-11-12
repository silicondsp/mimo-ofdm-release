


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


#include <stdio.h>
#include <math.h>

#include <capsim.h>
#include <stars.h>

//Written by Sasan Ardalan


float ComputeFreqOffset(complex* x_P, int points) {

complex sum;
int i;
float theta;

                sum.re = 0.0; sum.im=0.0;
                for (i=0; i<points; i++) {

                     sum.re += x_P[i].re*x_P[i+points].re+x_P[i].im*x_P[i+points].im;
                     sum.im += x_P[i].im*x_P[i+points].re-x_P[i].re*x_P[i+points].im;

                } 

                theta= atan2(sum.im,sum.re);

return(theta);

}


