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




#define N 48               // number of input complex numbers

// After multiplying by Scale = SQRT(42) input floats should be within {-8 ... +8}

void soft_demap(float * input_x, float * input_y, float * output);
void quant(float inp, float * out);
void quant3bit(float inp, float * out);

// Table of precomputed Lower (Left) Constellation Boundaries
static float LCB[8] = {-8, -6, -4, -2, 0, 2, 4, 6}; 
							         				
