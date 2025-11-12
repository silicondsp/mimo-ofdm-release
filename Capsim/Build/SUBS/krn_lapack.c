

#include <stdlib.h>
#include <f2cm.h>
#include <clapackm.h>


#include <tcl.h>
#include "vectors.h"


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
// Date: 2006
// 




#if 11111 //DISABLE FOR QT for now

#if 00000
int Krn_ComputeSVDRealMatrix(dsp_Matrix_t *mat_P) {

    int i,j;
    
   
    int fpixel;
    integer M ;
    integer N ;
    integer LDA;
    integer LDU ;
    integer LDVT;
    integer LWORK;
    integer INFO;
    int workLength;
    double* aa_P;
    double* uu_P;
    double* vv_P;
    double* work_P;
    double* s_P;
    
    dsp_Matrix_t img;
    FILE*  fp;
    char *fileName="svdresults.dat";
   
  
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
    
    
    
    
    
       /*
        * allocate space for arrays
        */

       s_P=(double*)calloc(img.height,sizeof(double));
       
       aa_P=(double*)calloc(img.width*img.height,sizeof(double));
       uu_P=(double*)calloc(img.width*img.height,sizeof(double));
       vv_P=(double*)calloc(img.width*img.height,sizeof(double));
	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(double*)calloc(workLength,sizeof(double));

       if(!aa_P || !uu_P || !vv_P || !work_P || !s_P ) {
            fprintf(stderr,"singvaldec: Could not allocate space\n"); 
            return(3);
       
       }
       
       M = img.width;
       N=img.height;
       
      
    
       LDA = M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
	      }
       }


       /*     Subroutine int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
        *  doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
        *  ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
        *   integer *info)
        */

       dgesvd_( "A", "A", &M, &N, aa_P, &LDA, s_P, uu_P, 
          &LDU, vv_P, &LDVT, work_P, &LWORK, &INFO);



       printf("INFO=%d\n",INFO);
       for(i=0; i< img.height; i++) {
           printf("%d\t%f\n",i,s_P[i]);
       
       }


       /*
        * store results
        */
        
       fp=fopen(fileName,"w");
       if(!fp) {
            fprintf(stderr,"sigvaldec: could not open:%s to write\n",fileName);
            return(5);
       }


       fprintf(stderr,"Storing computed resulte in:%s\n",fileName); 


       for(i=0; i< img.height; i++) {
           fprintf(fp,"%d\t%f\n",i,s_P[i]);
       
       }
       
       fclose(fp);
       
       
       free(aa_P);
       free(uu_P);
       free(vv_P);
       free(work_P);
       free(s_P);
    
    
    
    
    
    
    
    
    
    
    
    
     
 #if 0000   
         /*
        * allocate space for arrays
        */

       s_P=(double*)calloc(mat_P->height,sizeof(double));
       
       aa_P=(double*)calloc(mat_P->width,mat_P->height*sizeof(double));
       uu_P=(double*)calloc(mat_P->width,mat_P->height*sizeof(double));
       vv_P=(double*)calloc(mat_P->width,mat_P->height*sizeof(double));
	   if(mat_P->width*mat_P->height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = mat_P->width*mat_P->height*2;

       work_P=(double*)calloc(workLength,sizeof(double));

       if(!aa_P || !uu_P || !vv_P || !work_P || !s_P ) {
            fprintf(stderr,"Singular Value Decomposition: Could not allocate space\n"); 
            return(3);
       
       }
            
       M = mat_P->width;
       N=mat_P->height;
 
       LWORK=workLength;
       
       for ( i= 0; i< mat_P->height; i++ ) {
	      for(j= 0; j< mat_P->width; j++) {
		     aa_P[j*mat_P->width+i]=mat_P->matrix_PP[i][j];
	      }
       }

       
      for ( i= 0; i< mat_P->height; i++ ) {
	      for(j= 0; j< mat_P->width; j++) {
		     printf("%f\t",mat_P->matrix_PP[i][j]);
	      }
	      printf("\n");
       }    
       
       for(i=0; i< mat_P->height*mat_P->width; i++)
               printf("%f \n",aa_P[i]);
       
       /*     Subroutine int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
        *  doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
        *  ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
        *   integer *info)
        */

//       dgesvd_( "A", "A", &M, &N, aa_P, &LDA, s_P, uu_P, 
  //        &LDU, vv_P, &LDVT, work_P, &LWORK, &INFO);


       printf("INFO=%d\n",INFO);
       for(i=0; i< mat_P->height; i++) {
           printf("%d\t%f\n",i,s_P[i]);
       
       }      
       
       /*
        * store results
        */
        
       fp=fopen(fileName,"w");
       if(!fp) {
            fprintf(stderr,"sigvaldec: could not open:%s to write\n",fileName);
            return(5);
       }


       fprintf(stderr,"Storing computed resulte in:%s\n",fileName); 


       for(i=0; i< mat_P->height; i++) {
           fprintf(fp,"%d\t%f\n",i,s_P[i]);
       
       }
       
       fclose(fp);
       
 #if 000      
       free(aa_P);
       free(uu_P);
       free(vv_P);
       free(work_P);
       free(s_P);
 #endif     
#endif
       
}
#endif



int Krn_ComputeEigenvalueRealMatrix(dsp_Matrix_t *mat_P,cxVector_t *e_P,dsp_Matrix_t *vl_P,dsp_Matrix_t *vr_P ) {

    	int i,j;
   	
   	int fpixel;
   	
   	integer M ;
    integer N ;
    
    integer LDA;
    integer LDU ;
    integer LDVV;
    integer LWORK;
    integer INFO;

	int workLength;
    
    double* aa_P;
    double* uu_P;
    double* vv_P;
    double* work_P;
    double* eigenr_P;
    double* eigeni_P;
    
    dsp_Matrix_t img;
    
    FILE*  fp;
    char *fileName="eigenresults.dat";
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
    
    
        /*
        * allocate space for arrays
        */

       eigenr_P=(double*)calloc(img.width,sizeof(double));
       eigeni_P=(double*)calloc(img.width,sizeof(double));
       
       aa_P=(double*)calloc(img.width*img.height,sizeof(double));
       uu_P=(double*)calloc(img.width*img.height,sizeof(double));
       vv_P=(double*)calloc(img.width*img.height,sizeof(double));
	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(double*)calloc(workLength,sizeof(double));

       if(!aa_P || !uu_P || !vv_P || !work_P || !eigenr_P || !eigeni_P) {
            fprintf(stderr,"eigen: Could not allocate space\n"); 
            return(3);
       
       }
       
       M = img.width;
       N=img.height;
       
       if(M != N) {
            fprintf(stderr,"eigen: Matrix must be square\n"); 
            return(4);
       
       }
    
    
       LDA = M;
       LDU = M;
       LDVV = N;

	   LWORK=workLength;

       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
	      }
       }


       /*
        * compute eigenvalues and eigenvectors
        */
       dgeev_( "V", "V", &M, aa_P, &LDA, eigenr_P, eigeni_P,uu_P, 
          &LDU, vv_P, &LDVV, work_P, &LWORK, &INFO);


       fprintf(stderr,"INFO=%d\n",INFO);
       for(i=0; i< img.height; i++) {
           printf("%d\t%f\t%f\n",i,eigenr_P[i],eigeni_P[i]);
       
       }


       /*
        * store eigenvalues
        */
        
       fp=fopen(fileName,"w");
       if(!fp) {
            fprintf(stderr,"eigen: could not open:%s to write\n",fileName); 
            return(5);
       }


       fprintf(stderr,"Storing computed eigenvalues in:%s\n",fileName); 


       for(i=0; i< img.height; i++) {
           fprintf(fp,"%d\t%f\t%f\n",i,eigenr_P[i],eigeni_P[i]);
       
       }
       
       fclose(fp);
       
       if(e_P) {
           e_P->length=mat_P->height;
	   for(i=0; i<e_P->length; i++) {
	       e_P->vector_P[i].re=eigenr_P[i];
	       e_P->vector_P[i].im=eigeni_P[i];
	       
	       printf("--- %d %f %f\n",i,e_P->vector_P[i].re,e_P->vector_P[i].im);
           }
       }

       if(vr_P) {       
         // u_P->width=M;
	 // u_P->height=M;
	  for(i=0;i<M; i++) {
	     for(j=0; j<M; j++) {
	         vr_P->matrix_PP[i][j]=uu_P[j*M+i];
		 printf("VR %d %d  %e\n",i,j,vr_P->matrix_PP[i][j]);
	     }	  
	  }       
       }
      if(vl_P) {       
          //v_P->width=N;
	  //v_P->height=N;
	  for(i=0;i<N; i++) {
	     for(j=0; j<N; j++) {
	         vl_P->matrix_PP[i][j]=vv_P[j*N+i];
		 printf("VL %d %d  %e \n",i,j,vl_P->matrix_PP[i][j]);
	     }	  
	  }       
       }       
         
       
       
       
       free(aa_P);
       free(uu_P);
       free(vv_P);
       free(work_P);
       free(eigenr_P);
       free(eigeni_P);   
       
}

//+++++

int Krn_ComputeEigenvalueComplexMatrix(dsp_cxMatrix_t *mat_P,cxVector_t *e_P,dsp_cxMatrix_t *vl_P,dsp_cxMatrix_t *vr_P ) {

    	int i,j;
   	
   	int fpixel;
   	
   	integer M ;
    integer N ;
    
    integer LDA;
    integer LDU ;
    integer LDVV;
    integer LWORK;
    integer INFO;

	int workLength;
    
    doublecomplex* aa_P;
    doublecomplex* uu_P;
    doublecomplex* vv_P;
    doublecomplex* work_P;
    doublecomplex* eigen_P;
	
	doublereal *rwork_P;
   
    
    dsp_cxMatrix_t img;
    
    FILE*  fp;
    char *fileName="eigenresults.dat";
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
    
    
        /*
        * allocate space for arrays
        */

       eigen_P=(doublecomplex*)calloc(img.width,sizeof(doublecomplex));
       
       aa_P=(doublecomplex*)calloc(img.width*img.height,sizeof(doublecomplex));
       uu_P=(doublecomplex*)calloc(img.width*img.height,sizeof(doublecomplex));
       vv_P=(doublecomplex*)calloc(img.width*img.height,sizeof(doublecomplex));
	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(doublecomplex*)calloc(workLength,sizeof(doublecomplex));
	   
	   rwork_P=(doublereal*)calloc(2*img.width,sizeof(doublereal));


       if(!aa_P || !uu_P || !vv_P || !work_P || !rwork_P ||  !eigen_P ) {
            fprintf(stderr,"eigen complex: Could not allocate space\n"); 
            return(3);
       
       }
       
       M = img.width;
       N=img.height;
       
       if(M != N) {
            fprintf(stderr,"eigen complex: Matrix must be square\n"); 
            return(4);
       
       }
    
    
       LDA = M;
       LDU = M;
       LDVV = N;

	   LWORK=workLength;

       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
		     aa_P[j*img.width+i].r= img.matrix_PP[i][j].re;
		     aa_P[j*img.width+i].i= img.matrix_PP[i][j].im;
	      }
       }


       /*
        * compute eigenvalues and eigenvectors
        */
       zgeev_( "V", "V", &M, aa_P, &LDA, eigen_P,uu_P, 
          &LDU, vv_P, &LDVV, work_P, &LWORK, rwork_P, &INFO);


       fprintf(stderr,"INFO=%d\n",INFO);
       for(i=0; i< img.height; i++) {
           printf("%d\t%f\t%f\n",i,eigen_P[i].r,eigen_P[i].i);
       
       }


       /*
        * store eigenvalues
        */
        
       fp=fopen(fileName,"w");
       if(!fp) {
            fprintf(stderr,"eigen complex: could not open:%s to write\n",fileName); 
            return(5);
       }


       fprintf(stderr,"Storing computed eigenvalues in:%s\n",fileName); 


       for(i=0; i< img.height; i++) {
           fprintf(fp,"%d\t%f\t%f\n",i,eigen_P[i].r,eigen_P[i].i);
       
       }
       
       fclose(fp);
       
       if(e_P) {
           e_P->length=mat_P->height;
	   for(i=0; i<e_P->length; i++) {
	       e_P->vector_P[i].re=eigen_P[i].r;
	       e_P->vector_P[i].im=eigen_P[i].i;
	       
	       printf("--- %d %f %f\n",i,e_P->vector_P[i].re,e_P->vector_P[i].im);
           }
       }

       if(vr_P) {       
         // u_P->width=M;
	 // u_P->height=M;
	  for(i=0;i<M; i++) {
	     for(j=0; j<M; j++) {
	         vr_P->matrix_PP[i][j].re=uu_P[j*M+i].r;
	         vr_P->matrix_PP[i][j].im=uu_P[j*M+i].i;
	         
	         
		 printf("VR %d %d  %e %e \n",i,j,vr_P->matrix_PP[i][j].re,vr_P->matrix_PP[i][j].im);
	     }	  
	  }       
       }
      if(vl_P) {       
          //v_P->width=N;
	  //v_P->height=N;
	  for(i=0;i<N; i++) {
	     for(j=0; j<N; j++) {
	         vl_P->matrix_PP[i][j].re=vv_P[j*N+i].r;
	         vl_P->matrix_PP[i][j].im=vv_P[j*N+i].i;
		 printf("VL %d %d  %e %e\n",i,j,vl_P->matrix_PP[i][j].re,vl_P->matrix_PP[i][j].im);
	     }	  
	  }       
       }       
         
       
       
       
       free(aa_P);
       free(uu_P);
       free(vv_P);
       free(work_P);
       free(eigen_P);
       free(rwork_P);   

       return(0);
       
}




//+++++


int Krn_ComputeSVDCxMatrix(dsp_cxMatrix_t *mat_P, doubleVector_t *ss_P,dsp_cxMatrix_t *u_P, dsp_cxMatrix_t *v_P){

  	int i,j;
   	dsp_cxMatrix_t img;
   	int fpixel;
        int len;
   	
   	integer M ;
    integer N ;
    
    integer LDA;
    integer LDU ;
    integer LDVT;
    integer LWORK;
    doublereal RWORK;
    integer INFO;

	int workLength;
    
    doublecomplex* aa_P;
    doublecomplex* uu_P;
    doublecomplex* vv_P;
    doublecomplex* work_P;
    doublereal* rwork_P;
    doublereal* s_P;
    
    char *fileName="cxsvdresults.dat";
    FILE *fp;
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
   
      /*
        * allocate space for arrays
        */

       if(img.width > img.height) 
               len=img.height;
           else 
               len=img.width;

       s_P=(doublereal*)calloc(len,sizeof(doublereal));
       
       aa_P=(doublecomplex*)calloc(img.width*img.height,sizeof(doublecomplex));
       uu_P=(doublecomplex*)calloc(img.height*img.height,sizeof(doublecomplex));
       vv_P=(doublecomplex*)calloc(img.width*img.width,sizeof(doublecomplex));

	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(doublecomplex*)calloc(workLength,sizeof(doublecomplex));


       rwork_P=(doublereal*)calloc(10*len,sizeof(doublereal));

       if(!aa_P || !uu_P || !vv_P || !work_P || !s_P || !rwork_P) {
            fprintf(stderr,"cxsvd: Could not allocate space\n"); 
            return(3);
       
       }
       
       N = img.width;
       M=img.height;
       
      
    
       LDA = M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
//		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
//printf("%f,%f  ", aa_P[j*img.width+i].r,aa_P[j*img.width+i].i);
                 //  aa_P[i*img.height+j]=img.matrix_PP[i][j];
		 aa_P[j*img.height+i].r=img.matrix_PP[i][j].re;
		 aa_P[j*img.height+i].i=img.matrix_PP[i][j].im;
//DEBUG                   printf("%f,%f  ", aa_P[j*img.height+i].r,aa_P[j*img.height+i].i);
	      }
//DEBUG printf("\n");
       }


       /*     Subroutine int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
        *  doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
        *  ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
        *   integer *info)
        */


/* Subroutine */ /* int cgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	complex *a, integer *lda, real *s, complex *u, integer *ldu, complex *
	vt, integer *ldvt, complex *work, integer *lwork, real *rwork_P, 
	integer *info) */
/* Subroutine  int zgesvd_(char *jobu, char *jobvt, integer *m, integer *n,
        doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u,
        integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work,
        integer *lwork, doublereal *rwork, integer *info)
*/


       zgesvd_( "A", "A", &M, &N, aa_P, &LDA, s_P, uu_P, 
          &LDU, vv_P, &LDVT, work_P, &LWORK, rwork_P, &INFO);


       printf("INFO=%d Order=%d len=%d ;\nSingular Values:\n",INFO,img.height, len);
       for(i=0; i< img.height; i++) {
           printf("%d\t%f\n",i,s_P[i]);
       
       }

//   return(0); //DEBUG=====================================

       /*
        * store results
        */
        


#if 000
       fprintf(stderr,"Storing computed resulte in:%s\n",fileName); 

       fp=fopen(fileName,"w");
       if(fp) {

            for(i=0; i< img.height; i++) {
                 fprintf(fp,"%d\t%f\n",i,s_P[i]);
       
            }
            fclose(fp);
       }
#endif
       if(ss_P) {
           ss_P->length=len;
	   for(i=0; i<len; i++) {
	       ss_P->vector_P[i]=s_P[i];
//DEBUG 	       printf("ss_P --- %d %f\n",i,ss_P->vector_P[i]);
 //	       printf("--- %d %f\n",i,ss_P->vector_P[i]);
           }
       }

       if(u_P) {       
         // u_P->width=M;
	 // u_P->height=M;
	  for(i=0;i<M; i++) {
	     for(j=0; j<M; j++) {
	         u_P->matrix_PP[i][j].re=uu_P[j*M+i].r;
	         u_P->matrix_PP[i][j].im=uu_P[j*M+i].i;

//DEBUG 		 printf("UU %d %d  %e %e \n",i,j,u_P->matrix_PP[i][j].r,u_P->matrix_PP[i][j].i);
 //		 printf("UU %d %d  %e %e \n",i,j,u_P->matrix_PP[i][j].re,u_P->matrix_PP[i][j].im);
	     }	  
	  }       
       }
      if(v_P) {       
          //v_P->width=N;
	  //v_P->height=N;
	  for(i=0;i<N; i++) {
	     for(j=0; j<N; j++) {
	         v_P->matrix_PP[i][j].re=vv_P[j*N+i].r;
	         v_P->matrix_PP[i][j].im=vv_P[j*N+i].i;
//DEBUG 		 printf("VV %d %d  %e %e  \n",i,j,v_P->matrix_PP[i][j].r,v_P->matrix_PP[i][j].i);
// 		 printf("VV %d %d  %e %e  \n",i,j,v_P->matrix_PP[i][j].re,v_P->matrix_PP[i][j].im);
	     }	  
	  }       
       }       
       
#if 111       
       free(aa_P);
       free(uu_P);
       free(vv_P);
       free(work_P);
       free(rwork_P);
       free(s_P);
#endif
        return(0);

}


//++++


int Krn_ComputeSVDRealMatrix(dsp_Matrix_t *mat_P, doubleVector_t *ss_P,dsp_Matrix_t *u_P, dsp_Matrix_t *v_P){

  	int i,j;
   	dsp_Matrix_t img;
   	int fpixel;
        int len;
   	
   	integer M ;
    integer N ;
    
    integer LDA;
    integer LDU ;
    integer LDVT;
    integer LWORK;
    doublereal RWORK;
    integer INFO;

	int workLength;
    
    double* aa_P;
    double* uu_P;
    double* vv_P;
    double* work_P;
    doublereal* rwork_P;
    doublereal* s_P;
    
    char *fileName="svdresults.dat";
    FILE *fp;
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
   
      /*
        * allocate space for arrays
        */

       if(img.width > img.height) 
               len=img.height;
           else 
               len=img.width;

       s_P=(doublereal*)calloc(len,sizeof(doublereal));
       
       aa_P=(double*)calloc(img.width*img.height,sizeof(double));
       uu_P=(double*)calloc(img.width*img.width,sizeof(double));
       vv_P=(double*)calloc(img.height*img.height,sizeof(double));

	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(double*)calloc(workLength,sizeof(double));


       rwork_P=(doublereal*)calloc(5*len,sizeof(doublereal));

       if(!aa_P || !uu_P || !vv_P || !work_P || !s_P || !rwork_P) {
            fprintf(stderr,"RealSVD: Could not allocate space\n"); 
            return(3);
       
       }
       
       M = img.width;
       N=img.height;
       
      
    
       LDA = M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
//		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
//printf("%f,%f  ", aa_P[j*img.width+i].r,aa_P[j*img.width+i].i);
                 //  aa_P[i*img.height+j]=img.matrix_PP[i][j];
		 aa_P[j*img.height+i]=img.matrix_PP[i][j];
       //DEBUG    printf("%f ", aa_P[j*img.height+i]);
	      }
//DEBUG printf("\n");
       }


       /*     Subroutine int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
        *  doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
        *  ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
        *   integer *info)
        */


/* Subroutine */ /* int cgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	complex *a, integer *lda, real *s, complex *u, integer *ldu, complex *
	vt, integer *ldvt, complex *work, integer *lwork, real *rwork_P, 
	integer *info) */
/* Subroutine  int zgesvd_(char *jobu, char *jobvt, integer *m, integer *n,
        doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u,
        integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work,
        integer *lwork, doublereal *rwork, integer *info)
*/


       dgesvd_( "A", "A", &M, &N, aa_P, &LDA, s_P, uu_P, 
          &LDU, vv_P, &LDVT, work_P, &LWORK, &INFO);



       printf("INFO=%d Order=%d\nSingular Values: \n",INFO,img.height);
       for(i=0; i< img.height; i++) {
           printf("%d\t%f\n",i,s_P[i]);
       
       }


       /*
        * store results
        */
        


#if 000
       fprintf(stderr,"Storing computed resulte in:%s\n",fileName); 

       fp=fopen(fileName,"w");
       if(fp) {

            for(i=0; i< img.height; i++) {
                 fprintf(fp,"%d\t%f\n",i,s_P[i]);
       
            }
            fclose(fp);
       }
#endif
       if(ss_P) {
           ss_P->length=len;
	   for(i=0; i<len; i++) {
	       ss_P->vector_P[i]=s_P[i];
	       printf("--- %d %f\n",i,ss_P->vector_P[i]);
           }
       }

       if(u_P) {       
         // u_P->width=M;
	 // u_P->height=M;
	  for(i=0;i<M; i++) {
	     for(j=0; j<M; j++) {
	         u_P->matrix_PP[i][j]=uu_P[j*M+i];
      //DEBUG		 printf("UU %d %d  %e\n",i,j,u_P->matrix_PP[i][j]);
	     }	  
	  }       
       }
      if(v_P) {       
          //v_P->width=N;
	  //v_P->height=N;
	  for(i=0;i<N; i++) {
	     for(j=0; j<N; j++) {
	         v_P->matrix_PP[i][j]=vv_P[j*N+i];
	      //DEBUG	 printf("VV %d %d  %e \n",i,j,v_P->matrix_PP[i][j]);
	     }	  
	  }       
       }       
       
#if 0000 //CHECK !!!       
       free(aa_P);
       free(uu_P);
       free(vv_P);
       free(work_P);
       free(rwork_P);
       free(s_P);
#endif

}



//++++



int Krn_ComputeInverseCxMatrix(dsp_cxMatrix_t *mat_P, dsp_cxMatrix_t *inverse_P){

  	int i,j;
   	dsp_cxMatrix_t img;
   	int fpixel;
        int len;
   	
   	integer M ;
    integer N ;
    
    integer LDA;
    integer LDU ;
    integer LDVT;
    integer LWORK;
    doublereal RWORK;
    integer INFO;

	int workLength;
    
    doublecomplex* aa_P; 
    doublecomplex* uu_P;
    doublecomplex* vv_P;
    doublecomplex* work_P;
    doublereal* rwork_P;
    doublereal* s_P;
    
    char *fileName="cxsvdresults.dat";
    FILE *fp;
    
    integer *ipiv;
    
    if(mat_P->width != mat_P->height) {
         fprintf(stderr,"CxMatrixInverse: matrix must be square\n");
    }
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
   
      /*
        * allocate space for arrays
        */

       if(img.width > img.height) 
               len=img.height;
           else 
               len=img.width;

       ipiv=(integer*)calloc(len,sizeof(len));
       
       aa_P=(doublecomplex*)calloc(img.width*img.height,sizeof(doublecomplex));
 //      uu_P=(doublecomplex*)calloc(img.width*img.width,sizeof(doublecomplex));
  //     vv_P=(doublecomplex*)calloc(img.height*img.height,sizeof(doublecomplex));

	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(doublecomplex*)calloc(workLength,sizeof(doublecomplex));


       rwork_P=(doublereal*)calloc(5*len,sizeof(doublereal));

       if(!aa_P || !ipiv  ) {
            fprintf(stderr,"CxMatrixInverse: Could not allocate space\n"); 
            return(300);
       
       }
       
       M = img.width;
       N=img.height;
       
      
    
       LDA = M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
//		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
//printf("%f,%f  ", aa_P[j*img.width+i].r,aa_P[j*img.width+i].i);
                 //  aa_P[i*img.height+j]=img.matrix_PP[i][j];
		 aa_P[j*img.height+i].r=img.matrix_PP[i][j].re;
		  aa_P[j*img.height+i].i=img.matrix_PP[i][j].im;
      //DEBUG                   printf("%f,%f  ", aa_P[j*img.height+i].r,aa_P[j*img.height+i].i);
	      }
printf("\n");
       }


       /*     Subroutine int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
        *  doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
        *  ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
        *   integer *info)
        */


/* Subroutine */ /* int cgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	complex *a, integer *lda, real *s, complex *u, integer *ldu, complex *
	vt, integer *ldvt, complex *work, integer *lwork, real *rwork_P, 
	integer *info) */
/* Subroutine  int zgesvd_(char *jobu, char *jobvt, integer *m, integer *n,
        doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u,
        integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work,
        integer *lwork, doublereal *rwork, integer *info)
*/


       zgetrf_(  &M, &N, aa_P, &LDA, ipiv,  &INFO);

       zgetri_( &M, aa_P, &LDA, ipiv, work_P, &LWORK,  &INFO);


       /*
        * store results
        */
       if(inverse_P) {       
 	     for(i=0;i<M; i++) {
	        for(j=0; j<M; j++) {
	            inverse_P->matrix_PP[i][j].re=aa_P[j*M+i].r;
	            inverse_P->matrix_PP[i][j].im=aa_P[j*M+i].i;

	      //DEBUG	        printf("Inverse %d %d  %e %e \n",i,j,inverse_P->matrix_PP[i][j].r,inverse_P->matrix_PP[i][j].i);
	        }	  
	     }       
       }        


     return(INFO);
       
#if 111       
       free(aa_P);
         free(work_P);
       free(rwork_P);
       free(ipiv);
#endif

}




int Krn_ComputeInverseRealMatrix(dsp_Matrix_t *mat_P, dsp_Matrix_t *inverse_P){

  	int i,j;
   	dsp_Matrix_t img;
   	int fpixel;
        int len;
   	
   	integer M ;
    integer N ;
    
    integer LDA;
    integer LDU ;
    integer LDVT;
    integer LWORK;
    doublereal RWORK;
    integer INFO;

	int workLength;
    
    double* aa_P; 
    double* work_P;
    doublereal* rwork_P;
    doublereal* s_P;
    
    char *fileName="inverseresults.dat";
    FILE *fp;
    
    integer *ipiv;
    
    if(mat_P->width != mat_P->height) {
         fprintf(stderr,"MatrixInverse: matrix must be square\n");
    }
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
   
      /*
        * allocate space for arrays
        */

       if(img.width > img.height) 
               len=img.height;
           else 
               len=img.width;

       ipiv=(integer*)calloc(len,sizeof(len));
       
       aa_P=(double *)calloc(img.width*img.height,sizeof(double));
 
	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(double *)calloc(workLength,sizeof(double));


       rwork_P=(doublereal*)calloc(5*len,sizeof(doublereal));

       if(!aa_P || !ipiv  ) {
            fprintf(stderr,"MatrixInverse: Could not allocate space\n"); 
            return(300);
       
       }
       
       M = img.width;
       N=img.height;
       
      
    
       LDA = M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
 	     aa_P[j*img.width+i] =img.matrix_PP[i][j] ;
 	  
//printf("%f,%f  ", aa_P[j*img.width+i].r,aa_P[j*img.width+i].i);
            //       aa_P[i*img.height+j]=img.matrix_PP[i][j];
      //DEBUG		 aa_P[j*img.height+i]=img.matrix_PP[i][j];
                   printf("%f ", aa_P[j*img.height+i]);
	      }
printf("\n");
       }


       /*     Subroutine int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
        *  doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
        *  ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
        *   integer *info)
        */


/* Subroutine */ /* int cgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	complex *a, integer *lda, real *s, complex *u, integer *ldu, complex *
	vt, integer *ldvt, complex *work, integer *lwork, real *rwork_P, 
	integer *info) */
/* Subroutine  int zgesvd_(char *jobu, char *jobvt, integer *m, integer *n,
        doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u,
        integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work,
        integer *lwork, doublereal *rwork, integer *info)
*/


       dgetrf_(  &M, &N, aa_P, &LDA, ipiv,  &INFO);

       dgetri_( &M, aa_P, &LDA, ipiv, work_P, &LWORK,  &INFO);


       /*
        * store results
        */
       if(inverse_P) {       
 	     for(i=0;i<M; i++) {
	        for(j=0; j<M; j++) {
	            inverse_P->matrix_PP[i][j]=aa_P[j*M+i];
	      //DEBUG	        printf("Inverse %d %d  %e\n",i,j,inverse_P->matrix_PP[i][j]);
	        }	  
	     }       
       }        


     return(INFO);
       
#if 11       
       free(aa_P);
       free(work_P);
       free(rwork_P);
       free(ipiv);
#endif

}



int Krn_ComputeQRCxMatrix(dsp_cxMatrix_t *mat_P,dsp_cxMatrix_t *Q_P, dsp_cxMatrix_t *R_P){

  	int i,j;
   	dsp_cxMatrix_t img;
   	int fpixel;
        int len;
   	
   	integer M ;
    integer N ;
    integer K ;
    
    integer LDA;
    integer LDU ;
    integer LDVT;
    integer LWORK;
    doublereal RWORK;
    integer INFO;

	int workLength;
    
    doublecomplex* aa_P;
    doublecomplex* tau_P;
    doublecomplex* work_P;
    doublereal* rwork_P;
    
    char *fileName="cxqrresults.dat";
    FILE *fp;
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
   
    M=img.height;
    N=img.width;   
    if(M>N ) K=N; else K=M;

   
      /*
        * allocate space for arrays
        */

       if(img.width > img.height) 
               len=img.height;
           else 
               len=img.width;

       
       aa_P=(doublecomplex*)calloc(img.height*img.height,sizeof(doublecomplex));
      // tau_P=(doublecomplex*)calloc(K,sizeof(doublecomplex));
      tau_P=(doublecomplex*)calloc(M,sizeof(doublecomplex));
   
	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(doublecomplex*)calloc(workLength,sizeof(doublecomplex));


      // rwork_P=(doublereal*)calloc(10*len,sizeof(doublereal));

       if(!aa_P || !work_P ) {
            fprintf(stderr,"Complex QR: Could not allocate space\n"); 
            return(300);
       
       }
       
       
      
    
       LDA = M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
//		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
//printf("%f,%f  ", aa_P[j*img.width+i].r,aa_P[j*img.width+i].i);
                 //  aa_P[i*img.height+j]=img.matrix_PP[i][j];
		 aa_P[j*img.height+i].r=img.matrix_PP[i][j].re;
		 aa_P[j*img.height+i].i=img.matrix_PP[i][j].im;
            //DEBUG             printf("%f,%f  ", aa_P[j*img.height+i].r,aa_P[j*img.height+i].i);
	      }
printf("\n");
       }


       /*     Subroutine int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
        *  doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
        *  ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
        *   integer *info)
        */


/* Subroutine */ /* int cgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	complex *a, integer *lda, real *s, complex *u, integer *ldu, complex *
	vt, integer *ldvt, complex *work, integer *lwork, real *rwork_P, 
	integer *info) */
/* Subroutine  int zgesvd_(char *jobu, char *jobvt, integer *m, integer *n,
        doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u,
        integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work,
        integer *lwork, doublereal *rwork, integer *info)
*/

      zgeqrf_(&M, &N, aa_P, &LDA, 
	       tau_P, work_P, &LWORK, &INFO);




       printf("INFO=%d\n",INFO);
       //DEBUG      printf("Complex QR: R Matrix on diagonal and upper\n");
       for(i=0; i< M; i++) {
           for(j=i; j< N; j++){
                   R_P->matrix_PP[i][j].re=aa_P[j*M+i].r;
                    R_P->matrix_PP[i][j].im=aa_P[j*M+i].i;
                   //DEBUG      printf("%f,%f\t",aa_P[j*M+i].r,aa_P[j*M+i].i);
           }
            //DEBUG     printf("\n");
       }
       
       K=M;
#if 1
       zungqr_(&M, &M, &K,aa_P, &LDA, 
	       tau_P, work_P, &LWORK, &INFO);
#endif	       
	       
	       
      
       //DEBUG     printf("Complex QR: Q MAtrix\n");
       for(i=0; i< M; i++) {
           for(j=0; j< M; j++){
                 Q_P->matrix_PP[i][j].re=aa_P[j*M+i].r;
                 Q_P->matrix_PP[i][j].im=aa_P[j*M+i].i;
                //DEBUG         printf("%f,%f\t",aa_P[j*M+i].r,aa_P[j*M+i].i);
           }
             //DEBUG    printf("\n");
       }

         return(0);
        
#if 111       
       free(aa_P);
        free(work_P);
       free(tau_P);

 #endif

}

/*
 * (b - Ax)
 */

int Krn_ComputeLinearSystemCxMatrix(dsp_cxMatrix_t *mat_P,cxVector_t *b_P, cxVector_t *x_P){

  	int i,j;
   	dsp_cxMatrix_t img;
   	int fpixel;
        int len;
   	
   	integer M ;
    integer N ;
    integer K ;
    
    integer LDA;
    integer LDB;
    integer LDU ;
    integer LDVT;
    integer NRHS=1;
    integer LWORK;
    doublereal RWORK;
    integer INFO;

	int workLength;
    
    doublecomplex* aa_P;
    doublecomplex* tau_P;
    doublecomplex* work_P;
    doublecomplex* xx_P;
    doublecomplex* bb_P;
    doublereal* rwork_P;
    
    char *fileName="cxqrresults.dat";
    FILE *fp;
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
   
    M=img.height;
    N=img.width;   
    if(M>N ) K=N; else K=M;

   
      /*
        * allocate space for arrays
        */

       if(img.width > img.height) 
               len=img.height;
           else 
               len=img.width;

       
       aa_P=(doublecomplex*)calloc(img.height*img.height,sizeof(doublecomplex));
      // tau_P=(doublecomplex*)calloc(K,sizeof(doublecomplex));
      
      xx_P=(doublecomplex*)calloc(N,sizeof(doublecomplex));
      
      bb_P=(doublecomplex*)calloc(M+N,sizeof(doublecomplex));
      
      
   
	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(doublecomplex*)calloc(workLength,sizeof(doublecomplex));


      // rwork_P=(doublereal*)calloc(10*len,sizeof(doublereal));

       if(!aa_P || !work_P || !xx_P || !bb_P) {
            fprintf(stderr,"Complex Linear System: Could not allocate space\n"); 
            return(300);
       
       }
       
       
      
    
       LDA = M;
       LDB= M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
//		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
//printf("%f,%f  ", aa_P[j*img.width+i].r,aa_P[j*img.width+i].i);
                 //  aa_P[i*img.height+j]=img.matrix_PP[i][j];
		 aa_P[j*img.height+i].r=img.matrix_PP[i][j].re;
		 aa_P[j*img.height+i].i=img.matrix_PP[i][j].im;

      //DEBUG                   printf("%f,%f  ", aa_P[j*img.height+i].r,aa_P[j*img.height+i].i);
	      }
      //DEBUG printf("\n");
       }

      for(i=0; i< M; i++) {
                   bb_P[i].r=b_P->vector_P[i].re;      
                   bb_P[i].i=b_P->vector_P[i].im;             
       }
       
       /*     Subroutine int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
        *  doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
        *  ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
        *   integer *info)
        */


/* Subroutine */ /* int cgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	complex *a, integer *lda, real *s, complex *u, integer *ldu, complex *
	vt, integer *ldvt, complex *work, integer *lwork, real *rwork_P, 
	integer *info) */
/* Subroutine  int zgesvd_(char *jobu, char *jobvt, integer *m, integer *n,
        doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u,
        integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work,
        integer *lwork, doublereal *rwork, integer *info)
*/


/* Subroutine
     int zgels_(char *trans, integer *m, integer *n, integer *
        nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb,
        doublecomplex *work, integer *lwork, integer *info)
*/
	

      zgels_("N",&M, &N, &NRHS,aa_P, &LDA, bb_P, &LDB, work_P, &LWORK, &INFO);




       printf("INFO=%d\n",INFO);
//DEBUG       printf("Linear System Solution: x vector N=%d\n",N);
       for(i=0; i< N; i++) {
                   x_P->vector_P[i].re=bb_P[i].r;
                   x_P->vector_P[i].im=bb_P[i].i;
                   
      //DEBUG             printf("%f\t%f\n",bb_P[i].r,bb_P[i].i);
        }
       
 

         return(0);
        
#if 111       
       free(aa_P);
       free(bb_P);
        free(xx_P);
        free(work_P);
#endif

}


int Krn_ComputeLinearSystemRealMatrix(dsp_Matrix_t *mat_P,doubleVector_t *b_P, doubleVector_t *x_P) {


    int i,j;
    dsp_Matrix_t img;
    int fpixel;
    int len;
   	
    integer M ;
    integer N ;
    integer K ;
    
    integer LDA;
    integer LDB;
    integer LDU ;
    integer LDVT;
    integer NRHS=1;
    integer LWORK;
    doublereal RWORK;
    integer INFO;

    int workLength;
    
    doublereal* aa_P;
    doublereal* tau_P;
    doublereal* work_P;
    doublereal* xx_P;
    doublereal* bb_P;
    doublereal* rwork_P;
    
    FILE *fp;
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
   
    M=img.height;
    N=img.width;   
    if(M>N ) K=N; else K=M;

   
      /*
        * allocate space for arrays
        */

       if(img.width > img.height) 
               len=img.height;
           else 
               len=img.width;

       
       aa_P=(doublereal*)calloc(img.height*img.height,sizeof(doublereal));
      // tau_P=(doublecomplex*)calloc(K,sizeof(doublecomplex));
      
      xx_P=(doublereal*)calloc(N,sizeof(doublereal));
      
      bb_P=(doublereal*)calloc(M+N,sizeof(doublereal));
      
      
   
	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(doublereal*)calloc(workLength,sizeof(doublereal));


      // rwork_P=(doublereal*)calloc(10*len,sizeof(doublereal));

       if(!aa_P || !work_P || !xx_P || !bb_P) {
            fprintf(stderr,"Real Linear System: Could not allocate space\n"); 
            return(300);
       
       }
       
       
      
    
       LDA = M;
       LDB= M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
//		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
//printf("%f,%f  ", aa_P[j*img.width+i].r,aa_P[j*img.width+i].i);
                 //  aa_P[i*img.height+j]=img.matrix_PP[i][j];
		 aa_P[j*img.height+i]=img.matrix_PP[i][j];
            //DEBUG       printf("%f   ", aa_P[j*img.height+i]);
	      }
//DEBUG printf("\n");
       }

      for(i=0; i< M; i++) {
                   bb_P[i]=b_P->vector_P[i];                   
       }
       



/* Subroutine  int dgels_(char *trans, integer *m, integer *n, integer *
        nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb,
        doublereal *work, integer *lwork, integer *info)

*/	

      dgels_("N",&M, &N, &NRHS,aa_P, &LDA, bb_P, &LDB, work_P, &LWORK, &INFO);




       printf("INFO=%d\n",INFO);
//DEBUG       printf("Linear System Solution: x vector N=%d\n",N);
       for(i=0; i< N; i++) {
                   x_P->vector_P[i]=bb_P[i];
                   
//DEBUG                   printf("%f\n",bb_P[i]);
        }
       
 

         return(0);
        
#if 111      
       free(aa_P);
       free(bb_P);
       free(xx_P);
       free(work_P);
 #endif


}




int Krn_ComputeQRRealMatrix(dsp_Matrix_t *mat_P,dsp_Matrix_t *Q_P, dsp_Matrix_t *R_P){

  	int i,j;
   	dsp_Matrix_t img;
   	int fpixel;
        int len;
   	
   	integer M ;
    integer N ;
    integer K ;
    
    integer LDA;
    integer LDU ;
    integer LDVT;
    integer LWORK;
    doublereal RWORK;
    integer INFO;

	int workLength;
    
    doublereal* aa_P;
    doublereal* tau_P;
    doublereal* work_P;
    doublereal* rwork_P;
    
    FILE *fp;
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
   
    M=img.height;
    N=img.width;   
    if(M>N ) K=N; else K=M;

   
      /*
        * allocate space for arrays
        */

       if(img.width > img.height) 
               len=img.height;
           else 
               len=img.width;

       
       aa_P=(doublereal*)calloc(img.height*img.height,sizeof(doublereal));
      // tau_P=(doublecomplex*)calloc(K,sizeof(doublecomplex));
      tau_P=(doublereal*)calloc(M,sizeof(doublereal));
   
	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(doublereal*)calloc(workLength,sizeof(doublereal));


      // rwork_P=(doublereal*)calloc(10*len,sizeof(doublereal));

       if(!aa_P || !work_P ) {
            fprintf(stderr,"Real QR: Could not allocate space\n"); 
            return(300);
       
       }
       
       
      
    
       LDA = M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
//		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
//printf("%f,%f  ", aa_P[j*img.width+i].r,aa_P[j*img.width+i].i);
                 //  aa_P[i*img.height+j]=img.matrix_PP[i][j];
		 aa_P[j*img.height+i]=img.matrix_PP[i][j];
//DEBUG                   printf("%f  ", aa_P[j*img.height+i]);
	      }
//DEBUG              printf("\n");
       }

/* Subroutine  int dgeqrf_(integer *m, integer *n, doublereal *a, integer *
        lda, doublereal *tau, doublereal *work, integer *lwork, integer *info)
*/   


      dgeqrf_(&M, &N, aa_P, &LDA, 
	       tau_P, work_P, &LWORK, &INFO);




       printf("INFO=%d\n",INFO);
//DEBUG       printf("Real QR: R Matrix on diagonal and upper\n");
       for(i=0; i< M; i++) {
           for(j=i; j< N; j++){
                   R_P->matrix_PP[i][j]=aa_P[j*M+i];
                   printf("%f\t",aa_P[j*M+i]);
           }
//DEBUG           printf("\n");
       }
       
       K=M;
#if 1
/* Subroutine  int dorgqr_(integer *m, integer *n, integer *k, doublereal *
        a, integer *lda, doublereal *tau, doublereal *work, integer *lwork,
        integer *info)
*/
	
       dorgqr_(&M, &M, &K,aa_P, &LDA, 
	       tau_P, work_P, &LWORK, &INFO);
#endif	       
	       
	       
      
//DEBUG      printf("Real QR: Q MAtrix\n");
       for(i=0; i< M; i++) {
           for(j=0; j< M; j++){
                 Q_P->matrix_PP[i][j]=aa_P[j*M+i];
//DEBUG                   printf("%f\t",aa_P[j*M+i]);
           }
//DEBUG           printf("\n");
       }

         return(0);
        
#if 111       
       free(aa_P);
       free(tau_P);
       free(work_P);
 #endif

}



int Krn_ComputeSystemRealMatrix(dsp_Matrix_t *mat_P,doubleVector_t *b_P, doubleVector_t *x_P) {


    int i,j;
    dsp_Matrix_t img;
    int fpixel;
    int len;
   	
    integer M ;
    integer N ;
    integer K ;
    
    integer LDA;
    integer LDB;
    integer LDU ;
    integer LDVT;
    integer NRHS=1;
    integer LWORK;
    doublereal RWORK;
    integer INFO;

    int workLength;
    
    doublereal* aa_P;
    doublereal* tau_P;
    doublereal* work_P;
    doublereal* xx_P;
    doublereal* bb_P;
    doublereal* rwork_P;
    integer *IPIV_P;
    
    FILE *fp;
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
   
    M=img.height;
    N=img.width;   
    if(M != N) return(100);

   
      /*
        * allocate space for arrays
        */

       if(img.width > img.height) 
               len=img.height;
           else 
               len=img.width;

       
       aa_P=(doublereal*)calloc(img.height*img.height,sizeof(doublereal));
      // tau_P=(doublecomplex*)calloc(K,sizeof(doublecomplex));
      
      xx_P=(doublereal*)calloc(N,sizeof(doublereal));
      
      bb_P=(doublereal*)calloc(N,sizeof(doublereal));
      
      IPIV_P=(integer*)calloc(N,sizeof(integer));
      
   
	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(doublereal*)calloc(workLength,sizeof(doublereal));


      // rwork_P=(doublereal*)calloc(10*len,sizeof(doublereal));

       if(!aa_P || !work_P || !xx_P || !bb_P) {
            fprintf(stderr,"Real Linear System: Could not allocate space\n"); 
            return(300);
       
       }
       
       
      
    
       LDA = M;
       LDB= M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
//		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
//printf("%f,%f  ", aa_P[j*img.width+i].r,aa_P[j*img.width+i].i);
                 //  aa_P[i*img.height+j]=img.matrix_PP[i][j];
		 aa_P[j*img.height+i]=img.matrix_PP[i][j];
//DEBUG                   printf("%f   ", aa_P[j*img.height+i]);
	      }
//DEBUG printf("\n");
       }

      for(i=0; i< M; i++) {
                   bb_P[i]=b_P->vector_P[i];                   
       }
       


/* Subroutine int dsysv_(char *uplo, integer *n, integer *nrhs, doublereal
        *a, integer *lda, integer *ipiv, doublereal *b, integer *ldb,
        doublereal *work, integer *lwork, integer *info)
*/ 	

      dsysv_("U", &N, &NRHS,aa_P, &LDA, IPIV_P,bb_P, &LDB, work_P, &LWORK, &INFO);




       printf("INFO=%d\n",INFO);
//DEBUG        printf("Linear System Solution: x vector N=%d\n",N);
       for(i=0; i< N; i++) {
                   x_P->vector_P[i]=bb_P[i];
                   
//DEBUG                    printf("%f\n",bb_P[i]);
        }
       
 

         return(0);
        
#if 111       
       free(aa_P);
       free(bb_P);
       free(xx_P);
       free(work_P);
       free(IPIV_P);
       
#endif


}



int Krn_ComputeSystemCxMatrix(dsp_cxMatrix_t *mat_P,cxVector_t *b_P, cxVector_t *x_P){

  	int i,j;
   	dsp_cxMatrix_t img;
   	int fpixel;
        int len;
   	
   	integer M ;
    integer N ;
    integer K ;
    
    integer LDA;
    integer LDB;
    integer LDU ;
    integer LDVT;
    integer NRHS=1;
    integer LWORK;
    doublereal RWORK;
    integer INFO;

    int workLength;
	
    integer *IPIV_P;
    
    doublecomplex* aa_P;
    doublecomplex* tau_P;
    doublecomplex* work_P;
    doublecomplex* xx_P;
    doublecomplex* bb_P;
    doublereal* rwork_P;
    
    char *fileName="cxqrresults.dat";
    FILE *fp;
    
    img.width=mat_P->width;
    img.height=mat_P->height;
    img.matrix_PP=mat_P->matrix_PP;
   
    M=img.height;
    N=img.width;   
      if(M != N) return(100);


   
      /*
        * allocate space for arrays
        */

       if(img.width > img.height) 
               len=img.height;
           else 
               len=img.width;

       
       aa_P=(doublecomplex*)calloc(img.height*img.height,sizeof(doublecomplex));
      // tau_P=(doublecomplex*)calloc(K,sizeof(doublecomplex));
      
      xx_P=(doublecomplex*)calloc(N,sizeof(doublecomplex));
      
      bb_P=(doublecomplex*)calloc(M+N,sizeof(doublecomplex));
      
      IPIV_P=(integer*)calloc(N,sizeof(integer));
     
   
	   if(img.width*img.height*2 < 8000)
		     workLength=8000;
	   else
		    workLength = img.width*img.height*2;

       work_P=(doublecomplex*)calloc(workLength,sizeof(doublecomplex));


      // rwork_P=(doublereal*)calloc(10*len,sizeof(doublereal));

       if(!aa_P || !work_P || !xx_P || !bb_P) {
            fprintf(stderr,"Complex Linear System: Could not allocate space\n"); 
            return(300);
       
       }
       
       
      
    
       LDA = M;
       LDB= M;
       LDU = M;
       LDVT = N;

	   LWORK=workLength;

    
       for ( i= 0; i< img.height; i++ ) {
	      for(j= 0; j< img.width; j++) {
//		     aa_P[j*img.width+i]=img.matrix_PP[i][j];
//printf("%f,%f  ", aa_P[j*img.width+i].r,aa_P[j*img.width+i].i);
                 //  aa_P[i*img.height+j]=img.matrix_PP[i][j];
		 aa_P[j*img.height+i].r=img.matrix_PP[i][j].re;
		  aa_P[j*img.height+i].i=img.matrix_PP[i][j].im;
		  
       //DEBUG             printf("%f,%f  ", aa_P[j*img.height+i].r,aa_P[j*img.height+i].i);
	      }
//DEBUG printf("\n");
       }

      for(i=0; i< N; i++) {
                   bb_P[i].r=b_P->vector_P[i].re;
                   bb_P[i].i=b_P->vector_P[i].im;                     
       }
       
       /*     Subroutine int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
        *  doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
        *  ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
        *   integer *info)
        */


/* Subroutine */ /* int cgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	complex *a, integer *lda, real *s, complex *u, integer *ldu, complex *
	vt, integer *ldvt, complex *work, integer *lwork, real *rwork_P, 
	integer *info) */
/* Subroutine  int zgesvd_(char *jobu, char *jobvt, integer *m, integer *n,
        doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u,
        integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work,
        integer *lwork, doublereal *rwork, integer *info)
*/


/* Subroutine  int zsysv_(char *uplo, integer *n, integer *nrhs,
        doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b,
        integer *ldb, doublecomplex *work, integer *lwork, integer *info)
	
*/
      zsysv_("U",&N, &NRHS,aa_P, &LDA, IPIV_P,bb_P, &LDB, work_P, &LWORK, &INFO);

///* Subroutine */ int zsysv_(char *uplo, integer *n, integer *nrhs, 
//	doublecomplex *a, integer *lda, integer *ipiv, doublecomplex *b, 
//	integer *ldb, doublecomplex *work, integer *lwork, integer *info);


       printf("INFO=%d\n",INFO);
//DEBUG        printf("Linear System Solution: x vector N=%d\n",N);
       for(i=0; i< N; i++) {
                   x_P->vector_P[i].re=bb_P[i].r;
                    x_P->vector_P[i].im=bb_P[i].i;
                   
//DEBUG                    printf("%f\t%f\n",bb_P[i].r,bb_P[i].i);
        }
       
 

         return(0);
        
#if 1111       
       free(aa_P);
       free(bb_P);
       free(xx_P);
       free(work_P);
       free(IPIV_P);
#endif

}



#endif  //DIABLE FOR QT for now


