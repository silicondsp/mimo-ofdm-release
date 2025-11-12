

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


#define OUTCXMAT(BUFFER_NO,DELAY) \
         *(dsp_cxMatrix_t *)BufferAccess(star_P->outBuffer_P[BUFFER_NO],0,DELAY)

#define INCXMAT(BUFFER_NO,DELAY) \
         *(dsp_cxMatrix_t *)BufferAccess(star_P->inBuffer_P[BUFFER_NO],1,DELAY)

#define OUTDVEC(BUFFER_NO,DELAY) \
         *(doubleVector_t *)BufferAccess(star_P->outBuffer_P[BUFFER_NO],0,DELAY)

#define INCDVEC(BUFFER_NO,DELAY) \
         *(doubleVector_t *)BufferAccess(star_P->inBuffer_P[BUFFER_NO],1,DELAY)

