

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


#if      !defined(_CordicArctan_H)
#define  _CordicArctan_H


typedef signed short INT16S;
typedef signed int   INT32S;
typedef double       FP64;
typedef float        FP32;

/*
 * CORDIC parameters
 */
#define  INPUT_WL      16                   /* Wordlength of x and y      */
#define  NUMBER_ITER   14                   /* Number of iterations       */
#define  ANG_WL        18                   /* angle wordlength           */
#define  G_LSB         3                    /* Number of LSB guard bits   */

 
#define  PI            3.14159265358979 


INT32S CordicArctan(INT32S x,
	                INT32S y, INT32S *r_P);

void ArctanTable(INT32S *atI_P);

void PrintMatrixComplex(INT32S u1r11,INT32S  u1i11,INT32S  u1r12,INT32S  u1i12,INT32S u1r21,INT32S u1i21,INT32S u1r22,INT32S u1i22);

void MultiplyMatrixComplex(INT32S scale2,INT32S u1r11,INT32S u1i11,INT32S u1r12,
                              INT32S u1i12,INT32S u1r21,INT32S u1i21,INT32S u1r22,INT32S u1i22,
                              INT32S ar11,INT32S ai11,INT32S ar12,INT32S ai12,INT32S ar21,
                              INT32S ai21,INT32S ar22,INT32S ai22,
                              INT32S *cr11_P,INT32S *ci11_P,INT32S *cr12_P,INT32S *ci12_P,INT32S *cr21_P,
                              INT32S *ci21_P,INT32S *cr22_P,INT32S *ci22_P);


void MultiplyMatrix(INT32S scale2,INT32S u11,INT32S u12, INT32S u21,INT32S u22,
                              INT32S a11,INT32S a12,INT32S a21, INT32S a22,
                              INT32S *c11_P,INT32S *c12_P,INT32S *c21_P, INT32S *c22_P);




void MultiplyMatrixComplexFP(float  scale2,float  ur11,float  ui11,float  ur12,
                              float  ui12,float  ur21,float  ui21,float  ur22,float  ui22,
                              float  ar11,float  ai11,float  ar12,float  ai12,float  ar21,
                              float  ai21,float  ar22,float  ai22,
                              float  *cr11_P,float  *ci11_P,float  *cr12_P,float  *ci12_P,float  *cr21_P,
                              float  *ci21_P,float  *cr22_P,float  *ci22_P);

void PrintMatrixComplexFP(float u1r11,float u1i11,float u1r12,float u1i12,float u1r21,float u1i21,float u1r22,float u1i22);
 
void MultiplyMatrixFP(float scale2,float u11,float u12, float u21,float u22,
                              float a11,float a12,float a21, float a22,
                              float *c11_P,float *c12_P,float *c21_P, float *c22_P);
#endif

