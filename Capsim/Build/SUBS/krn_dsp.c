#include <stdio.h>
#include <math.h>
#include <string.h>

#include <tcl.h>
#include <cap_fft.h>
#include <cap_fftr.h>
#include "vectors.h"
#include "random.h"


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

//
// Author: Sasan Ardalan
// Date: 2007


#define RAND_LARGE 0x7fffffff
#define DEC
#define BLOCK_SIZE 512

#define PI 3.14159265358979323846

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


void Krn_PrintMatrix(dsp_Matrix_t *mat_P,char format[], FILE *fp) {
  int n;
  int i,j;
  char format1[256];

  strcpy(format1,"%");
  strcat(format1,format);
  strcat(format1,"\t");



  printf("Printing Matrix Rows=%d Columns=%d\n",mat_P->height,mat_P->width);
  for(i=0; i<mat_P->height; i++) {
     for(j=0; j<mat_P->width; j++){
          fprintf(fp,format1,mat_P->matrix_PP[i][j]);
     }
     fprintf(fp,"\n");
  }

}
void Krn_PrintMatrixFloat(dsp_floatMatrix_Pt mat_P,char format[], FILE *fp) {
  int n;
  int i,j;
  char format1[256];

  strcpy(format1,"%");
  strcat(format1,format);
  strcat(format1,"\t");



  printf("Printing Matrix Rows=%d Columns=%d\n",mat_P->height,mat_P->width);
  for(i=0; i<mat_P->height; i++) {
     for(j=0; j<mat_P->width; j++){
          fprintf(fp,format1,mat_P->matrix_PP[i][j]);
     }
     fprintf(fp,"\n");
  }

}

void Krn_PrintCxMatrix(dsp_cxMatrix_t *mat_P,char format[], FILE *fp) {
  int n;
  int i,j;
  char format1[256];
  char format2[256];
  char complexNumber[1024];
   char buffer[1024];
   char tsign[3];


  strcpy(format1,"%");
  strcat(format1,format);



  //sprintf(format2,"%s+%si\t",format1,format1);

  fprintf(fp,"%d %d\n",mat_P->height,mat_P->width);

  printf("Printing Complex Matrix (real,imag) Rows=%d Columns=%d\n",mat_P->height,mat_P->width);
  for(i=0; i<mat_P->height; i++) {
     for(j=0; j<mat_P->width; j++){


           if(mat_P->matrix_PP[i][j].im<0) strcpy(tsign," "); else strcpy(tsign,"+");
           sprintf(format2,"%s %s %s i ",format1,tsign,format1);

            sprintf(complexNumber,format2,mat_P->matrix_PP[i][j].re,mat_P->matrix_PP[i][j].im);

            StripSpaces(complexNumber,buffer,1024);
            fprintf(fp,"%s ",buffer);



     }
     fprintf(fp,"\n");
  }

}

void Krn_PrintComplexScalar(cxScalar_t *x_P,char format[], FILE *fp) {
  int n;
  int i;
  char format1[256];
   char format2[256];
   char complexNumber[1024];
   char buffer[1024];
   char tsign[3];

  strcpy(format1,"%");
  strcat(format1,format);





  printf("Printing Complex Scalar\n");

     if(x_P->value.im<0) strcpy(tsign," "); else strcpy(tsign,"+");
     sprintf(format2,"%s %s %s i ",format1,tsign,format1);
     //printf("FORMAT=%s\n",format2);
            sprintf(complexNumber,format2,x_P->value.re,x_P->value.im);


		//	printf("complex number=%s\n",complexNumber);
            StripSpaces(complexNumber,buffer,1024);
            fprintf(fp,"%s",buffer);
            fprintf(fp,"\n");
}



void Krn_PrintVector(doubleVector_t *vec_P,char format[], FILE *fp, int nolen) {
  int n;
  int i;
  char format1[256];


  strcpy(format1,"%");
  strcat(format1,format);
  strcat(format1," ");
  //sprintf(format1,"\%%s \n",format);
  n=vec_P->length;


  //printf("FORMAT=%s FORMAT1=%s\n",format,format1);
  printf("Printing vector with n=%d elements\n",n);
  if(nolen==0) {
     fprintf(fp,"%d\n",n);
  }
  for(i=0; i<n; i++) {

     if(!vec_P->transpose) {
          fprintf(fp,format1,vec_P->vector_P[i]);
          fprintf(fp,"\n");
     }
     else
          fprintf(fp,format1,vec_P->vector_P[i]);
  }
  if(vec_P->transpose) fprintf(fp,"\n");
}

void StripSpaces(char origText[], char desText[], int maxlength) {

int len;
int j;
int i;
int c;

	    len=strlen(origText);
	    // get rid of all spaces including tabs
	    j=0;
	    for(i=0; i<len; i++) {
	       if(i > maxlength-1) continue;
	       c=origText[i];
	       switch(c) {
	          case ' ':

		    break;
		  case '\t':

		    break;
		  default:
		    desText[j]=c;
		    j++;

		    break;
	        }

	    }
	    desText[j]=NULL;

}


void Dsp_MultiplyComplexMatricesComplexVector(dsp_cxMatrix_t *a_P,cxVector_t *vbx_P,cxVector_t *vcx_P)
{
//Warning dimension compatibility assumed prior to call
int i,j,k;
int m;
int n;
int p;
double sumr;
double sumi;


m=a_P->height;
n=a_P->width;

for(k=0; k<m; k++) {
       sumr=0.0;
       sumi=0;
       for(j=0; j<n; j++) {
          sumr += a_P->matrix_PP[k][j].re*vbx_P->vector_P[j].re -a_P->matrix_PP[k][j].im*vbx_P->vector_P[j].im;
	  sumi += a_P->matrix_PP[k][j].re*vbx_P->vector_P[j].im+a_P->matrix_PP[k][j].im*vbx_P->vector_P[j].re;
       }
       vcx_P->vector_P[k].re=sumr;
       vcx_P->vector_P[k].im=sumi;

}

return;

}


void Dsp_MultiplyRealMatrixRealVector(dsp_Matrix_t *ar_P,doubleVector_t *vb_P,doubleVector_t *vc_P)
{
//Warning dimension compatibility assumed prior to call
int i,j,k;
int m;
int n;
int p;
double sum;

m=ar_P->height;
n=ar_P->width;

for(k=0; k<m; k++) {

       sum=0.0;
       for(j=0; j<n; j++) {
          sum += ar_P->matrix_PP[k][j]*vb_P->vector_P[j];
       }
       vc_P->vector_P[k]=sum;


}

return;

}


/*
 * Free the matrix
 * Only the matrix is in the data structure is freed
 */

//void  Dsp_FreeCpxMatrix(dsp_cpxMatrix_t *matrix_P)
void  Dsp_FreeCpxMatrix(dsp_cxMatrix_t *matrix_P)

{
int		i,j;



for(i=0; i< matrix_P->height; i++)
	free(matrix_P->matrix_PP[i]);

free(matrix_P->matrix_PP);
free(matrix_P);


return;
}




void Dsp_MultiplyComplexMatrices(dsp_cxMatrix_t *a_P,dsp_cxMatrix_t *b_P,dsp_cxMatrix_t *c_P)
{
//Warning dimension compatibility assumed prior to call
int i,j,k;
int m;
int n;
int p;
double sumr;
double sumi;


m=a_P->height;
n=a_P->width;
p=b_P->width;
for(k=0; k<p; k++) {
   for(i=0; i<m; i++) {
       sumr=0.0;
       sumi=0;
       for(j=0; j<n; j++) {
          sumr += a_P->matrix_PP[i][j].re*b_P->matrix_PP[j][k].re -a_P->matrix_PP[i][j].im*b_P->matrix_PP[j][k].im;
	  sumi += a_P->matrix_PP[i][j].re*b_P->matrix_PP[j][k].im+a_P->matrix_PP[i][j].im*b_P->matrix_PP[j][k].re;
       }
       c_P->matrix_PP[i][k].re=sumr;
       c_P->matrix_PP[i][k].im=sumi;
   }
}

return;

}

void Dsp_MultiplyComplexMatricesRealVector(dsp_cxMatrix_t *a_P,doubleVector_t*vb_P,cxVector_t *vcx_P)
{
//Warning dimension compatibility assumed prior to call
int i,j,k;
int m;
int n;
int p;
double sumr;
double sumi;


m=a_P->height;
n=a_P->width;

for(k=0; k<m; k++) {

       sumr=0.0;
       sumi=0;
       for(j=0; j<n; j++) {
          sumr += a_P->matrix_PP[k][j].re*vb_P->vector_P[j];
	  sumi += a_P->matrix_PP[k][j].im*vb_P->vector_P[j];
       }
       vcx_P->vector_P[k].re=sumr;
       vcx_P->vector_P[k].im=sumi;

}

return;

}


void Krn_TransposeConjugateMatrix(dsp_cxMatrix_t *mat_P) {
int k;
int j;
cx_t temp;


             /*
              * Transpose
              */
             for(k=0; k<mat_P->height; k++) {
                      for(j=k; j<mat_P->width; j++) {
                           temp.re=mat_P->matrix_PP[k][j].re;
                           temp.im=mat_P->matrix_PP[k][j].im;
                           mat_P->matrix_PP[k][j].re=mat_P->matrix_PP[j][k].re;
			   mat_P->matrix_PP[k][j].im=mat_P->matrix_PP[j][k].im;
                           mat_P->matrix_PP[j][k].re=temp.re;
			   mat_P->matrix_PP[j][k].im=temp.im;
                      }
             }
             for(k=0; k<mat_P->height; k++) {
                      for(j=0; j<mat_P->width; j++) {

			   mat_P->matrix_PP[k][j].im= -mat_P->matrix_PP[k][j].im;

                      }
             }

}









