

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

/* 
File:                   puncture.c
Description: c-code model for puncturing

*/

enum codingRate {RATE_12=12,RATE_34=34,RATE_23=23};
//#define NUM_DATA_RATES 8
//#define MAX_BYTES_PER_BITSTREAM ((432+7)/8)
//#define SPLAT_BUFFER 10  //efficient algorithm overruns minimal data size, so what
//#define MAX_BYTES_OUTPUT ((7*4)+SPLAT_BUFFER)
/*

struct rateInfo {
	int dataRate;
	int codingRate;
	int codedBitsSubcarrier;
	int codedBitsSymbol;
	int dataBitsSymbol;
};

/* extern void puncture(
		int codingRate,
		unsigned long ABits[],
		unsigned long BBits[],
		int dataBitsSymbol,
		int codedBitsSymbol,
		unsigned long* outputBuf);

extern void puncFast(
		int codingRate,
		//unsigned char bitstreamA[],
		//unsigned char bitstreamB[],
		//int dataBitsSymbol,
		int codedBitsSymbol
		//unsigned char outputBuf[]
		);

void	puncFast12(
		int codingRate,
		int outsize
		);
void	puncFast34(
		int codingRate,
		int outsize
		);
void	puncFast23(
		int codingRate,
		int outsize
		);


//control warning BOPS compiler pragmas, so they don't get intrusive
#if !defined _BOPS && defined _WIN32
#pragma warning( disable : 4068 )  // Disable warning messages
#endif
*/
