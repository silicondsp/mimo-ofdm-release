

/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 1989-2017   Silicon DSP  Corporation

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




/*                   myfmod.c compute remainder of x/y.

                     This algorithm is simplified and only used for 802.11a
                     PHY floating point operation.

         Algorithm:

                    The fmod() function compute the floating-point remainder of x / y, even 
                    if the quotient x / y isn't representable.

                     Retrurns:   x-i*y, in is some interger.

                     For an integer i such that: 

                     If y is:                               fmod() returns: 

                        0                                          0 
                        !0                                  The same sign as x, 
                                                            and a magnitude less 
                                                            than the magnitude of y. 


     Author:         Bin Huang
     Date:           10/20/02  

*/




float myfmod(float x,float y)

{

	int i;
	int DoneSign;             //    DoneSign=0 means x>=0, DoneSign=1 ==> x<0

	DoneSign = 0;
	if(x<0.0)
	{
		x= -x;
		DoneSign=1;
	}
	
	if (y==0.0)
		return 0;
	if(y<0.0)
		y=-y;


   i=0;
   while ((x-i*y)>=0.0)
   {
	   i++;
   }

   if(DoneSign ==0)
   {
	   return x-(i-1)*y;
   }
   else {
	   return -(x-(i-1)*y);
   }

}
