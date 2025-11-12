

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

   

// by Ayman Elezabi.
// First Generated: 7-24-01.
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//
//
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//
// File Specification ********************************************
//
// NAME: intrlvr.cpp
//
// CONTENTS: tests intrlvr80211a.s
//
// SYSTEM CONFIGURATION: 2x2 
//
// End File Specification ****************************************

//----------------------------------------------------------------
// Includes
//----------------------------------------------------------------
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
//----------------------------------------------------------------
// Types
//----------------------------------------------------------------

//----------------------------------------------------------------
// Constants
//----------------------------------------------------------------
#define N_CBPS		48	// number of code bits per symbol.
#define N_BPSC		N_CBPS/48	// Number of (coded) bits per subcarrier. 
								// 48 is the number of data subcarriers. 
#define NUMBER_OF_PES		4	// 2x2 configuration
#define NUMBER_OF_BITS_PER_PE		N_CBPS / NUMBER_OF_PES
#define REGISTER_SIZE		32

//----------------------------------------------------------------
// Macros
//----------------------------------------------------------------

//----------------------------------------------------------------
// Variables
//----------------------------------------------------------------

//----------------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------------

unsigned int BinaryRandom();

//------------------------------------------------------------------------------------------

void interleaver(
 unsigned long inputBits[],        /*[i]: input data bits   */
 unsigned long outPE0[],           /*[o]: first 1/4 output bits, total 3 32-bit numbers  */
 unsigned long outPE1[],           /*[o]: second 1/4 output bits, total 3 32-bit numbers  */
 unsigned long outPE2[],           /*[o]: third 1/4 output bits, total 3 32-bit numbers  */
 unsigned long outPE3[]            /*[o]:  fourth 1/4 output bits, total 3 32-bit numbers  */
 ) 
{

int ii,jj,kk;		// loop counter variables.
int s;		// interleaver parameter.
//unsigned long inputBits[N_CBPS],intrlvdBits[N_CBPS];
unsigned long intrlvdBits[N_CBPS];
int PE0Data[NUMBER_OF_BITS_PER_PE];
int PE1Data[NUMBER_OF_BITS_PER_PE];
int PE2Data[NUMBER_OF_BITS_PER_PE];
int PE3Data[NUMBER_OF_BITS_PER_PE];

unsigned long PE0r10, PE0r11, PE0r12;	// PE registers that hold the output (interleaved)
unsigned long PE1r10, PE1r11, PE1r12;	// packed bits. 
unsigned long PE2r10, PE2r11, PE2r12;
unsigned long PE3r10, PE3r11, PE3r12;

//FILE *inputFile, *outputFile; 

unsigned long r0,r1,r2,r3,r4,r5,r6,r7,r8;	// PE registers that hold the packed input bits.

// generate input: inputBits[]


// Packing the input bits to save them in a file that is used as input in the asm program
r0=r1=r2=r3=r4=r5=r6=r7=r8= 0;

for (kk=0; kk < REGISTER_SIZE; kk++)
{

	if (inputBits[kk] == 1)
		r0 |= (1 << kk);

	if (inputBits[kk + REGISTER_SIZE] == 1)
		r1 |= (1 << kk);

	if (inputBits[kk + 2*REGISTER_SIZE] == 1)
		r2 |= (1 << kk);

	if (inputBits[kk + 3*REGISTER_SIZE] == 1)
		r3 |= (1 << kk);

	if (inputBits[kk + 4*REGISTER_SIZE] == 1)
		r4 |= (1 << kk);

	if (inputBits[kk + 5*REGISTER_SIZE] == 1)
		r5 |= (1 << kk);

	if (inputBits[kk + 6*REGISTER_SIZE] == 1)
		r6 |= (1 << kk);

	if (inputBits[kk + 7*REGISTER_SIZE] == 1)
		r7 |= (1 << kk);

	if (inputBits[kk + 8*REGISTER_SIZE] == 1)
		r8 |= (1 << kk);

}


/*
fprintf(inputFile,".word 0x%x\n",r0);
fprintf(inputFile,".word 0x%x\n",r1);
fprintf(inputFile,".word 0x%x\n",r2);
fprintf(inputFile,".word 0x%x\n",r3);
fprintf(inputFile,".word 0x%x\n",r4);
fprintf(inputFile,".word 0x%x\n",r5);
fprintf(inputFile,".word 0x%x\n",r6);
fprintf(inputFile,".word 0x%x\n",r7);
fprintf(inputFile,".word 0x%x\n",r8);
*/

//fclose(inputFile);

//s = __max(N_BPSC/2,1);

 if((N_BPSC/2) > 1)
  {
    s = N_BPSC/2;
  }
  else
   {
     s = 1;
   }

for (kk=0; kk < N_CBPS; kk++)
{
ii = (N_CBPS / 16) * (kk%16) + (int) floor(kk/16);

jj = s * (int) floor(ii/s) + ( (ii + N_CBPS - (int) floor(16*ii/N_CBPS)) % s);

// finalBitPos[kk] = jj;

// orig_bit_pos[kk] = kk;

intrlvdBits[jj] = inputBits[kk];

}

// Emulate the distribution of the interleaved (output) bits on all 4 PE's.

for (kk=0; kk < NUMBER_OF_BITS_PER_PE; kk++)
{
	PE0Data[kk] = intrlvdBits[kk];
	PE1Data[kk] = intrlvdBits[kk + NUMBER_OF_BITS_PER_PE];
	PE2Data[kk] = intrlvdBits[kk + 2*NUMBER_OF_BITS_PER_PE];
	PE3Data[kk] = intrlvdBits[kk + 3*NUMBER_OF_BITS_PER_PE];
}


// Pack the interleaved bits in registers for comparison with output of asm code.
// r10, r11, and r12 are used in the variable names since the asm code currently generates the
// interleaved bits in those registers on each PE.

PE0r10 = PE0r11 = PE0r12 =0;
PE1r10 = PE1r11 = PE1r12 =0;
PE2r10 = PE2r11 = PE2r12 =0;
PE3r10 = PE3r11 = PE3r12 =0;

for (kk=0; kk < NUMBER_OF_BITS_PER_PE; kk++)
{
	if(kk < REGISTER_SIZE)
	{
		if (PE0Data[kk] == 1)
			PE0r10 = PE0r10 | (1 << kk);

		if (PE1Data[kk] == 1)
			PE1r10 = PE1r10 | (1 << kk);

		if (PE2Data[kk] == 1)
			PE2r10 = PE2r10 | (1 << kk);

		if (PE3Data[kk] == 1)
			PE3r10 = PE3r10 | (1 << kk);

	}


	else if ( (kk >= REGISTER_SIZE) && (kk < 2*REGISTER_SIZE) )
	{
		if (PE0Data[kk] == 1)
			PE0r11 = PE0r11 | (1 << (kk - REGISTER_SIZE) );

		if (PE1Data[kk] == 1)
			PE1r11 = PE1r11 | (1 << (kk - REGISTER_SIZE) );

		if (PE2Data[kk] == 1)
			PE2r11 = PE2r11 | (1 << (kk - REGISTER_SIZE) );

		if (PE3Data[kk] == 1)
			PE3r11 = PE3r11 | (1 << (kk - REGISTER_SIZE) );

	}

	else	// This occurs only for the 54 Mbps case.
	{
		if (PE0Data[kk] == 1)
			PE0r12 = PE0r12 | (1 << (kk - 2*REGISTER_SIZE) );

		if (PE1Data[kk] == 1)
			PE1r12 = PE1r12 | (1 << (kk - 2*REGISTER_SIZE) );

		if (PE2Data[kk] == 1)
			PE2r12 = PE2r12 | (1 << (kk - 2*REGISTER_SIZE) );

		if (PE3Data[kk] == 1)
			PE3r12 = PE3r12 | (1 << (kk - 2*REGISTER_SIZE) );
	}

	
}

//printf("PE0r10= %x, PE0r11= %x, PE0r12= %x \n",PE0r10, PE0r11, PE0r12);
//printf("PE1r10= %x, PE1r11= %x, PE1r12= %x \n",PE1r10, PE1r11, PE1r12);
//printf("PE2r10= %x, PE2r11= %x, PE2r12= %x  \n",PE2r10, PE2r11, PE2r12);
//printf("PE3r10= %x, PE3r11= %x, PE3r12= %x  \n",PE3r10, PE3r11, PE3r12);

//if ( (outputFile=fopen("output_bits_intrlvr.s","w"))==NULL)
//{puts("error creating 'output_bits_intrlvr.s'");exit(1);}

//fprintf(outputFile, ".word 0x%x\n.word 0x%x\n.word 0x%x\n",PE0r10, PE0r11, PE0r12);
//fprintf(outputFile, ".word 0x%x\n.word 0x%x\n.word 0x%x\n",PE1r10, PE1r11, PE1r12);
//fprintf(outputFile, ".word 0x%x\n.word 0x%x\n.word 0x%x\n",PE2r10, PE2r11, PE2r12);
//fprintf(outputFile, ".word 0x%x\n.word 0x%x\n.word 0x%x\n",PE3r10, PE3r11, PE3r12);


//_fcloseall();

// output of interleaver:

  outPE0[0] = PE0r10;
  outPE0[1] = PE0r11;
  outPE0[2] = PE0r12; 

  outPE1[0] = PE1r10;
  outPE1[1] = PE1r11;
  outPE1[2] = PE1r12; 

  outPE2[0] = PE2r10;
  outPE2[1] = PE2r11;
  outPE2[2] = PE2r12; 

  outPE3[0] = PE3r10;
  outPE3[1] = PE3r11;
  outPE3[2] = PE3r12; 

// For automated unit test: ...

// Distribute data to the PE data memories.
// call main asm program.
// get output (interleaved bits) from PE data memories.
// Compare

}

//-------------------------------------------------------------------------------------------
//|																							|
//|								FUNCTION DEFINITIONS										|
//|																							|
//-------------------------------------------------------------------------------------------

// Function Specification **********************************************
   //
   // Name: BinaryRandom
   //
   // Purpose: To generate binary random numbers
   //
   // Parms: none
   //
   // Returns: unsigned int - randomly selected binary (0 or 1) digit.
   //
   // End Function Specification ******************************************

   unsigned int BinaryRandom()
   {
      int x,y;

	   x = rand();
	   if (x > RAND_MAX/2)
		   y = 1;
	   else
		   y = 0;

      return y;
   }



