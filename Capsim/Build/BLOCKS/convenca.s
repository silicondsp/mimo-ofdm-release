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
convenca
</BLOCK_NAME> 

<COMMENTS>
<![CDATA[ 

/* convenca.s */
/******************************************************************
			convenca()
*******************************************************************
Accepts 27 ints carrying 27*8 = 216 bits packed as b7 b6 b5 b4 b3 b2 b1 b0. Bits are
repacked to form 7 unsigned long int ~~ 32 bit words.
Call to function convenc.c produces the same number of output bits packed the same way.
Within the block function output bits are repacked as 8 bits per int to form 27 output integers.
prev6 contains 24 last bits from the previous input stream (only 6 bits are needed
hence the name). It is initialized to 0 when convenc.c is first called.
*/
]]>
</COMMENTS> 

<DESC_SHORT>
COnvolutional ENcoder 802.11a
</DESC_SHORT>


<INCLUDES>
<![CDATA[ 

#include "typedef.h"
#include "anisim.h"

]]>
</INCLUDES> 

<DECLARATIONS> 

	int i,j, k;
	unsigned long int  xval;
	unsigned long int  yval;
	int N1;

</DECLARATIONS> 




<STATES>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> count </NAME>
		<VALUE> 0 </VALUE>
	</STATE>
	<STATE>
		<TYPE> ULINT* </TYPE>
		<NAME> x_P </NAME>
	</STATE>
	<STATE>
		<TYPE> ULINT* </TYPE>
		<NAME> a_P </NAME>
	</STATE>
	<STATE>
		<TYPE> ULINT* </TYPE>
		<NAME> b_P </NAME>
	</STATE>
	<STATE>
		<TYPE> ULINT </TYPE>
		<NAME> prev6 </NAME>
	</STATE>
</STATES>



<PARAMETERS>
	<PARAM>
		<DEF> Number of words to input </DEF>
		<TYPE> int </TYPE>
		<NAME> NWORDS </NAME>
		<VALUE> 7 </VALUE>
	</PARAM>
</PARAMETERS>



<INPUT_BUFFERS>
	<BUFFER>
		<TYPE> int </TYPE>
		<NAME> x </NAME>
	</BUFFER>
</INPUT_BUFFERS>



<OUTPUT_BUFFERS>
	<BUFFER>
		<TYPE> int </TYPE>
		<NAME> achan </NAME>
	</BUFFER>
	<BUFFER>
		<TYPE> int </TYPE>
		<NAME> bchan </NAME>
	</BUFFER>
</OUTPUT_BUFFERS>

<INIT_CODE>
<![CDATA[ 

         x_P=(ULINT*)calloc(NWORDS,sizeof(ULINT));
         a_P=(ULINT*)calloc(NWORDS,sizeof(ULINT));
         b_P=(ULINT*)calloc(NWORDS,sizeof(ULINT));
         if(x_P == NULL || a_P ==NULL || b_P==NULL)  {
             fprintf(stderr,"convenca:Could not allocate space\n");
             return(3);
         }
         prev6 = 0;

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 


	for(i=MIN_AVAIL();i>0; --i) {
                x_P[count] = (unsigned long int) 0;
		IT_IN(0);
		xval = x(0);		
		x_P[count] += (xval&0xFF);
				
		IT_IN(0);
		xval = x(0);				
		x_P[count]+= ((xval&0xFF)<<8);
		i--;		
                		
		IT_IN(0);		
		xval = x(0);		
		x_P[count]+= ((xval&0xFF)<<16);		
                i--;
                		
		if( (i-1) - 27*floor((i-1)/27) != 0 )
		{			
		     IT_IN(0);	
		     xval = x(0);		
		     x_P[count]+= ((xval&0xFF)<<24);					
		     i--;
		}			
		count++;
		if(count == NWORDS)
		{
              //        fprintf(stdout, " x_P[5] is = %d \n", x_P[count-2]);		
              //        fprintf(stdout, " x_P[6] is = %d \n", x_P[count-1]);		
		      convenc(x_P, prev6, a_P, b_P, NWORDS);
		      prev6 = (x_P[6])<<8;
		      N1 = 4;
		      for(j=0; j<NWORDS; j++) {
		                xval = a_P[j];		
		                yval = b_P[j];
		                if(j==NWORDS-1)
		                {
		                    N1 = 3;
		                }
		                for(k=0; k<N1; k++){
		                         if(IT_OUT(0)) {
					          KrnOverflow("operate",0);
					          return(99);
				         }
				         achan(0)=(int) (xval&0x00FF);
				         xval = (xval>>8);
				         if(IT_OUT(1)) {
					          KrnOverflow("operate",0);
					          return(99);
				         }
				   //      printf("conv   %d  %d\n",k, yval&0x00FF );
				         bchan(0)=(int) (yval&0x00FF);
				         yval = (yval>>8);
		                }
							
		       }
		       count=0;		
		}

	}
	return(0);

]]>
</MAIN_CODE> 

<WRAPUP_CODE>
<![CDATA[ 


]]>
</WRAPUP_CODE> 



</BLOCK> 

