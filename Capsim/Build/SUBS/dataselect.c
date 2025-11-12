
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

/*  *********************************************************
     
	dataselect()

    perform data selection: data reorder, remove the zeros.

    programmer:       Bin Huang
    data:             8/6/02


 *************************************************************
*/

void DataSelect(float * x_re,         /* real part of input data[64] */
                float * x_im,         /* imag part of input data[64] */
                float * yy_re,        /* real part of rearranged data[48] */
                float * yy_im,        /* imag part of rearranged data[48] */
                float * pilo_re,    /* real part of pilots[4] */
                float * pilo_im)    /* imag part of pilots[4] -supposed to be 0 */
{
    float * temp_re;
    float * temp_im;
    int N1 = 64;
    int count;
    int k;

                      temp_re = x_re + N1/2 + 6;
                      temp_im = x_im + N1/2 + 6;
                      count = 0;
                      for(k=0; k<5; k++)
                      {
                           yy_re[count] = *temp_re++;
                           yy_im[count] = *temp_im++;
                           count++;
                      }
                      pilo_re[0] = *temp_re++;
                      pilo_im[0] = *temp_im++;

                      for(k=0; k<13; k++)
                      {
                           yy_re[count] = *temp_re++;
                           yy_im[count] = *temp_im++;
                           count++;
                      }
                      pilo_re[1] = *temp_re++;
                      pilo_im[1] = *temp_im++;

                      for(k=0; k<6; k++)
                      {
                           yy_re[count] = *temp_re++;
                           yy_im[count] = *temp_im++;
                           count++;
                      }

                      temp_re = temp_re - (N1-1);
                      temp_im = temp_im - (N1-1);

                      for(k=0; k<6; k++)
                      {
                           yy_re[count] = *temp_re++;
                           yy_im[count] = *temp_im++;
                           count++;
                      }
                      pilo_re[2] = *temp_re++;
                      pilo_im[2] = *temp_im++;

                      for(k=0; k<13; k++)
                      {
                           yy_re[count] = *temp_re++;
                           yy_im[count] = *temp_im++;
                           count++;
                      }
                      pilo_re[3] = *temp_re++;
                      pilo_im[3] = *temp_im++;

                      for(k=0; k<5; k++)
                      {
                           yy_re[count] = *temp_re++;
                           yy_im[count] = *temp_im++;
                           count++;
                      }
     return;
}
