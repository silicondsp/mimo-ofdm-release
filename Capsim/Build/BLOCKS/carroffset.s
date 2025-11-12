<BLOCK>
<LICENSE>

/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 2001-2017   Silicon DSP  Corporation

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
carroffset
</BLOCK_NAME> 

<COMMENTS>
<![CDATA[ 

/* carroffset.s */
/**********************************************************************
                            carroffset()
***********************************************************************
Function has a single complex input buffer, and output
buffer. The parameter is the carrier offset normalized to the carrier spacing.
Author:Sasa Ardalan
Date: August 1, 2001
*/
]]>
</COMMENTS> 

<DESC_SHORT>
Adds carrier offset to complex input stream.
</DESC_SHORT>

<DEFINES> 

#define PI 3.1415926535898

</DEFINES> 

<DECLARATIONS> 

	int numberOfSamples;
	int i;
	complex val;
	complex calc;
        float sinang;
        float cosang;

</DECLARATIONS> 




<STATES>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> numOutBuffers </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> k </NAME>
		<VALUE> 0 </VALUE>
	</STATE>
	<STATE>
		<TYPE> double </TYPE>
		<NAME> angle </NAME>
		<VALUE> 0 </VALUE>
	</STATE>
	<STATE>
		<TYPE> float </TYPE>
		<NAME> delta </NAME>
	</STATE>
</STATES>



<PARAMETERS>
	<PARAM>
		<DEF> Carrier offset </DEF>
		<TYPE> float </TYPE>
		<NAME> offset </NAME>
		<VALUE> 0.0 </VALUE>
	</PARAM>
	<PARAM>
		<DEF> Sampling Rate </DEF>
		<TYPE> float </TYPE>
		<NAME> fs </NAME>
		<VALUE> 20000000 </VALUE>
	</PARAM>
</PARAMETERS>



<INPUT_BUFFERS>
	<BUFFER>
		<TYPE> complex </TYPE>
		<NAME> x </NAME>
	</BUFFER>
</INPUT_BUFFERS>

<INIT_CODE>
<![CDATA[ 

        delta=PI*2*offset/fs;
	/* note and store the number of output buffers */
	if((numOutBuffers = NO_OUTPUT_BUFFERS() ) <= 0) {
		fprintf(stdout,"node: no output buffers\n");
		return(1); /* no output buffers */
	}
	SET_CELL_SIZE_IN(0,sizeof(complex));
	for (i=0; i<numOutBuffers; i++)
		SET_CELL_SIZE_OUT(i,sizeof(complex));

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 


	for(numberOfSamples=MIN_AVAIL();numberOfSamples >0; --numberOfSamples) {
		IT_IN(0);
		for(i=0;i<numOutBuffers;++i) {
			if(IT_OUT(i)) {
				KrnOverflow("carroffset",i);
				return(99);
			}
			val=x(0);

                        angle=fmod(angle+delta,PI*2);
                        cosang=cos(angle);
                        sinang= -sin(angle);
                        calc.re= val.re*cosang-val.im*sinang;

			calc.im = val.re*sinang+val.im*cosang;
			OUTCX(i,0) = calc;
		}
	}

    	return(0);  /* input buffer empty */


]]>
</MAIN_CODE> 

<WRAPUP_CODE>
<![CDATA[ 


]]>
</WRAPUP_CODE> 



</BLOCK> 

