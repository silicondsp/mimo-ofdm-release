
# topology file:  cxdecim.t

#--------------------------------------------------- 
# Title: PER  
# Author: Aziz-Casey 
# Date: July 31, 2003 
# Description: PER IEEE 802.11a 2.5e-005 
#--------------------------------------------------- 

inform title cxdecim 
inform author Sasan
inform date Feb 1, 2004
inform descrip Complex Interpolation

arg 0 int 2 "Input to output ratio" 


block cxreim0 cxreim

param arg 0 
param array 1  0
block demux0 demux

param arg 0 
param array 1  0
block demux1 demux

block cxmakecx0 cxmakecx

connect input 0 cxreim0 0  
connect cxreim0 0 demux0 0
connect cxreim0 1 demux1 0 	
connect demux0 0 cxmakecx0 0  	
connect demux1 0 cxmakecx0 1  	
connect cxmakecx0 0 output 0  	


