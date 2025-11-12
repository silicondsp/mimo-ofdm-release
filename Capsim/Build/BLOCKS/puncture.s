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
puncture
</BLOCK_NAME> 


<DESC_SHORT>
puncture
</DESC_SHORT>


<COMMENTS>
<![CDATA[ 

/*
                   puncture()
 puncturing function used to come up the coding rate with 1/2,2/3 and 3/4.
 programmer:      Bin Huang
 date:            10/11/01
*/
]]>
</COMMENTS> 

<INCLUDES>
<![CDATA[ 

#include "math.h"
#include <stdio.h>

]]>
</INCLUDES> 

<DEFINES> 

#define N 216
#define N54  288
#define RATE_12 12
#define RATE_34 34
#define RATE_23 23

</DEFINES> 

<DECLARATIONS> 

	int count;
	int maxBits;
	int tempA,tempB;
	int insize,outsize;
	int i;
	int no_samples;

</DECLARATIONS> 




<STATES>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> stateA </NAME>
	</STATE>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> stateB </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> numBits </NAME>
	</STATE>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> punctureBuff </NAME>
	</STATE>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> Ap </NAME>
	</STATE>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> Bp </NAME>
	</STATE>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> BSOp </NAME>
	</STATE>
</STATES>



<PARAMETERS>
	<PARAM>
		<DEF> codingRates are 12 23 34. </DEF>
		<TYPE> int </TYPE>
		<NAME> codingRate </NAME>
		<VALUE> RATE_34 </VALUE>
	</PARAM>
	<PARAM>
		<DEF> dataRate=54 </DEF>
		<TYPE> int </TYPE>
		<NAME> dataRate </NAME>
		<VALUE> 54 </VALUE>
	</PARAM>
</PARAMETERS>



<INPUT_BUFFERS>
	<BUFFER>
		<TYPE> int </TYPE>
		<NAME> dataA </NAME>
	</BUFFER>
	<BUFFER>
		<TYPE> int </TYPE>
		<NAME> dataB </NAME>
	</BUFFER>
</INPUT_BUFFERS>



<OUTPUT_BUFFERS>
	<BUFFER>
		<TYPE> int </TYPE>
		<NAME> BitStolen </NAME>
	</BUFFER>
</OUTPUT_BUFFERS>

<INIT_CODE>
<![CDATA[ 

 /* allocate memory and return pointers for internal states*/
 if((stateA= (int*)calloc(N,sizeof(int))) == NULL ||
   (stateB = (int*)calloc(N,sizeof(int))) == NULL ||
    (punctureBuff = (int*)calloc(N54,sizeof(int))) == NULL ||
    (Ap = (int*)calloc(N54,sizeof(int))) == NULL ||
    (Bp = (int*)calloc(N54,sizeof(int))) == NULL ||
    (BSOp = (int*)calloc(N54,sizeof(int))) == NULL ) {
   fprintf(stderr,"puncture: can't allocate work space\n");
   return(4);
   }
   numBits=0;

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 



for (no_samples = MIN_AVAIL();no_samples>0; --no_samples)
  {

  IT_IN(0);        /*read input from buffer*/
  IT_IN(1);
  tempA=dataA(0);
  tempB=dataB(0);

  switch (dataRate)
 	{
 	default:
 	case 54:
 	   insize=216;
 	   outsize=288;
 	//   numBytes=insize/8;
 	   break;

 	}

  /*convert from 8 bits per input value coming from conv. coder to 1 bit per element in the array*/
  for (i=0;i<8;i++)
  	{
  	stateA[numBits]=tempA&1;  tempA=tempA>>1;
  	stateB[numBits]=tempB&1;  tempB=tempB>>1;
  	numBits++;
  	}
  if (numBits ==insize)
  {/*once you get enough bits for a symbol, do puncture work here*/
	//create the bit-stolen output,
	numBits = 0;
	Ap=stateA;
	Bp=stateB;
	BSOp=punctureBuff;
	
	switch (codingRate)
	{
		case RATE_12:  //just copy input to output, alternating A, then B

			count=0;
			do
			{
				*BSOp++ = *Ap++; count++;
				*BSOp++ = *Bp++; count++;
			} while (count<outsize);
			break;

		case RATE_34:  //create pattern: A0,B0,A1,B2
			count=0;
			do
			{
				*BSOp++ = *Ap++; count++;
				*BSOp++ = *Bp++; count++; Bp++;//skip B1
				*BSOp++ = *Ap++; count++; Ap++;//skip A2
				*BSOp++ = *Bp++; count++;
		//	 printf("puncture   %d\n",i,  *--BSOp);
			} while (count<outsize);
			break;
		case RATE_23:  //create pattern: A0,B0,A1
			count=0;
			do
			{
				*BSOp++ = *Ap++; count++;
				*BSOp++ = *Bp++; count++; Bp++;//skip B1
				*BSOp++ = *Ap++; count++;
			} while (count<outsize);
			break;

	} //end switch
	
	
 /*now do the CAPSIM-specific processing for output buffer*/



     for (i=0;i<outsize;i++)
    	{
     	
     	 if(IT_OUT(0)){
	          KrnOverflow("puncture",0);
	          return(99);
	          }
  //      printf("puncture %d  %d\n",i, punctureBuff[i]);	
        BitStolen(0) = punctureBuff[i];


     	}
  }/*end of if clause which really proceses a symbol*/

}  /*end outer for loop*/

]]>
</MAIN_CODE> 

<WRAPUP_CODE>
<![CDATA[ 


]]>
</WRAPUP_CODE> 



</BLOCK> 

