
/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library
    Copyright (C) 2007-2017   Sasan Ardalan
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
// GitHub Repository https://github.com/silicondsp/mimo-ofdm-release
// https://github.com/silicondsp/mimo-ofdm-release/blob/main/Article/MIMO-OFDM_SVD_Computation_CORDIC_Operations.pdf
//

#include <stdio.h>
#include <math.h>
#include <tcl.h>

#include <vectors.h>


#include "CordicArctan.h"
#include "CordicRotate.h"

#define PI 3.1415926535898


extern void PrintCxMatrix(dsp_cxMatrix_t *mat_P);

int Krn_Compute2x2SVDCxMatrixFP(dsp_cxMatrix_t *mat_P, doubleVector_t *ss_P,dsp_cxMatrix_t *u_P, dsp_cxMatrix_t *v_P){

  	      int len;

   	int M ;
    int N ;


    int INFO;

	int workLength;
    //++++++++++++++++++++++++++++
    int	pwidth;
	int	pheight;
      float  scale2;

	int i,j,k,ii;
	unsigned short pixel;
	float	fpixel;

        float x,y;

        float norm;



    float tr;
    float ti;

      float xv;
      float yv;
      float angv;
      float rv;

     float phi;
     float psi;
     float alpha;
     float beta;
     float eta;
     float omega;

     float cos_alpha;
     float sin_alpha;
     float cos_beta;
     float sin_beta;

     float cos_eta;
     float sin_eta;
     float cos_omega;
     float sin_omega;


     float theta;

     float cos_theta;
     float sin_theta;


     float cos_phi;
     float sin_phi;

     float cos_psi;
     float sin_psi;

     float phi_plus_psi;
     float phi_minus_psi;

     float a11,a12,a21,a22;
     float c11,c12,c21,c22;

     float ar11,ar12,ar21,ar22;
     float ai11,ai12,ai21,ai22;

     float cr11,cr12,cr21,cr22;
     float ci11,ci12,ci21,ci22;



     float u1r11,u1r12,u1r21,u1r22;
     float u1i11,u1i12,u1i21,u1i22;

     float u2r11,u2r12,u2r21,u2r22;
     float u2i11,u2i12,u2i21,u2i22;

     float v1r11,v1r12,v1r21,v1r22;
     float v1i11,v1i12,v1i21,v1i22;

     float v2r11,v2r12,v2r21,v2r22;
     float v2i11,v2i12,v2i21,v2i22;



     float ur11,ur12,ur21,ur22;
     float ui11,ui12,ui21,ui22;


     float vr11,vr12,vr21,vr22;
     float vi11,vi12,vi21,vi22;



     int sgn=0;

     double th;

     int numberRowsRead;

     float scale;

    //++++++++++++++++++++++++++++



        pwidth=2;
        pheight=2;


    //    scale=1024;

    scale=1.0;

        scale2=scale;
  #ifdef TEST
       mat_P->matrix_PP[0][0].re=9;
        mat_P->matrix_PP[0][0].im=5;
        mat_P->matrix_PP[0][1].re=3;
        mat_P->matrix_PP[0][1].im=11;
        mat_P->matrix_PP[1][1].re=3;
        mat_P->matrix_PP[1][1].im=7;
        mat_P->matrix_PP[1][0].re=6;
        mat_P->matrix_PP[1][0].im=-7;
#endif


        ar11=mat_P->matrix_PP[0][0].re*scale;
        ai11=mat_P->matrix_PP[0][0].im*scale;
        ar12=mat_P->matrix_PP[0][1].re*scale;
        ai12=mat_P->matrix_PP[0][1].im*scale;
        ar22=mat_P->matrix_PP[1][1].re*scale;
        ai22=mat_P->matrix_PP[1][1].im*scale;
        ar21=mat_P->matrix_PP[1][0].re*scale;
        ai21=mat_P->matrix_PP[1][0].im*scale;


        /*
         * convert complex matrix elements into polar coordinates
         */
	 printf("Polar\n");
        for(i=0; i< pheight; i++) {

             for(j=0; j< pwidth; j++) {


                  xv=(float )mat_P->matrix_PP[i][j].re*scale;
                  yv=(float )mat_P->matrix_PP[i][j].im*scale;

                  // angv=CordicArctan(xv,yv,&rv);
                  angv=atan2(yv,xv);
                  rv=sqrt(xv*xv+yv*yv);

                  mat_P->matrix_PP[i][j].re=rv;
                  mat_P->matrix_PP[i][j].im=angv;


                  printf("%f,%f  ",mat_P->matrix_PP[i][j].re/(scale*4.0),mat_P->matrix_PP[i][j].im);





             }
             printf("\n");

        }
         /*
          * compute U1 and V1 elements
          * for U1 phi=0.
          * so we need alpha and beta
          */
         /*
          * psi=arctan(rml/rmm) r21/r22
          */
        phi=0;

//FXP        xv=((float)mat_PP[1][1].re)/16;
//FXP        yv=((float)mat_PP[1][0].re)/16;

        xv=((float)mat_P->matrix_PP[1][1].re)/16.0;
        yv=((float)mat_P->matrix_PP[1][0].re)/16.0;

//FXP        psi= CordicArctan(xv,yv,&rv);
        psi= atan2(yv,xv);
        rv=sqrt(xv*xv+yv*yv);

        alpha= -(mat_P->matrix_PP[1][1].im+mat_P->matrix_PP[1][0].im)/2;
        beta=alpha;
        eta= (mat_P->matrix_PP[1][1].im-mat_P->matrix_PP[1][0].im)/2;
        omega= -eta;

        printf("alpha=%f, beta=%f, eta=%f, omega=%f, phi=%f, psi=%f \n",
                 (float)alpha,(float)beta,eta,(float)omega,(float)phi, (float)psi);

        /*
         * compute Exp(j*alpha)
         */
       xv=scale;
       yv=0;
       //FXP CordicRotate(&xv,&yv, alpha);
       xv=scale*cos(alpha);
       yv=scale*sin(alpha);

       cos_alpha=xv;
       sin_alpha=yv;

       cos_beta=xv;
       sin_beta=yv;

       xv=scale;
       yv=0;
       //FXP CordicRotate(&xv,&yv, eta);
       xv=scale*cos(eta);
       yv=scale*sin(eta);
       cos_eta=xv;
       sin_eta=yv;

       cos_omega=xv;
       sin_omega= - yv;

       xv=scale;
       yv=0;
//FXP       CordicRotate(&xv,&yv, psi);
       xv=scale*cos(psi);
       yv=scale*sin(psi);

       cos_psi=xv;
       sin_psi=yv;



       /*
        * compute U1
        */
       u1r11= cos_alpha;
       u1i11= sin_alpha;

       u1r22= cos_beta;
       u1i22= sin_beta;

       u1r21=0;
       u1i21=0;
       u1r12=0;
       u1i12=0;


       /*
        * compute V1
        */
       v1r11= cos_eta*cos_psi/scale2;
       v1i11= sin_eta*cos_psi/scale2;

       v1r12= sin_psi*cos_eta/scale2;
       v1i12= sin_psi*sin_eta/scale2;

       v1r21= -sin_psi*cos_omega/scale2;
       v1i21= -sin_psi*sin_omega/scale2;
       v1r22= cos_psi*cos_omega/scale2;
       v1i22= cos_psi*sin_omega/scale2;

       printf("U1 Matrix\n");
       PrintMatrixComplexFP(u1r11,u1i11,u1r12,u1i12,u1r21,u1i21,u1r22,u1i22);
       printf("\n\n");

       printf("V1 Matrix\n");
       PrintMatrixComplexFP(v1r11,v1i11,v1r12,v1i12,v1r21,v1i21,v1r22,v1i22);
       printf("\n\n");


       MultiplyMatrixComplexFP(scale2,u1r11,u1i11,u1r12,u1i12,u1r21,u1i21,u1r22,u1i22,
                    ar11,ai11,ar12,ai12,ar21,ai21,ar22,ai22,
                    &cr11,&ci11,&cr12,&ci12,&cr21,&ci21,&cr22,&ci22);

       MultiplyMatrixComplexFP(scale2,cr11,ci11,cr12,ci12,cr21,ci21,cr22,ci22,
                                 v1r11,v1i11,v1r12,v1i12,v1r21,v1i21,v1r22,v1i22,
                                        &ar11,&ai11,&ar12,&ai12,&ar21,&ai21,&ar22,&ai22);



       printf("U1.A.V1 Matrix\n");
       PrintMatrixComplexFP(ar11,ai11,ar12,ai12,ar21,ai21,ar22,ai22);
       printf("\n\n");

       /*
        * Matrix should be upper triangular
        * Therefore, set ar21=0 ai21=0
        * also ai22=0
        */
      ar21=0;
      ai21=0;
      ai22=0;



    //+++++++++++++++     U2 and V2 ++++++++++++++++++++++++++++++++++++++++++++++++++
       /*
        * convert A into polar coordinates
        */

        /*
         * convert complex matrix elements into polar coordinates
         */
        mat_P->matrix_PP[0][0].re=(float)ar11;
        mat_P->matrix_PP[0][0].im=(float)ai11;
        mat_P->matrix_PP[0][1].re=(float)ar12;
        mat_P->matrix_PP[0][1].im=(float)ai12;
        mat_P->matrix_PP[1][0].re=(float)ar21;
        mat_P->matrix_PP[1][0].im=(float)ai21;
        mat_P->matrix_PP[1][1].re=(float)ar22;
        mat_P->matrix_PP[1][1].im=(float)ai22;
        for(i=0; i< pheight; i++) {

             for(j=0; j< pwidth; j++) {


                  xv=(float )mat_P->matrix_PP[i][j].re;
                  yv=(float )mat_P->matrix_PP[i][j].im;

//FXP                  angv=CordicArctan(xv,yv,&rv);
                  angv=atan2(yv,xv);
                  rv=sqrt(xv*xv+yv*yv);

                  mat_P->matrix_PP[i][j].re=rv;
                  mat_P->matrix_PP[i][j].im=angv;


                  printf("%f,%f  ",mat_P->matrix_PP[i][j].re/(scale*4.0),mat_P->matrix_PP[i][j].im/(float)PI_1*PI);





             }
             printf("\n");

        }



        /*
         * compute U2 and V2 elements
         */

        alpha = -((float)mat_P->matrix_PP[0][0].im+(float)mat_P->matrix_PP[0][1].im)/2;
        eta   =  ((float)mat_P->matrix_PP[0][1].im-(float)mat_P->matrix_PP[0][0].im)/2;
        omega = -eta;
        beta = eta;

        xv=((float)(mat_P->matrix_PP[1][1].re+mat_P->matrix_PP[0][0].re))/16.0;
        yv=((float)mat_P->matrix_PP[0][1].re)/16.0;
        //FXP phi_plus_psi= -CordicArctan(xv,yv,&rv);
        phi_plus_psi =- atan2(yv,xv);
        rv=sqrt(xv*xv+yv*yv);

        xv=((float)(mat_P->matrix_PP[1][1].re-mat_P->matrix_PP[0][0].re))/16.0;
        yv=((float)mat_P->matrix_PP[0][1].re)/16.0;
        //FXP phi_minus_psi= CordicArctan(xv,yv,&rv);
        phi_minus_psi = atan2(yv,xv);
        rv=sqrt(xv*xv+yv*yv);

        printf("phi_plus_psi=%f  phi_minus_psi=%f \n",(float)phi_plus_psi,(float)phi_minus_psi);

        phi= (phi_plus_psi+ phi_minus_psi)/2;
        psi= (phi_plus_psi- phi_minus_psi)/2;


        printf("alpha=%f, beta=%f, eta=%f, omega=%f, phi=%f, psi=%f \n",
                 (float)alpha,(float)beta,eta,(float)omega,(float)phi, (float)psi);

        /*
         * compute Exp(j*alpha)
         */
       xv=scale;
       yv=0;
       //FXP CordicRotate(&xv,&yv, alpha);
       xv=scale*cos(alpha);
       yv=scale*sin(alpha);
       cos_alpha=xv;
       sin_alpha=yv;


       xv=scale;
       yv=0;
       //FXP CordicRotate(&xv,&yv, eta);
       xv=scale*cos(eta);
       yv=scale*sin(eta);
       cos_eta=xv;
       sin_eta=yv;

       cos_beta=xv;
       sin_beta=yv;



       cos_omega=xv;
       sin_omega= - yv;

       xv=scale;
       yv=0;
       //FXP CordicRotate(&xv,&yv, psi);
       xv=scale*cos(psi);
       yv=scale*sin(psi);
       cos_psi=xv;
       sin_psi=yv;

       xv=scale;
       yv=0;
       //FXP CordicRotate(&xv,&yv, phi);
       xv=scale*cos(phi);
       yv=scale*sin(phi);
       cos_phi=xv;
       sin_phi=yv;



       /*
        * compute U2
        */
       u2r11= cos_phi*cos_alpha/scale2;
       u2i11= cos_phi*sin_alpha/scale2;

       u2r12=sin_phi*cos_beta/scale2;
       u2i12=sin_phi*sin_beta/scale2;

       u2r21= -sin_phi*cos_alpha/scale2;
       u2i21= -sin_phi*sin_alpha/scale2;

       u2r22= cos_phi*cos_beta/scale2;
       u2i22= cos_phi*sin_beta/scale2;

       /*
        * compute V2
        */
       v2r11= cos_eta*cos_psi/scale2;
       v2i11= sin_eta*cos_psi/scale2;

       v2r12= sin_psi*cos_eta/scale2;
       v2i12= sin_psi*sin_eta/scale2;

       v2r21= -sin_psi*cos_omega/scale2;
       v2i21= -sin_psi*sin_omega/scale2;
       v2r22= cos_psi*cos_omega/scale2;
       v2i22= cos_psi*sin_omega/scale2;

       printf("U2 Matrix\n");
       PrintMatrixComplexFP(u2r11,u2i11,u2r12,u2i12,u2r21,u2i21,u2r22,u2i22);
       printf("\n\n");

       printf("V2 Matrix\n");
       PrintMatrixComplexFP(v2r11,v2i11,v2r12,v2i12,v2r21,v2i21,v2r22,v2i22);
       printf("\n\n");


       MultiplyMatrixComplexFP(scale2,u2r11,u2i11,u2r12,u2i12,u2r21,u2i21,u2r22,u2i22,
                    ar11,ai11,ar12,ai12,ar21,ai21,ar22,ai22,
                    &cr11,&ci11,&cr12,&ci12,&cr21,&ci21,&cr22,&ci22);

       MultiplyMatrixComplexFP(scale2,cr11,ci11,cr12,ci12,cr21,ci21,cr22,ci22,
                                 v2r11,v2i11,v2r12,v2i12,v2r21,v2i21,v2r22,v2i22,
                                        &ar11,&ai11,&ar12,&ai12,&ar21,&ai21,&ar22,&ai22);



       printf("U2.A.V2 Matrix\n");
       PrintMatrixComplexFP(ar11,ai11,ar12,ai12,ar21,ai21,ar22,ai22);
       printf("\n\n");



   //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

       /*
        * At this point the A matrix is real so we setup new real matrix A
        */

       a11=ar11;
       a12=ar12;
       a21=ar21;
       a22=ar22;


        xv=(a11-a22)/16.0;
        if(xv <0) { xv= -xv; sgn=-1;}
        yv=(2*a12)/16.0;
        //FXP theta= CordicArctan(xv,yv,&rv)/2;
        theta=atan2(yv,xv)/2.0;
        rv=sqrt(xv*xv+yv*yv);

        if(sgn <0) theta= -theta;

        xv=scale;
        yv=0;
        //FXP CordicRotate(&xv,&yv, theta);
        xv=scale*cos(theta);
        yv=scale*sin(theta);

        cos_theta=xv;
        sin_theta=yv;

        printf("Theta=%f cos_theta=%f  sin_theta=%f\n",(float)theta,xv,yv);

        th=0.5*atan(2*(float)a12/(float)(a11-a22));

        printf("Theta Float =%f cos_theta=%f  sin_theta=%f \n",th,cos(th),sin(th));

        th=0.5*atan2((float)(a11-a22),2*(float)a12);

        printf("Theta atan2 Float =%f cos_theta=%f  sin_theta=%f \n",th,cos(th),sin(th));


        MultiplyMatrixFP(scale2,cos_theta,sin_theta,-sin_theta,cos_theta,
                              a11,a12,a21, a22,
                              &c11,&c12,&c21,&c22);

        MultiplyMatrixFP(scale2, c11,c12,c21,c22,
                               cos_theta,-sin_theta,sin_theta,cos_theta,
                               &a11,&a12,&a21, &a22 );

        printf("Rr.A.Rl\n");
        printf ("%f\t%f\n%f\t%f\n",a11,a12,a21,a22);




//U=Rr.U2.U1
      MultiplyMatrixComplexFP(scale2,cos_theta,0,sin_theta,0,-sin_theta,0,cos_theta,0,
                    u2r11,u2i11,u2r12,u2i12,u2r21,u2i21,u2r22,u2i22,
                    &cr11,&ci11,&cr12,&ci12,&cr21,&ci21,&cr22,&ci22);

       MultiplyMatrixComplexFP(scale2,cr11,ci11,cr12,ci12,cr21,ci21,cr22,ci22,
                                 u1r11,u1i11,u1r12,u1i12,u1r21,u1i21,u1r22,u1i22,
                                        &ur11,&ui11,&ur12,&ui12,&ur21,&ui21,&ur22,&ui22);


//V=V1.V2.Rl
#if 1
      MultiplyMatrixComplexFP(scale2,v1r11,v1i11,v1r12,v1i12,v1r21,v1i21,v1r22,v1i22,
                    v2r11,v2i11,v2r12,v2i12,v2r21,v2i21,v2r22,v2i22,
                    &cr11,&ci11,&cr12,&ci12,&cr21,&ci21,&cr22,&ci22);

       MultiplyMatrixComplexFP(scale2,cr11,ci11,cr12,ci12,cr21,ci21,cr22,ci22,
                                 cos_theta,0,-sin_theta,0,sin_theta,0,cos_theta,0,
                                        &vr11,&vi11,&vr12,&vi12,&vr21,&vi21,&vr22,&vi22);
#endif



       printf("U Matrix\n");
       PrintMatrixComplexFP(ur11,ui11,ur12,ui12,ur21,ui21,ur22,ui22);
       printf("\n\n");

       printf("V Matrix\n");
       PrintMatrixComplexFP(vr11,vi11,vr12,vi12,vr21,vi21,vr22,vi22);
       printf("\n\n");

#if 000
      tr=vr12;
      ti=vi12;

      vr12=vr21;
      vi12=-vi21;

      vr21=tr;
      vi21=-ti;

      vi11=-vi11;
      vi22=-vi22;
#endif

      MultiplyMatrixComplexFP(scale2,ur11,ui11,ur12,ui12,ur21,ui21,ur22,ui22,
                    a11,0,0,0,0,0,a22,0,
                    &cr11,&ci11,&cr12,&ci12,&cr21,&ci21,&cr22,&ci22);

       MultiplyMatrixComplexFP(scale2,cr11,ci11,cr12,ci12,cr21,ci21,cr22,ci22,
                                 vr11,vi11,vr12,vi12,vr21,vi21,vr22,vi22,
                                        &cr11,&ci11,&cr12,&ci12,&cr21,&ci21,&cr22,&ci22);



     printf("U S VH Matrix\n");
       PrintMatrixComplexFP(cr11,ci11,cr12,ci12,cr21,ci21,cr22,ci22);
       printf("\n\n");







      //  if(a11 >= a22) {
if(1) {
        u_P->matrix_PP[0][0].re=(float)ur11;
        u_P->matrix_PP[0][0].im=(float)ui11;
        u_P->matrix_PP[0][1].re=(float)ur12;
        u_P->matrix_PP[0][1].im=(float)ui12;
        u_P->matrix_PP[1][1].re=(float)ur22;
        u_P->matrix_PP[1][1].im=(float)ui22;
        u_P->matrix_PP[1][0].re=(float)ur21;
        u_P->matrix_PP[1][0].im=(float)ui21;


        v_P->matrix_PP[0][0].re=(float)vr11;
        v_P->matrix_PP[0][0].im=(float)vi11;
        v_P->matrix_PP[0][1].re=(float)vr12;
        v_P->matrix_PP[0][1].im=(float)vi12;
        v_P->matrix_PP[1][1].re=(float)vr22;
        v_P->matrix_PP[1][1].im=(float)vi22;
        v_P->matrix_PP[1][0].re=(float)vr21;
        v_P->matrix_PP[1][0].im=(float)vi21;

        ss_P->vector_P[0]=(float)a11/scale;
        ss_P->vector_P[1]=(float)a22/scale;

        } else {

        u_P->matrix_PP[0][0].re=(float)ur12;
        u_P->matrix_PP[0][0].im=(float)ui12;
        u_P->matrix_PP[0][1].re=(float)ur11;
        u_P->matrix_PP[0][1].im=(float)ui11;
        u_P->matrix_PP[1][1].re=(float)ur21;
        u_P->matrix_PP[1][1].im=(float)ui21;
        u_P->matrix_PP[1][0].re=(float)ur22;
        u_P->matrix_PP[1][0].im=(float)ui22;


        v_P->matrix_PP[0][0].re=(float)vr12;
        v_P->matrix_PP[0][0].im=(float)vi12;
        v_P->matrix_PP[0][1].re=(float)vr11;
        v_P->matrix_PP[0][1].im=(float)vi11;
        v_P->matrix_PP[1][1].re=(float)vr21;
        v_P->matrix_PP[1][1].im=(float)vi21;
        v_P->matrix_PP[1][0].re=(float)vr22;
        v_P->matrix_PP[1][0].im=(float)vi22;

        ss_P->vector_P[0]=(float)a22/scale;
        ss_P->vector_P[1]=(float)a11/scale;





        }

        norm=1/(scale);
        for(i=0; i<2; i++)
           for(j=0; j<2; j++) {
                   v_P->matrix_PP[i][j].re=v_P->matrix_PP[i][j].re*norm;
                   v_P->matrix_PP[i][j].im=v_P->matrix_PP[i][j].im*norm;


                   u_P->matrix_PP[i][j].re=u_P->matrix_PP[i][j].re*norm;
                   u_P->matrix_PP[i][j].im=u_P->matrix_PP[i][j].im*norm;


        }



        printf("SVD FXP  %f    %f\n\n", ss_P->vector_P[0], ss_P->vector_P[1]);

        printf("SVD FXP U\n");
        PrintCxMatrix(u_P);

        printf("SVD FXP V\n");
        PrintCxMatrix(v_P);


  //      Krn_TransposeConjugateMatrix(v_P) ;
//+++++++++++++++++++++++++++++++++++++++++++









       /*
        * store results
        */


return(INFO);

}



