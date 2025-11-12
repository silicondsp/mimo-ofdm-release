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
scramble
</BLOCK_NAME> 

<DESC_SHORT>
scramble
</DESC_SHORT>

<COMMENTS>
<![CDATA[ 

/* scramble.s */
/******************************************************************
			scramble_216()
*******************************************************************
Programmer: 	Anisim Silivra	
Date:	 	Oct. 5, 2001	
Modified:
*/
]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 

#include <math.h>
#include "typedef.h"
#include "anisim.h"

]]>
</INCLUDES> 

<DECLARATIONS> 

	int i,j;
	char  xval;	
	int temp;
	int ed[7] = {1, 0, 1, 1, 1, 0, 1};	

</DECLARATIONS> 




<STATES>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> count </NAME>
		<VALUE> 0 </VALUE>
	</STATE>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> seed </NAME>
	</STATE>
	<STATE>
		<TYPE> char* </TYPE>
		<NAME> x_in </NAME>
	</STATE>
	<STATE>
		<TYPE> char* </TYPE>
		<NAME> x_out </NAME>
	</STATE>
</STATES>



<PARAMETERS>
	<PARAM>
		<DEF> Number of bytes to input </DEF>
		<TYPE> int </TYPE>
		<NAME> N </NAME>
		<VALUE> 216 </VALUE>
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
		<NAME> y </NAME>
	</BUFFER>
</OUTPUT_BUFFERS>

<INIT_CODE>
<![CDATA[ 

         x_in=(char*)calloc(N,sizeof(char));
         x_out=(char*)calloc(N/8,sizeof(char));
         seed = (int*)calloc(7, sizeof(int));
         for(i=0; i<7; i++)
         {
               seed[i] = ed[i];
         }
         if(x_in == NULL || x_out == NULL)  {
             fprintf(stderr,"scrambler:Could not allocate space\n");
             return(3);
         }
/*         SET_CELL_SIZE_OUT(0, sizeof(ULINT) );  */

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 

        while(IT_IN(0))
	{
		xval = (char)x(0);
		x_in[count]=xval;
		count++;
	        if(count == N)
	        {
	              scrambler_216(seed, (unsigned char *)x_in, (unsigned char *)x_out, N);
	              count = 0;
                      for(i=0; i<7; i++)
                      {

                            seed[i] = 0;
                      }	
	
	              for(j=0; j<N/8; j++)
	              {
	                     IT_OUT(0);
	                     temp = (int) 0;
	                     temp += x_out[j];
	                     y(0) = temp;
                      }
	
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

