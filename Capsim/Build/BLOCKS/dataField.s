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
dataField
</BLOCK_NAME> 

<DESC_SHORT>
Data Field 802.11a
</DESC_SHORT>

<COMMENTS>
<![CDATA[ 

/*
File:                     dataField()
Description:    will create data field which includes 16 service bits, data bits(PSDU)
                6 tail bits and Pad bits. In this function, the number of OFDM symbols
                and the number of Pad bits will be decided. The number of OFDM symbols
                will be sent to Signal packet. remember this file is only for 54 Mbps(
                288 bits)currently, the general one( for 48,96,192 and 288 bits) will
                be made later.
<Author>                        Bin Huang
<date created>                  10/4/01
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

<DEFINES> 

#define N_DBPS54 216              /* for 54 Mbps */
#define SERVICE  16               /* the number of service bits */
#define TAIL 6                    /* number of tail bits */
#define N  32832                  /* the max number of bits in DATA field: N_data */

</DEFINES> 

<DECLARATIONS> 

double temp;
double Lp;
int nData, nPad,i;
int nSym;

</DECLARATIONS> 




<STATES>
	<STATE>
		<TYPE> float* </TYPE>
		<NAME> interX </NAME>
	</STATE>
	<STATE>
		<TYPE> int* </TYPE>
		<NAME> interY </NAME>
	</STATE>
	<STATE>
		<TYPE> int </TYPE>
		<NAME> numBits </NAME>
	</STATE>
</STATES>



<PARAMETERS>
	<PARAM>
		<DEF>  the  number of PSDU(data bits)  </DEF>
		<TYPE> int </TYPE>
		<NAME> numPSDU </NAME>
		<VALUE> 64 </VALUE>
	</PARAM>
</PARAMETERS>



<INPUT_BUFFERS>
	<BUFFER>
		<TYPE> float </TYPE>
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

 /* allocate memory and return pointers for internal states interX */
 if((interX = (float*)calloc(numPSDU,sizeof(float))) == NULL ||
   (interY = (int*)calloc(numPSDU+SERVICE+TAIL+N_DBPS54,sizeof(int))) == NULL) {
   fprintf(stderr,"Datafield: can't allocate work space\n");
   return(4);
   }
 numBits = 0;

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 


   while(IT_IN(0))
    {
      interX[numBits] = x(0);
      numBits++;

      if (numBits == numPSDU)
       {
        numBits = 0;
        temp = (double) (SERVICE + numPSDU + TAIL)/N_DBPS54;

        Lp = ceil(temp);
        nSym = (int) Lp;

        /* number of bits in DATA field  */

        nData = nSym * N_DBPS54;

        /* number of Pad bits  */

        nPad = nData - (SERVICE + numPSDU + TAIL);

        /* outdata with 16 service bits and 6 tail bits and pad zeros   */

         for (i=0; i<SERVICE; i++)            /* add service bits total 16 bits */
            interY[i] = 0;


         for (i=0; i< numPSDU; i++)           /* add PSDU */
            interY[i+SERVICE] = (int) interX[i];

         for (i=0; i<nPad+6; i++)      /* add tail bits and pad bits   */
	    interY[i+SERVICE+numPSDU] = 0;
	
	 for (i=0;i<nData;i++)
           {
             if(IT_OUT(0)){
	          KrnOverflow("dataField",0);
	          return(99);
	          }
	
	    // y(0) = interY[i];
	 //   printf("dataField y=%d\n",  interY[i]);
	
	     OUTI(0,0)=   interY[i];
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

