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

<BLOCK_NAME>
pilot
</BLOCK_NAME> 

<DESC_SHORT>
pilot
</DESC_SHORT>

<COMMENTS>
<![CDATA[ 

/*
                pilot()
    perform pilot insertion.
	programmer:    Bin Huang
	date:          6/11/02
*/
]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 

#include "typedef.h"
#include "anisim.h"
#include "ftab_80211a.h"

]]>
</INCLUDES> 

<DEFINES> 

#define N 64
#define M54 216
#define Sym 48

</DEFINES> 

<DECLARATIONS> 

 int i,j=0,k;
 int no_samples;
 int index;
 complex  xx, tem;
 double tmp;

</DECLARATIONS> 




<STATES>
	<STATE>
		<TYPE> complex* </TYPE>
		<NAME> xi </NAME>
	</STATE>
	<STATE>
		<TYPE> complex* </TYPE>
		<NAME> yi </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> pointCount </NAME>
		<VALUE> 0 </VALUE>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> pilotIndex </NAME>
		<VALUE> 1 </VALUE>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> numberOfSym </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> numberOfSam </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> cntOfSym </NAME>
		<VALUE> 0 </VALUE>
	</STATE>
</STATES>



<PARAMETERS>
	<PARAM>
		<DEF> number of input bits per packet </DEF>
		<TYPE> int </TYPE>
		<NAME> numOfBits </NAME>
		<VALUE> 0 </VALUE>
	</PARAM>
</PARAMETERS>



<INPUT_BUFFERS>
	<BUFFER>
		<TYPE> complex </TYPE>
		<NAME> x </NAME>
	</BUFFER>
</INPUT_BUFFERS>



<OUTPUT_BUFFERS>
	<BUFFER>
		<TYPE> complex </TYPE>
		<NAME> yout </NAME>
	</BUFFER>
</OUTPUT_BUFFERS>

<INIT_CODE>
<![CDATA[ 

    tmp = (double) (16 + numOfBits + 6)/M54;
    numberOfSym = (int) ceil(tmp);                   // number of data symbols
    numberOfSam= numberOfSym * Sym;                   // number of data symbols
 /* allocate memory and return pointers for internal states xi and yi */
 if((xi = (complex*)calloc(N,sizeof(complex))) == NULL ||
   (yi = (complex*)calloc(N,sizeof(complex))) == NULL) {
   fprintf(stderr,"pilot: can't allocate work space\n");
   return(4);
   }
  /* initialize the internal states to be zeros  */
    SET_CELL_SIZE_IN(0,sizeof(complex));
    SET_CELL_SIZE_OUT(0,sizeof(complex));

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 


 for (no_samples = MIN_AVAIL();no_samples>0; --no_samples)
  {
         IT_IN(0);
         index = pilotMapping[pointCount];
         xx.re = x(0).re;
         xx.im = x(0).im;
         xi[index] = xx;
         pointCount++;             /* read in all input into internal buffer */
		 cntOfSym++;               // count all symbols and then set pilot index zero

  /* once 48 complex samples have been read in, process them */

    if ( pointCount == 48){

      pointCount = 0;

      xi[5].re = 1.0;              /* insert pilot   */
      xi[5].im = 0.0;
      xi[19].re = 1.0;
      xi[19].im = 0.0;
      xi[32].re = 1.0;
      xi[32].im = 0.0;
      xi[46].re = -1.0;
      xi[46].im = 0.0;

     /* adding zeros  */

     for (i=0; i<6; i++)
       {
         yi[i].re = 0.0;
         yi[i].im = 0.0;
       }

     for (i=0; i<26; i++)
      {
         yi[i+6].re = xi[i].re;
         yi[i+6].im = xi[i].im;
       }

       yi[32].re = 0.0;
       yi[32].im = 0.0;

     for(i=26; i<52; i++)
       {
         yi[i+7].re = xi[i].re;
         yi[i+7].im = xi[i].im;
       }

     for(i=0;i<5;i++)
       {
         yi[i+59].re = 0.0;
         yi[i+59].im = 0.0;
       }


	/* need to swap first -26 to -1 with last 1 to 26  in order to come up with
           input to IFFT   */


          Swap(yi,32);

    //      for(i=0; i<N;i++)
    //       {
    //        printf("pilotInput %d %f %f\n",i, yi[i].re,yi[i].im);
    //       }
	
	/*  add polarity control for pilot subcarriers   */

            Polarity(yi, pilotIndex);

            pilotIndex++;

            if (pilotIndex == 127)
             {
               pilotIndex = 0;
             }

	
	  for (i=0;i<N;i++)
	    {
	       if(IT_OUT(0)){
	          KrnOverflow("pilot",0);
	          return(99);
	       }
	
	       tem.re = yi[i].re;
	       tem.im = yi[i].im;
	       yi[i].re = 0.0;          /* yi[i] needs to be cleared  */
	       yi[i].im = 0.0;
	//        printf("pilot   %d  %f  %f\n",i,tem.re,tem.im );
	       yout(0) = tem;
	     }
       }

	   if(cntOfSym == numberOfSam)      // for multi-packet usage
	    {
		  cntOfSym = 0;
		  pilotIndex = 0;
	//	  fprintf(stderr,"%d \n",pilotIndex); 
         }
   }	
	
	






]]>
</MAIN_CODE> 

<WRAPUP_CODE>
<![CDATA[ 


]]>
</WRAPUP_CODE> 



</BLOCK> 

