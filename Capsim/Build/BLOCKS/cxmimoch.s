<BLOCK>
<LICENSE>

/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 2000-2017   Silicon DSP  Corporation

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

<BLOCK_NAME>cxmimoch</BLOCK_NAME> 

<COMMENTS>
<![CDATA[ 

/* cxmimoch.s */
/***********************************************************************
                             cxmimoch()
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

Random Gaussian Variable Generation Pryson Pate, NC State 1989.


<NAME>
cxmimoch
</NAME>
<DESC_SHORT>
This block convolves  the input samples with the computed complex channel impulse response.
</DESC_SHORT>
<DESCRIPTION>
</DESCRIPTION>
<PROGRAMMERS>
Date:  August 28, 2006 
Programmer: Sasan Ardalan
Modified: June 29, 2007 extended to MIMO with auto fan-in and fan-out
</PROGRAMMERS>
*/

]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 


]]>
</INCLUDES> 

<DEFINES> 


#define RAND_LARGE 0x7fffffff
#define DEC

#define MAX_TAPS 1024

</DEFINES> 


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
     

<STATES>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>Ndiv2</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>NTaps</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>numberTxAntennas</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>numberRxAntennas</NAME>
	</STATE>
	<STATE>
		<TYPE>complex***</TYPE>
		<NAME>h_P</NAME>
	</STATE>

	<STATE>
		<TYPE>complex**</TYPE>
		<NAME>x_P</NAME>
	</STATE>

	<STATE>
		<TYPE>complex**</TYPE>
		<NAME>sum_P</NAME>
	</STATE>

	
</STATES>
 
<DECLARATIONS> 

 	complex tmp1,tmp2;
        complex  sum;
        complex tmp;
	FILE *fp;
	char fileName[256];

        double taps_r[MAX_TAPS];
        double taps_i[MAX_TAPS];
        double vark[MAX_TAPS];

       
        float sampTimeNsec;
        float var0;
        int Kmax;
        int i,j,k;
        int samples;
        double s,t,u,v,w,x;
        float y1,y2;
        int trouble;
        long 	seed=775499;
        float std=1.0;


        int iRx, iTx;
        complex val;
       
	
	
	
</DECLARATIONS> 

       


    


 
<INIT_CODE>
<![CDATA[ 

        printf("Initializing %s\n",STAR_NAME);


	/* store as state the number of input/output buffers */
	if((numberTxAntennas = NO_INPUT_BUFFERS()) < 1) {
		fprintf(stderr,"cxmimoch: no input buffers\n");
		return(2);
	}
	if((numberRxAntennas = NO_OUTPUT_BUFFERS()) < 1) {
		fprintf(stderr,"cxmimoch: no output buffers\n");
		return(3);
	}
	for (i=0; i<numberTxAntennas; i++) 
		SET_CELL_SIZE_IN(i,sizeof(complex));
	for (i=0; i<numberRxAntennas; i++) 
		SET_CELL_SIZE_OUT(i,sizeof(complex));

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
        fprintf(stderr,"cxmimoch too many Taps Kmax=%d \n",Kmax);
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


/*
 * Allocate H matrix Time Domain
 */
h_P=(complex ***) calloc(numberTxAntennas,sizeof(complex**));
if(h_P==NULL) {
           fprintf(stderr,"cxmimoch could not allocate H matrix\n");
	   return(4);

}
for(i=0; i<numberTxAntennas; i++) {

    h_P[i]=(complex **) calloc(numberRxAntennas,sizeof(complex*));
    if(h_P[i]==NULL) {
           fprintf(stderr,"cxmimoch could not allocate H matrix\n");
	   return(5);
    }
    for(j=0; j<numberRxAntennas; j++) {
         h_P[i][j]=(complex *) calloc(Kmax,sizeof(complex));
         if(h_P[i]==NULL) {
              fprintf(stderr,"cxmimoch could not allocate H matrix\n");
	     return(6);

         }
    }
}

NTaps=Kmax;

/*
 * Allocate tapped delay lines
 */
x_P=(complex **) calloc(numberTxAntennas,sizeof(complex*));
if(x_P==NULL) {
           fprintf(stderr,"cxmimoch could not allocate tapped delay line \n");
	   return(7);

}
for(i=0; i<numberTxAntennas; i++) {

    x_P[i]=(complex *) calloc(NTaps,sizeof(complex));
    if(x_P[i]==NULL) {
           fprintf(stderr,"cxmimoch could not allocate tapped delay line \n");
	   return(8);
    }
 
}



/*
 * Allocate individual convolution results to each receive antenna from tx antenna
 */
sum_P=(complex **) calloc(numberTxAntennas,sizeof(complex*));
if(sum_P==NULL) {
           fprintf(stderr,"cxmimoch could not allocate sum\n");
	   return(9);

}
for(i=0; i<numberTxAntennas; i++) {

    sum_P[i]=(complex *) calloc(numberRxAntennas,sizeof(complex));
    if(sum_P[i]==NULL) {
           fprintf(stderr,"cxmimoch could not allocate sum\n");
	   return(10);
    }
}

fprintf(fp,"%d %d %d\n",numberTxAntennas,numberRxAntennas,Kmax);


seed=seedParam;
#ifdef DEC
srandom(seed);
#else
srand48((long int)seed);
#endif

for(iTx=0; iTx<numberTxAntennas; iTx++) {
    for(iRx=0; iRx<numberRxAntennas; iRx++) {
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
		          fprintf(stderr,"cxmimoch: problem with random number\
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
// printf("%d\t%f\t%f\n",k,y1,y2);

            fprintf(fp,"%lf\t%lf\n",taps_r[k],taps_i[k]);

            h_P[iTx][iRx][k].re=taps_r[k];
            h_P[iTx][iRx][k].im=taps_i[k];



        } // end for loop for k

   } // end iRx
}   // end iTx

fclose(fp);

//+++++++++++


        Ndiv2=NTaps/2;

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 




   for(samples = MIN_AVAIL(); samples >0; --samples) {
          for(iTx=0; iTx<numberTxAntennas; ++iTx) {
                 IT_IN(iTx);
                 val = INCX(iTx,0);

		/*
		 * Shift input sample into tapped delay line
		 */
		tmp2=val;
		for(i=0; i<NTaps; i++) {
			tmp1=x_P[iTx][i];
			x_P[iTx][i]=tmp2;
			tmp2=tmp1;
		}
                for(iRx=0; iRx<numberRxAntennas; ++iRx) {
		   /*
		    * Compute inner product from iTx to iRx
		    */
                   sum_P[iTx][iRx].re = 0.0; sum_P[iTx][iRx].im=0.0;
		   for (i=0; i<NTaps; i++) {

                     sum_P[iTx][iRx].re += x_P[iTx][i].re*h_P[iTx][iRx][i].re-x_P[iTx][i].im*h_P[iTx][iRx][i].im;
                     sum_P[iTx][iRx].im += x_P[iTx][i].im*h_P[iTx][iRx][i].re+x_P[iTx][i].re*h_P[iTx][iRx][i].im;

		   }
               }  // end iRx

         }  //end iTx

         for(iRx=0; iRx<numberRxAntennas; ++iRx) {
              sum.re = 0.0; sum.im=0.0;
              for(iTx=0; iTx<numberTxAntennas; ++iTx) {
                    sum.re += sum_P[iTx][iRx].re;
                    sum.im += sum_P[iTx][iRx].im;

              }
              if(IT_OUT(iRx)) {
                         KrnOverflow("cxmimoch",iRx);
                                return(99);
              }
              OUTCX(iRx,0) = sum;


         }

    } // end samples

]]>
</MAIN_CODE> 

<WRAPUP_CODE>
<![CDATA[ 
for(i=0;i<numberTxAntennas; i++) {
       for(j=0;j<numberRxAntennas; j++) {
              free(h_P[i][j]);
       }
       free(h_P[i]);
}
free(h_P);
for(i=0;i<numberTxAntennas; i++) {
        free(x_P[i]);
}
free(x_P);

for(i=0;i<numberTxAntennas; i++) {
        free(sum_P[i]);
}
free(sum_P);	

]]>
</WRAPUP_CODE> 



</BLOCK> 

