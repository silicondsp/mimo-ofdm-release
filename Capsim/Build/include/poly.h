

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


/* Modified by Ayman Elezabi on 10-1-01
  The 2 polynomials for the K=7 case have been inter-changed to be identical
  to the 80211a standard.

*/


/*
 * Polynominals for convolutional encoder
 */

    /* polynomials for K = 3 */
    static int g_3[2][3] = {{1, 1, 1},     /* 7 */
                   {1, 0, 1}};    /* 5 */

    /* polynomials for K = 5 */
    static int g_5[2][5] = {{1, 1,  1, 0, 1},  /* 35 */
                   {1, 0,  0, 1, 1}}; /* 23 */


    /* polynomials for K = 7 */
    static int g_7[2][7] = {{1,  0, 1, 1,  0, 1, 1},  /* 171 */
                   {1,  1, 1, 1,  0, 0, 1}}; /* 133 */


    /* polynomials for K = 9 */
    static int g_9[2][9] = {{1, 1, 1,  1, 0, 1,  0, 1, 1}, /* 753 */
                   {1, 0, 1,  1, 1, 0,  0, 0, 1}}; /* 561 */



