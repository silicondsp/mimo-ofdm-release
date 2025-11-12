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
FQAM_64map
</BLOCK_NAME> 

<DESC_SHORT>
 Floating point 802.11a 64-QAM mapping function
</DESC_SHORT>



<COMMENTS>
<![CDATA[ 

/*
 File:                   FQAM_64map.s
 Description: Floating point 802.11a 64-QAM mapping function, total number of
              input bits is 288. The output should be 48 complex symbols.
   Programmer:         Bin Huang
   Date:               8/21/01
*/
]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 

#include <math.h>
#include "ftab_80211a.h"

]]>
</INCLUDES> 

<DEFINES> 

#define  NBITS 288
#define  NSIZE 48

</DEFINES> 

<DECLARATIONS> 

  int tableIndex,i,j;
  float  real, imag;
  complex cl;

</DECLARATIONS> 




<STATES>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> numberBits </NAME>
	</STATE>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> qaminput </NAME>
	</STATE>
	<STATE>
		<TYPE> complex* </TYPE>
		<NAME> qam </NAME>
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
		<TYPE> complex </TYPE>
		<NAME> output </NAME>
	</BUFFER>
</OUTPUT_BUFFERS>

<INIT_CODE>
<![CDATA[ 

   if((qaminput = (int*)calloc(NBITS,sizeof(int))) == NULL ||
       (qam = (complex*)calloc(NSIZE,sizeof(complex))) == NULL) {
   fprintf(stderr,"QAM: can't allocate work space\n");
   return(4);
   }
   numberBits = 0;
   SET_CELL_SIZE_OUT(0,sizeof(complex));

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 


 while(IT_IN(0))
    {
       qaminput[numberBits] = x(0);
       numberBits++;
       if (numberBits == NBITS)
         {
           numberBits = 0;
           j = 0;
           for (i=0; i<NBITS; i+=6)
             {
               tableIndex = qaminput[i]+2*qaminput[i+1]+4*qaminput[i+2]+8*qaminput[i+3]+16*qaminput[i+4]+32*qaminput[i+5];
        //       printf("QAM   %d\n", tableIndex);
               real = QAM_64MAPTable[0][tableIndex];
               imag = QAM_64MAPTable[1][tableIndex];
               qam[j].re = real;
               qam[j].im = imag;
               j++;
             }

          for (i=0; i<NSIZE; i++)
           {
           if (IT_OUT(0))
            {
              KrnOverflow("FQAM_64map", 0);
              return(99);
            }

           cl.re = qam[i].re;
           cl.im = qam[i].im;
  //          printf("QAM   %f  %f\n", cl.re,cl.im);
           output(0) = cl;

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

