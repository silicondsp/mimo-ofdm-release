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
interlr
</BLOCK_NAME> 

<DESC_SHORT>
interlr
</DESC_SHORT>

<COMMENTS>
<![CDATA[ 

/*
File:                   interlr.s
Description:
     fixed point 802.11a interleaver for rate=48,54 Mbps, total number of
     input bits is 288.
Author                        Bin Huang
date created                   10/6/01
*/
]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 

#include <math.h>
#include <stdio.h>
#include "ftab_80211a.h"

]]>
</INCLUDES> 

<DEFINES> 

#define NUMOFBITS   288

</DEFINES> 

<DECLARATIONS> 

   int i;
   int Lp;

</DECLARATIONS> 




<STATES>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> interX </NAME>
	</STATE>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> interY </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> numBits </NAME>
		<VALUE> 0 </VALUE>
	</STATE>
</STATES>



<INPUT_BUFFERS>
	<BUFFER>
		<TYPE> int </TYPE>
		<NAME> x </NAME>
	</BUFFER>
</INPUT_BUFFERS>



<OUTPUT_BUFFERS>
	<BUFFER>
		<TYPE> int </TYPE>
		<NAME> y </NAME>
	</BUFFER>
</OUTPUT_BUFFERS>

<INIT_CODE>
<![CDATA[ 

 /* allocate memory and return pointers for internal states bx */
 if((interX = (int*)calloc(NUMOFBITS,sizeof(int))) == NULL ||
   (interY = (int*)calloc(NUMOFBITS,sizeof(int))) == NULL) {
   fprintf(stderr,"interleaver: can't allocate work space\n");
   return(4);
   }

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 


 while(IT_IN(0))
    {
      interX[numBits] = x(0);
      numBits++;                   /* read all 288 bits into internal buffer */

       if (numBits == NUMOFBITS){

        numBits = 0;
        for (i=0;i<NUMOFBITS;i++)
          {
            Lp = interlrIndexTable[i];
            interY[Lp] = interX[i];
          }

        for (i=0;i<NUMOFBITS;i++)
           {
             if(IT_OUT(0)){
	          KrnOverflow("interleaver",0);
	          return(99);
	          }
	  //    printf("interleaver   %d  %d\n",i,  interY[i]);
	     y(0) = interY[i];
	    }
	}
}







]]>
</MAIN_CODE> 

<WRAPUP_CODE>
<![CDATA[ 


]]>
</WRAPUP_CODE> 



</BLOCK> 

