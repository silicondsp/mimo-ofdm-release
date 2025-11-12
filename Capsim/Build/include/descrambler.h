

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



#define  N 127

static char SEQU_TBL[2*N+2] = {
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

static int INDX_TBL[N+1]=  {  0,  31, 32, 62,  33,  93, 63, 7,
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

void DeScrambler(
                  short * init_seed,   // input, initial state of Descrambler
                  char * input,        // input, input sequence to be descrambled
                  char * output,       // output, descramblered sequence
                  int N_INPUT)         // input, length of input/output sequences
{
	int indx, skip, k;
	short * s;
	char * sequence;

	// compute index to the table
	s = init_seed;
	indx = (int) s[0]+2*(s[1]+2*(s[2]+2*(s[3]+2*(s[4]+2*(s[5]+2*s[6]) ) ) ) );

    // determine how many entries to skip
    skip = (int)*(INDX_TBL + indx);

	sequence = SEQU_TBL + skip;

	// scramble the input sequence
	/* generate scrambler sequence */
    for(k = 0; k<N_INPUT; k++)
	{
       output[k] = (*sequence)^(*input);
	   sequence++;
	   input++;
	}
	return;
}
