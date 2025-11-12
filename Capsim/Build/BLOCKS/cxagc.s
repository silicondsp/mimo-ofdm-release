<BLOCK>
<LICENSE>

/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 2006-2017   Silicon DSP  Corporation

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
cxagc
</BLOCK_NAME> 

<COMMENTS>
<![CDATA[ 

/* cxagc.s */
/***************************************************************
			cxagc() 
*******************************************************************
	Input:		x, the signal of interest
	Output:		optional:  terminate signal or flow through
*******************************************************************
This block adjust the gain to achieve a target rms value.
Programmer: 	Sasan Ardalan
Date:		Sept. 1, 2006

*/
]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 

#include <math.h>
#include <stdio.h>

]]>
</INCLUDES> 

<DECLARATIONS> 

	int i,j;
	float xSample;	/* current sample of input signal	*/
	float xr,xi;
	float mag,rmsVal;
	complex val;

</DECLARATIONS> 




<STATES>
	<STATE>
		<TYPE> float </TYPE>
		<NAME> gain </NAME>
		<VALUE> 1.0 </VALUE>
	</STATE>

	<STATE>
		<TYPE> int </TYPE>
		<NAME> count </NAME>
		<VALUE> 0 </VALUE>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> totalCount </NAME>
		<VALUE> 0 </VALUE>
	</STATE>
	<STATE>
		<TYPE> float </TYPE>
		<NAME> sum </NAME>
		<VALUE> 0.0 </VALUE>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> freezeAGC </NAME>
		<VALUE> 0 </VALUE>
	</STATE>	
	
</STATES>



<PARAMETERS>
	<PARAM>
		<DEF> Target rms </DEF>
		<TYPE> float </TYPE>
		<NAME> targetRMS </NAME>
		<VALUE> 0.08 </VALUE>
	</PARAM>	
	<PARAM>
		<DEF> Points to skip </DEF>
		<TYPE> int </TYPE>
		<NAME> skip </NAME>
		<VALUE> 0 </VALUE>
	</PARAM>
	<PARAM>
		<DEF> Window size </DEF>
		<TYPE> int </TYPE>
		<NAME> agcWindowSize </NAME>
		<VALUE> 32 </VALUE>
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
		<NAME> y </NAME>
	</BUFFER>
</OUTPUT_BUFFERS>

<INIT_CODE>
<![CDATA[ 
         gain=1.0;
         freezeAGC=0;
	 count=0;
	 totalCount=0;
]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 


	/* note the minimum number of samples on the input 	*/
	/* buffers and iterate that many times 			*/
	for(i=MIN_AVAIL();i>0; --i) {
    	     IT_IN(0);
	  
			if(IT_OUT(0)) {
				KrnOverflow("cxagc",0);
				return(99);
			}
			val=x(0);
			val.re= val.re*gain;
			val.im= val.im*gain;
			y(0) = val;
	     if(freezeAGC==0) {
//              printf("x=%f+j%f\n",x(0).re,x(0).im);
	        if(++totalCount > skip) {

			if (count<agcWindowSize){
				count++;
				xr = x(0).re;		

				xi = x(0).im;		
                                sum +=  xr*xr+xi*xi;
				

	      	        }

			if (count==agcWindowSize){
			        rmsVal=sqrt(sum/(float)agcWindowSize);
				gain=targetRMS/rmsVal;
				printf("cxagc rmsVal=%f gain=%f \n",rmsVal, gain);
				freezeAGC=1;
			
			
			}

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

