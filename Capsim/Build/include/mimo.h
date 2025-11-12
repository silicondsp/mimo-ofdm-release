

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

#include <cap_fft.h>
#include <cap_fftr.h>


typedef struct {
                double   re, im;
} cx_t;


typedef struct {
                float   re, im;
} cxFloat_t;

typedef struct double_vector {
        short   type;
        short   transpose;
        int     length;
        double   *vector_P;
} doubleVector_t, *doubleVector_Pt;



typedef struct {
                short   type;
                int     width;
                int     height;

                double   **matrix_PP;
} dsp_Matrix_t, *dsp_Matrix_Pt;


typedef struct {
                int     width;
                int     height;

                float   **matrix_PP;
} dsp_floatMatrix_t, *dsp_floatMatrix_Pt;


typedef struct {
                short   type;
                int     width;
                int     height;

                cx_t   **matrix_PP;
} dsp_cxMatrix_t, *dsp_cxMatrix_Pt;


typedef struct complex_scalar {
        short   type;
        cx_t   value;
} cxScalar_t, *cxScalar_Pt;


typedef struct doublecx_vector {
        short   type;
        short   transpose;
        int     length;
        cx_t   *vector_P;
} cxVector_t, *cxVector_Pt;




/*
 * KISS FFT MATRIX
 */
typedef struct {
                short   type;
                int     width;
                int     height;

                cap_fft_cpx   **matrix_PP;
} dsp_cpxMatrix_t, *dsp_cpxMatrix_Pt;





void PrintCxMatrix(dsp_cxMatrix_t *mat_P);
int Krn_Compute2x2SVDCxMatrix(dsp_cxMatrix_t *mat_P, doubleVector_t *ss_P,dsp_cxMatrix_t *u_P, dsp_cxMatrix_t *v_P);



int Krn_Compute2x2SVDCxMatrixFP(dsp_cxMatrix_t *mat_P, doubleVector_t *ss_P,dsp_cxMatrix_t *u_P, dsp_cxMatrix_t *v_P);


void  Dsp_FreeCpxMatrix(dsp_cpxMatrix_t *matrix_P);

doubleVector_t* Dsp_AllocateVector(int length);
cxVector_t* Dsp_AllocateCxVector(int length);
dsp_Matrix_Pt Dsp_AllocateRealMatrix(int width,int height);
dsp_cxMatrix_Pt Dsp_AllocateCxMatrix(int width,int height);

void fft2s( float realInput[], float imagInput[], float realOutput[], float imagOutput[], int fftSize, int fftSwitch);
doubleVector_t* Dsp_AllocateDoubleVector(int n);
void Krn_PrintVector(doubleVector_t *vec_P,char format[], FILE *fp, int nolen) ;

void Dsp_MultiplyComplexMatricesComplexVector(dsp_cxMatrix_t *a_P,cxVector_t *vbx_P,cxVector_t *vcx_P);
void Dsp_MultiplyComplexMatricesRealVector(dsp_cxMatrix_t *a_P,doubleVector_t*vb_P,cxVector_t *vcx_P);

int Krn_ComputeInverseCxMatrix(dsp_cxMatrix_t *mat_P, dsp_cxMatrix_t *inverse_P);
void Dsp_MultiplyComplexMatrices(dsp_cxMatrix_t *a_P,dsp_cxMatrix_t *b_P,dsp_cxMatrix_t *c_P);
int Krn_ComputeSVDCxMatrix(dsp_cxMatrix_t *mat_P, doubleVector_t *ss_P,dsp_cxMatrix_t *u_P, dsp_cxMatrix_t *v_P);
void Krn_TransposeConjugateMatrix(dsp_cxMatrix_t *mat_P) ;
void Krn_PrintCxMatrix(dsp_cxMatrix_t *mat_P,char format[], FILE *fp);



