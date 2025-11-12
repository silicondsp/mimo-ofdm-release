<BLOCK>
<LICENSE>


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

</LICENSE>

<BLOCK_NAME>cxchmodel</BLOCK_NAME> 

<COMMENTS>
<![CDATA[ 

/* cxchmodel.s */
/***********************************************************************
                             cxchmodel()
************************************************************************
This block models a fading channel.
Given the sampling rate in MHz and the delay spread in ns the complex impulse response 
is computed and convolved with the complex input stream.

Reference:
Evaluating the Performance of  HRb Proposals in the Presence of Multipath
Steve Halford,  
Karen Halford, and Mark Webster  **
Intersil Corporation
September, 2000
Submission to IEEE doc.: IEEE 802.11-00/282r2

Matlab coded converted to C


<NAME>
cxchmodel
</NAME>
<DESC_SHORT>
This block convolves  the input samples with the computed complex channel impulse response.
</DESC_SHORT>
<DESCRIPTION>
</DESCRIPTION>
<PROGRAMMERS>
Date:  August 28, 2006 
Programmer: Sasan Ardalan
</PROGRAMMERS>
*/

]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 

#include <math.h>
#include <stdio.h>

]]>
</INCLUDES> 

<DEFINES> 


#define RAND_LARGE 0x7fffffff
#define DEC

#define MAX_TAPS 1024

</DEFINES> 

     

<STATES>
	<STATE>
		<TYPE>complex*</TYPE>
		<NAME>x_P</NAME>
	</STATE>
	<STATE>
		<TYPE>complex*</TYPE>
		<NAME>h_P</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>Ndiv2</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>NTaps</NAME>
	</STATE>	
</STATES>
 
<DECLARATIONS> 

 	complex tmp1,tmp2;
        complex  sum;
        complex tmp;
	FILE *fp;
	char fileName[256];

        float taps_r[MAX_TAPS];
        float taps_i[MAX_TAPS];
        float vark[MAX_TAPS];

       
        float sampTimeNsec;
        float var0;
        int Kmax;
        int i,j,k;
        double s,t,u,v,w,x;
        float y1,y2;
        int trouble;
        long 	seed=775499;
        float std=1.0;
	
	
	
</DECLARATIONS> 

       

<PARAMETERS>
<PARAM>
	<DEF>Sampling Rate (MHz)</DEF>
	<TYPE>float</TYPE>
	<NAME>sampRateMHz</NAME>
	<VALUE>200</VALUE>
</PARAM>
<PARAM>
	<DEF>Delay Spread (ns)</DEF>
	<TYPE>float</TYPE>
	<NAME>delaySprdNsec</NAME>
	<VALUE>50</VALUE>
</PARAM>
<PARAM>
	<DEF>Seed</DEF>
	<TYPE>int</TYPE>
	<NAME>seedParam</NAME>
	<VALUE>725443</VALUE>
</PARAM>
</PARAMETERS>

    

<INPUT_BUFFERS>
	<BUFFER>
		<TYPE>complex</TYPE>
		<NAME>x</NAME>
	</BUFFER>
</INPUT_BUFFERS>
 
    

<OUTPUT_BUFFERS>
	<BUFFER>
		<TYPE>complex</TYPE>
		<NAME>y</NAME>
	</BUFFER>
</OUTPUT_BUFFERS>
 
<INIT_CODE>
<![CDATA[ 

//+++++++++++
// function [taps] = ExpChanTaps(sampRateMHz, delaySprdNsec)
sprintf(fileName,"%s.taps",STAR_NAME);
fp=fopen(fileName,"w");
if(!fp) {printf("%s could not open file.\n",STAR_NAME); return(100);}

sampTimeNsec = 1000.00 / sampRateMHz;
printf("fs(MHz)=%f delay spread (ns) =%f \n",sampRateMHz,delaySprdNsec);
if (delaySprdNsec == 0) {
   Kmax = 0;
   vark[0] = 1;
} else {
   Kmax = ceil( 10 * delaySprdNsec/sampTimeNsec );
   printf("Kmax=%d\n",Kmax);
  // fprintf(fp,"%d\n",Kmax);
   if(Kmax > MAX_TAPS) {
        fprintf(stderr,"cxchmodel too many Taps Kmax=%d \n",Kmax);
	return(101);
   }
   var0 = (1 - exp( -1*(sampTimeNsec)/delaySprdNsec ))/(1 - exp( -1*((Kmax+1)* sampTimeNsec)/delaySprdNsec ));

   for(k=0; k<Kmax; k++) {
        vark[k] = var0 * exp( - k*sampTimeNsec/delaySprdNsec );       
   }
 }
for(k=0; k<Kmax; k++) {
        vark[k] = sqrt(vark[k]/2);       
}
seed=seedParam;
#ifdef DEC
srandom(seed);
#else
srand48((long int)seed);
#endif
/*
 * calculate the taps
 */
for(k=0; k<Kmax; k++) {


/****************************************************************/
/* 		gauss						*/
/* code written by Prayson Pate					*/
/* This code generates two random variables that are normally 	*/
/* distributed with mean 0 and variance 1 i.e N(0,1).	 	*/
/* The polar method is used to generate normally distributed    */
/* samples from a sequence that is uniform on (-1,1).  The      */
/* resulting distribution is described exactly by N(0,1).       */
/* This method is based	on the inverse distribution function.   */
/****************************************************************/
trouble = 0;
do {
	if(++trouble > 100) {
		fprintf(stderr,"gauss: problem with random number\
			 generator\n");
		return(2);
	}
	/* 
 	 * get two random numbers in the interval (-1,1) 
	 */
#ifdef DEC
	s = (double)random()/RAND_LARGE;
#else
	s = drand48();
#endif
	u = -1.0 + 2.0*s;
#ifdef DEC
	t = (double)random()/RAND_LARGE;
#else
	t = drand48();
#endif
	v = -1.0 + 2.0*t;
	w = u*u + v*v;
	/* 
	 * is point (u,v) in the unit circle? 
	 */
} while (w >= 1.0 || w == 0.0);

x = sqrt((-2.0 * log(w))/w);
/* 
 * find two independent values of y	
 */
y1 = std * u * x;
y2 = std * v * x;

taps_r[k]=vark[k]*y1;
taps_i[k]=vark[k]*y2;

//printf("%d\t%f\t%f\n",k,taps_r[k],taps_i[k]);
//// printf("%d\t%f\t%f\n",k,y1,y2);

fprintf(fp,"%f\t%f\n",taps_r[k],taps_i[k]);

} // end for loop for k

fclose(fp);

//+++++++++++

NTaps=Kmax;

        Ndiv2=NTaps/2;
	/*
	 * Allocate memory and return pointers for tapped delay line x_P and
	 * array containing impulse response samples, h_P.
	 *
	 */
	if( (x_P = (complex*)calloc(NTaps,sizeof(complex))) == NULL ||
	    (h_P = (complex*)calloc(NTaps,sizeof(complex))) == NULL ) {
	   	fprintf(stderr,"cxchmodel: can't allocate work space\n");
		return(103);
	}
	/*
	 * Read in the impulse response samples into the array
	 * and initialize the tapped delay line to zero.
	 *
	 */
	for (i=0; i<NTaps; i++) {
		x_P[i].re= 0.0;   x_P[i].im= 0.0;
		h_P[i].re=taps_r[i];
		h_P[i].im=taps_i[i];
		
	}
          
	SET_CELL_SIZE_IN(0,sizeof(complex));
	SET_CELL_SIZE_OUT(0,sizeof(complex));

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 




	while(IT_IN(0)){
		/*
		 * Shift input sample into tapped delay line
		 */
		tmp2=x(0);
		for(i=0; i<NTaps; i++) {
			tmp1=x_P[i];
			x_P[i]=tmp2;
			tmp2=tmp1;
		}
		/*
		 * Compute inner product
		 */
                sum.re = 0.0; sum.im=0.0;
		for (i=0; i<NTaps; i++) {

                     sum.re += x_P[i].re*h_P[i].re+x_P[i].im*h_P[i].im;
                     sum.im += x_P[i].im*h_P[i].re-x_P[i].re*h_P[i].im;

		}
		if(IT_OUT(0)) {
			KrnOverflow("cxchmodel",0);
			return(99);
		}
		/*
	  	 * set output buffer to response result
		 */
		y(0) = sum;
	}

]]>
</MAIN_CODE> 

<WRAPUP_CODE>
<![CDATA[ 

	free(x_P); free(h_P); 

]]>
</WRAPUP_CODE> 



</BLOCK> 

