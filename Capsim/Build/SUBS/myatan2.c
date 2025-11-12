
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
	floating-point arctangent

	atan returns the value of the arctangent of its
	argument in the range [-pi/2,pi/2].

	atan2 returns the arctangent of arg1/arg2
	in the range [-pi,pi].

	there are no error returns.

	coefficients are #5077 from Hart & Cheney. (19.56D)
*/


double static sq2p1	 =2.414213562373095048802e0;
static double sq2m1	 = .414213562373095048802e0;
static double pio2	 =1.570796326794896619231e0;
static double pio4	 = .785398163397448309615e0;
static double p4	 = .161536412982230228262e2;
static double p3	 = .26842548195503973794141e3;
static double p2	 = .11530293515404850115428136e4;
static double p1	 = .178040631643319697105464587e4;
static double p0	 = .89678597403663861959987488e3;
static double q4	 = .5895697050844462222791e2;
static double q3	 = .536265374031215315104235e3;
static double q2	 = .16667838148816337184521798e4;
static double q1	 = .207933497444540981287275926e4;
static double q0	 = .89678597403663861962481162e3;

static double satan(double arg);
static double xatan(double arg);

/*
	atan makes its argument positive and
	calls the inner routine satan.
*/

double myatan(double arg)

{

	if(arg>0)
		return(satan(arg));
	else
		return(-satan(-arg));
}


/*
	atan2 discovers what quadrant the angle
	is in and calls atan.
*/

double myatan2(double arg1,double arg2)

{

	if((arg1+arg2)==arg1)
		if(arg1 >= 0.) return(pio2);
		else return(-pio2);
	else if(arg2 <0.)
		if(arg1 >= 0.)
			return(pio2+pio2 - satan(-arg1/arg2));
		else
			return(-pio2-pio2 + satan(arg1/arg2));
	else if(arg1>0)
		return(satan(arg1/arg2));
	else
		return(-satan(-arg1/arg2));
}

/*
	satan reduces its argument (known to be positive)
	to the range [0,0.414...] and calls xatan.
*/

static double satan(double arg)

{

	if(arg < sq2m1)
		return(xatan(arg));
	else if(arg > sq2p1)
		return(pio2 - xatan(1.0/arg));
	else
		return(pio4 + xatan((arg-1.0)/(arg+1.0)));
}

/*
	xatan evaluates a series valid in the
	range [-0.414...,+0.414...].
*/

static double xatan(double arg)

{
	double argsq;
	double value;

	argsq = arg*arg;
	value = ((((p4*argsq + p3)*argsq + p2)*argsq + p1)*argsq + p0);
	value = value/(((((argsq + q4)*argsq + q3)*argsq + q2)*argsq + q1)*argsq + q0);
	return(value*arg);
}










