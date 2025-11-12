

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


/*   *********************************************************************

       scrambler()


      perform scrambling.

  Programmer:    Anisim Silvara
  date:          7/2/01

     *********************************************************************
*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "complex.h"
#include "typedef.h"
#include "anisim.h"

#define  NB 216



static char SEQU_TBL[2*NB] = {
0,0,0,0,1,1,1,0,
1,1,1,1,0,0,1,0,
1,1,0,0,1,0,0,1,
0,0,0,0,0,0,1,0,
0,0,1,0,0,1,1,0,
0,0,1,0,1,1,1,0,
1,0,1,1,0,1,1,0,
0,0,0,0,1,1,0,0,
1,1,0,1,0,1,0,0,
1,1,1,0,0,1,1,1,
1,0,1,1,0,1,0,0,
0,0,1,0,1,0,1,0,
1,1,1,1,1,0,1,0,
0,1,0,1,0,0,0,1,
1,0,1,1,1,0,0,0,
1,1,1,1,1,1,1,

0,0,0,0,1,1,1,0,
1,1,1,1,0,0,1,0,
1,1,0,0,1,0,0,1,
0,0,0,0,0,0,1,0,
0,0,1,0,0,1,1,0,
0,0,1,0,1,1,1,0,
1,0,1,1,0,1,1,0,
0,0,0,0,1,1,0,0,
1,1,0,1,0,1,0,0,
1,1,1,0,0,1,1,1,
1,0,1,1,0,1,0,0,
0,0,1,0,1,0,1,0,
1,1,1,1,1,0,1,0,
0,1,0,1,0,0,0,1,
1,0,1,1,1,0,0,0,
1,1,1,1,1,1,1,

0,0 };

static char INDX_TBL[NB] = {   0,  31, 32, 62,  33,  93, 63, 7,
                             34,  38, 94, 46,  64, 115,  8, 124,
                             28,  35, 25, 39, 110,  95, 19, 47,
                             42,  65, 69, 116, 77,   9, 82, 125,
                             29,  91, 36, 113, 26, 108, 40, 75,
                             111, 73, 96, 98,  20,  54, 48, 100,
                             59,  43, 22, 66,  88,  70, 56, 117,
                             120, 78, 50, 10,  14,  83, 102, 126,
                             30,  61, 92,  6,  37,  45, 114, 123,
                             27, 24, 109, 18,  41,  68,  76, 81,
                             90, 112,107, 74,  72,  97,  53, 99,
                             58,  21, 87, 55, 119,  49,  13, 101,
                             60,  5,  44, 122, 23,  17,  67, 80,
                             89, 106, 71, 52,  57,  86, 118, 12,
                             4,  121, 16, 79, 105,  51,  85, 11,
                             3,  15, 104, 84,  2,  103,   1,  0};

static int prev_skip = 0;

void scrambler_216(int * init_seed,           // input, initial seed
                   unsigned char * input,     // input sequence of bytes, LSbit is on/off
                   unsigned char * output,    // output sequence of bytes, all 8 bits
                   int N_INPUT)
{
	int indx, skip, k, count;
	int * s;
	char * sequence;
	char temp[NB];

	// compute index to the table
	s = init_seed;
	indx = (int) s[0]+2*(s[1]+2*(s[2]+2*(s[3]+2*(s[4]+2*(s[5]+2*s[6]) ) ) ) );

    // determine how many entries to skip
        skip = (int)*(INDX_TBL + indx);
        if(indx == 0)
        {
             skip = prev_skip;
        }
 //        printf("scramle_216 %d \n",skip);
	sequence = SEQU_TBL + skip;

	// scramble the input sequence
	/* generate scrambler sequence */
    for(k = 0; k<N_INPUT; k++)
	{
	   /* make sequence behave as a circular buffer */
       temp[k] = (*(sequence + k -(int)(127*floor(k/127))) )^(*input);
	   input++;
	}

		/* compress 1 bit per char into 8 bits per unsigned char */ 
	sequence = temp;
	count = N_INPUT;
    indx = 0;
	while ( count > 0 )
	{
		output[indx] = 0;
	    for(k=0; k<8; k++)
		{
		    if( count > 0 )
			{
		        output[indx] += ((*sequence)<<k);
				sequence++;
			}
		    count = count - 1;
		}
		indx = indx + 1;
	}
	    /* memorize skip for next call */
	prev_skip = skip + 216;
	    /* make sure it is less than 127 */
	prev_skip = prev_skip -(int)(127*floor(prev_skip/127));
	return;
}

