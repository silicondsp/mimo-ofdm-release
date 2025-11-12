

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


/*  ************************************************************************

        FFT()

  perform both FFT and IFFT by setting FFTswitch 1 and -1 respectively. 
  general input N = 2^n, n is any integer and n>=0 && n<=31.



    ************************************************************************   
*/


// Include section



#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Source: Sasan Ardalan



//  #define FftSize 64

// Function prototypes


//float mycos_32(float x);
//float mysin_32(float x);



static void bri(int * brIndexPtr, int fftSize);

// double mylog2(double x);

static int myIndexSearch(int x);

static void twiddleVectors(float * cosVectorPtr, float * sinVectorPtr, int twiddleSize, int expSign);



// Define section



#define PI 3.141592654



// Main function: FFT/IFFT



void fft2s(
  float realInput[],
  float imagInput[],
  float realOutput[],
  float imagOutput[],
  int fftSize,
  int fftSwitch
)
{

int i,stageNum,butterflyStep,butterflyGap,numOfTwiddle,twiddleIndex,twiddleStep,log2FftSize,expSign;

int butterflyIndex1, butterflyIndex2, butterflyStart;

int * brIndexPtr;

float * cosVectorPtr, * sinVectorPtr;

float wReal,wImag,tReal,tImag, scaleFactor;



brIndexPtr=(int *)malloc(fftSize*sizeof(int));

cosVectorPtr=(float *)malloc(fftSize*sizeof(float));

sinVectorPtr=(float *)malloc(fftSize*sizeof(float));



// Adjust parameters for FFT or IFFT

if (fftSwitch==1) {

   expSign=-1;

   scaleFactor=1;

   }

else {

   expSign=1;

   scaleFactor=0.5;

   }



bri(brIndexPtr, fftSize);     // Compute bit reversed index

twiddleVectors(cosVectorPtr, sinVectorPtr, fftSize/2, expSign);   // Generate twiddle factors

log2FftSize= myIndexSearch(fftSize);  



// Actual bit reversing

for (i=0; i<fftSize; i++) {

   realOutput[i]=realInput[brIndexPtr[i]];

   imagOutput[i]=imagInput[brIndexPtr[i]];

}



butterflyStep=1;     // Difference in index between the first elements of two successive butterflies

twiddleStep=fftSize;

for (stageNum=0; stageNum<log2FftSize; stageNum++) {

   butterflyGap=butterflyStep;      // Difference in index between the two elements of a butterfly

   numOfTwiddle=butterflyGap;       // Number of distinct twiddle factors in each stage.

   butterflyStep=2*butterflyStep;

   twiddleIndex=0;

   twiddleStep=twiddleStep/2;

   for (butterflyStart=0; butterflyStart<numOfTwiddle; butterflyStart++) {

      wReal=cosVectorPtr[twiddleIndex];

      wImag=sinVectorPtr[twiddleIndex];

      twiddleIndex+=twiddleStep;

      for (butterflyIndex1=butterflyStart; butterflyIndex1<fftSize; butterflyIndex1+=butterflyStep) {

         butterflyIndex2=butterflyIndex1+butterflyGap;



         tReal=wReal*realOutput[butterflyIndex2]-wImag*imagOutput[butterflyIndex2];    // Twiddle multiplication

         tImag=wReal*imagOutput[butterflyIndex2]+wImag*realOutput[butterflyIndex2];



         realOutput[butterflyIndex2]=scaleFactor*(realOutput[butterflyIndex1]-tReal);  // Butterfly operation

	      imagOutput[butterflyIndex2]=scaleFactor*(imagOutput[butterflyIndex1]-tImag);

	      realOutput[butterflyIndex1]=scaleFactor*(realOutput[butterflyIndex1]+tReal);

	      imagOutput[butterflyIndex1]=scaleFactor*(imagOutput[butterflyIndex1]+tImag);

      }

   }

}





free(brIndexPtr);

free(cosVectorPtr);

free(sinVectorPtr);



return;

}







static void bri(int * brIndexPtr, int fftSize) {



int i,j,log2FftSize,divider,divided,accumulate,exponent;



log2FftSize= myIndexSearch(fftSize);  

brIndexPtr[0]=0;



for (i=1; i<fftSize; i++) {

   accumulate=0;

   exponent=1;

   divider=fftSize/2;

   divided=i;

   for(j=0; j<log2FftSize; j++) {

      if (divided>=divider) {

         divided-=divider;

         accumulate+=exponent;

      }

      divider=divider/2;

      exponent=exponent*2;

   }

   brIndexPtr[i]=accumulate;

}



return;

}







static void twiddleVectors(float * cosVectorPtr, float * sinVectorPtr, int twiddleSize, int expSign) {

int i;



for (i=0; i<twiddleSize; i++) {

   cosVectorPtr[i]=cos((float)(expSign*PI*i/twiddleSize));

   sinVectorPtr[i]=sin((float)(expSign*PI*i/twiddleSize));

}



return;

}







static int myIndexSearch(int x) {

   int i;
   int temp =1;

   i = 0; 
   while (temp != x) {
	   
	   temp = temp << 1;
	   i +=1;
   }


   return i;

}

   



   
