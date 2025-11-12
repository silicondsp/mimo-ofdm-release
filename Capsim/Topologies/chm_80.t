
# topology file:  chm_80.t

#--------------------------------------------------- 
# Title: chm_80.t 
# Author: Orhan Can Ozdural 
# Date: 08/11/2004 
# Description: SISO channel  
#--------------------------------------------------- 

inform title chm_80.t
inform author Orhan Can Ozdural
inform date 08/11/2004
inform descrip SISO channel 

arg 0 float 50 "Delay Spread (ns)"
arg 1 int 1487230 "Channel Seed SISO"

param float 4    (null)   "Over Sample Ratio"
param int 3    (null)   "Type"
hblock cxrsmpl0 cxrsmpl.t

param float 80    sampRateMHz   "Sampling Rate (MHz)"
param  arg 0 
param arg 1    seedParam   "Channel Seed SISO"
block cxchmodel0 cxchmodel

param int 4    (null)   "Input to output ratio"
hblock cxdecim0 cxdecim.t

connect input 0 cxrsmpl0 0   	
connect cxrsmpl0 0 cxchmodel0 0  	{cxrsmpl0:NULL:NULL,cxchmodel0:x:complex}
connect cxchmodel0 0 cxdecim0 0  	
connect cxdecim0 0 output 0  	

