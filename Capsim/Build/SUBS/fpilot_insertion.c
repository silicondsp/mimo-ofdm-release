

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




/*     ************************************************************************

                   FPilot_insertion()
 

     802.11a pilot isertion, total number of input symbols is 48(complex).
	 The output pattern should be like index: 0,1, 2,....,26, 0,0....0,-26,
	 -25, -24,.....-1. This file doesn't include polarity of pilot subcarriers.

     
programmer:                        Bin Huang
date:                              7/30/01 

      *************************************************************************
*/


#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include "ftab_80211a.h"



void swapFunction(
  Fword xr[],           /* (i/o)  : vector swap  */
  Fword xi[],
  Word16 m                   /* (i)    : length of vecotr  */
);

void polarityFunction(
  Fword xReal[],           /* (i/o)  : vector swap  */ 
  Word16 index               /* (i):     index for polarity control vector[0~126] */
);



void Pilot_insertion(
  Fword xReal[],       /* (i)    : real part    */
  Fword xImag[],       /* (i)    : imaginary part    */
  Word16 pilotCount,   /* (i)    : index polarity control vector for pilot subcarriers */
  Fword yiReal[],       /* (o)    : real part    */
  Fword yiImag[]        /* (o)    : imaginary part    */
 
)

{

   Word16  j,i; 
   Word16  N=64,index;
   Fword  yReal[64],yImag[64];



   for (j=0; j<48; j++)
   {
      index = pilotMapping[j];
	  yReal[index] = xReal[j];
	  yImag[index] = xImag[j];
   }
   
      yReal[5] = 1.0;              /* insert pilot   */
      yImag[5] = 0.0;
      yReal[19] = 1.0;
      yImag[19] = 0.0;
      yReal[32] = 1.0;
      yImag[32] = 0.0;
      yReal[46] = -1.0;
      yImag[46] = 0.0;

   /* adding zeros  */

     for (i=0; i<6; i++)
       {
         yiReal[i] = 0.0;
         yiImag[i] = 0.0;
       }

     for (i=0; i<26; i++)
      {
         yiReal[i+6] = yReal[i];
         yiImag[i+6] = yImag[i];
       }

       yiReal[32] = 0.0;
       yiImag[32] = 0.0;

     for(i=26; i<52; i++)
       {
         yiReal[i+7] = yReal[i];
         yiImag[i+7] = yImag[i];
       }

     for(i=0;i<5;i++)
       {
         yiReal[i+59] = 0.0;
         yiImag[i+59] = 0.0;
       }


    /* need to swap first -26 to -1 with last 1 to 26  in order to come up with
           input to IFFT   */


      swapFunction(yiReal,yiImag,32);



    /*  add polarity control for pilot subcarriers   */

      polarityFunction(yiReal, pilotCount);    
   
}



void swapFunction(
  Fword xr[],           /* (i/o)  : vector swap  */
  Fword xi[],
  Word16 m                   /* (i)    : length of vecotr  */
)

{
   Word16 i;
   Fword  pReal, pImag;

 for (i=0; i<m; i++)
  {

       pReal=xr[i];
       pImag=xi[i];
       xr[i]=xr[32+i];
       xi[i]=xi[32+i];
       xr[32+i]=pReal;
       xi[32+i]=pImag;  
 }
 
   
}


void polarityFunction(
  Fword xReal[],           /* (i/o)  : vector swap  */ 
  Word16 index               /* (i):     index for polarity control vector[0~126] */
)
{
	Fword  temp,k1=-1.0;

	temp = Polarity_control[index];
    xReal[7] = temp;
	xReal[21] = k1 * temp;
	xReal[43] = temp;
	xReal[57] = temp;

	

}

	
    
