

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

/*    802.11a OFDM Transceiver


      Author:                        Bin Huang
      date created                   8/16/01 

*/

extern  float BPSK_MAPTable[2][2];
extern  float QPSK_MAPTable[2][4];
extern  float QAM_16MAPTable[2][4];
extern  float QAM_64MAPTable[2][64];
extern  float Polarity_control[127];
extern  int Index_Reg54[288];
extern  int Index_shift54[288];
extern  int Index_Reg36[192];
extern  int Index_shift36[192];
extern  int Index_Reg18[96];
extern  int Index_shift18[96];
extern  int Index_Reg9[48];
extern  int Index_shift9[48];
extern  int Deintlr_indexTable[288];
extern  int rateTable[8];
extern  int interlrIndexTable[288];
extern  float shortTrain_TableRe[64];
extern  float shortTrain_TableIm[64];
extern  float longTrain_TableRe[64];
extern  float longTrain_TableIm[64];
extern  int pilotMapping[48];

