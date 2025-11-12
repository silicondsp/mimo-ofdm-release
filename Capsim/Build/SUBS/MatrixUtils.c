
/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 2007-2017   Silicon DSP  Corporation

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

//
// Author Sasan Ardalan
// Date: 2006
// 

#include <stdio.h>

#include "CordicArctan.h"
#include "CordicRotate.h"





void MultiplyMatrixComplex(INT32S scale2,INT32S ur11,INT32S ui11,INT32S ur12,
                              INT32S ui12,INT32S ur21,INT32S ui21,INT32S ur22,INT32S ui22,
                              INT32S ar11,INT32S ai11,INT32S ar12,INT32S ai12,INT32S ar21,
                              INT32S ai21,INT32S ar22,INT32S ai22,
                              INT32S *cr11_P,INT32S *ci11_P,INT32S *cr12_P,INT32S *ci12_P,INT32S *cr21_P,
                              INT32S *ci21_P,INT32S *cr22_P,INT32S *ci22_P) {

     *cr11_P=(ur11*ar11-ui11*ai11)+(ur12*ar21-ui12*ai21);
     *ci11_P=(ur11*ai11+ui11*ar11)+(ur12*ai21+ui12*ar21);

     *cr12_P=(ur11*ar12-ui11*ai12)+(ur12*ar22-ui12*ai22);
     *ci12_P=(ur11*ai12+ui11*ar12)+(ur12*ai22+ui12*ar22);

     *cr22_P=(ur21*ar12-ui21*ai12)+(ur22*ar22-ui22*ai22);
     *ci22_P=(ur21*ai12+ui21*ar12)+(ur22*ai22+ui22*ar22);

     *cr21_P=(ur21*ar11-ui21*ai11)+(ur22*ar21-ui22*ai21);
     *ci21_P=(ur21*ai11+ui21*ar11)+(ur22*ai21+ui22*ar21);

     *cr11_P = *cr11_P/scale2;
     *ci11_P = *ci11_P/scale2;
     *cr12_P = *cr12_P/scale2;
     *ci12_P = *ci12_P/scale2;

     *cr21_P = *cr21_P/scale2;
     *ci21_P = *ci21_P/scale2;
     *cr22_P = *cr22_P/scale2;
     *ci22_P = *ci22_P/scale2;




}

void MultiplyMatrixComplexRight(INT32S scale2,INT32S vr11,INT32S vi11,INT32S vr12,
                              INT32S vi12,INT32S vr21,INT32S vi21,INT32S vr22,INT32S vi22,
                              INT32S ar11,INT32S ai11,INT32S ar12,INT32S ai12,INT32S ar21,
                              INT32S ai21,INT32S ar22,INT32S ai22,
                              INT32S *cr11_P,INT32S *ci11_P,INT32S *cr12_P,INT32S *ci12_P,INT32S *cr21_P,
                              INT32S *ci21_P,INT32S *cr22_P,INT32S *ci22_P) {



     *cr11_P=(ar11*vr11-ai11*vi11)+(ar12*vr21-ai12*vi21);
     *ci11_P=(ar11*vi11+ai11*vr11)+(ar12*vi21+ai12*vr21);

     *cr12_P=(ar11*vr12-ai11*vi12)+(ar12*vr22-ai12*vi22);
     *ci12_P=(ar11*vi12+ai11*vr12)+(ar12*vi22+ai12*vr22);

     *cr22_P=(ar21*vr12-ai21*vi12)+(ar22*vr22-ai22*vi22);
     *ci22_P=(ar21*vi12+ai21*vr12)+(ar22*vi22+ai22*vr22);

     *cr21_P=(ar21*vr11-ai21*vi11)+(ar22*vr21-ai22*vi21);
     *ci21_P=(ar21*vi11+ai21*vr11)+(ar22*vi21+ai22*vr21);

     *cr11_P = *cr11_P/scale2;
     *ci11_P = *ci11_P/scale2;
     *cr12_P = *cr12_P/scale2;
     *ci12_P = *ci12_P/scale2;

     *cr21_P = *cr21_P/scale2;
     *ci21_P = *ci21_P/scale2;
     *cr22_P = *cr22_P/scale2;
     *ci22_P = *ci22_P/scale2;




}

void MultiplyMatrix(INT32S scale2,INT32S u11,INT32S u12, INT32S u21,INT32S u22,
                              INT32S a11,INT32S a12,INT32S a21, INT32S a22,
                              INT32S *c11_P,INT32S *c12_P,INT32S *c21_P, INT32S *c22_P) {

     *c11_P=(u11*a11)+(u12*a21);

     *c12_P=(u11*a12)+(u12*a22);

     *c22_P=(u21*a12)+(u22*a22);

     *c21_P=(u21*a11)+(u22*a21);

     *c11_P = *c11_P/scale2;
     *c12_P = *c12_P/scale2;

     *c21_P = *c21_P/scale2;
     *c22_P = *c22_P/scale2;




}



void PrintMatrixComplex(INT32S u1r11,INT32S  u1i11,INT32S  u1r12,INT32S  u1i12,INT32S u1r21,INT32S u1i21,INT32S u1r22,INT32S u1i22) {

   printf("%d,%d\t",u1r11,u1i11);
   printf("%d,%d\n",u1r12,u1i12);

   printf("%d,%d\t",u1r21,u1i21);
   printf("%d,%d\n",u1r22,u1i22);


}

void PrintMatrixComplexFP(float u1r11,float u1i11,float u1r12,float u1i12,float u1r21,float u1i21,float u1r22,float u1i22) {

   printf("%f,%f\t",u1r11,u1i11);
   printf("%f,%f\n",u1r12,u1i12);

   printf("%f,%f\t",u1r21,u1i21);
   printf("%f,%f\n",u1r22,u1i22);


}


void MultiplyMatrixComplexFP(float  scale2,float  ur11,float  ui11,float  ur12,
                              float  ui12,float  ur21,float  ui21,float  ur22,float  ui22,
                              float  ar11,float  ai11,float  ar12,float  ai12,float  ar21,
                              float  ai21,float  ar22,float  ai22,
                              float  *cr11_P,float  *ci11_P,float  *cr12_P,float  *ci12_P,float  *cr21_P,
                              float  *ci21_P,float  *cr22_P,float  *ci22_P) {

     *cr11_P=(ur11*ar11-ui11*ai11)+(ur12*ar21-ui12*ai21);
     *ci11_P=(ur11*ai11+ui11*ar11)+(ur12*ai21+ui12*ar21);

     *cr12_P=(ur11*ar12-ui11*ai12)+(ur12*ar22-ui12*ai22);
     *ci12_P=(ur11*ai12+ui11*ar12)+(ur12*ai22+ui12*ar22);

     *cr22_P=(ur21*ar12-ui21*ai12)+(ur22*ar22-ui22*ai22);
     *ci22_P=(ur21*ai12+ui21*ar12)+(ur22*ai22+ui22*ar22);

     *cr21_P=(ur21*ar11-ui21*ai11)+(ur22*ar21-ui22*ai21);
     *ci21_P=(ur21*ai11+ui21*ar11)+(ur22*ai21+ui22*ar21);

     *cr11_P = *cr11_P/scale2;
     *ci11_P = *ci11_P/scale2;
     *cr12_P = *cr12_P/scale2;
     *ci12_P = *ci12_P/scale2;

     *cr21_P = *cr21_P/scale2;
     *ci21_P = *ci21_P/scale2;
     *cr22_P = *cr22_P/scale2;
     *ci22_P = *ci22_P/scale2;




}

void MultiplyMatrixFP(float scale2,float u11,float u12, float u21,float u22,
                              float a11,float a12,float a21, float a22,
                              float *c11_P,float *c12_P,float *c21_P, float *c22_P) {

     *c11_P=(u11*a11)+(u12*a21);

     *c12_P=(u11*a12)+(u12*a22);

     *c22_P=(u21*a12)+(u22*a22);

     *c21_P=(u21*a11)+(u22*a21);

     *c11_P = *c11_P/scale2;
     *c12_P = *c12_P/scale2;

     *c21_P = *c21_P/scale2;
     *c22_P = *c22_P/scale2;




}


