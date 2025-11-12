
# topology file:  cxrsmpl.t

#--------------------------------------------------- 
# Title: cxrsmpl 
# Author: Sasan 
# Date: Feb 1, 2004 
# Description: Complex Interpolation 
#--------------------------------------------------- 

inform title cxrsmpl
inform author Sasan
inform date Feb 1, 2004
inform descrip Complex Interpolation

arg 0 float 2 "Over Sample Ratio"
arg 1 int 2 "Type"

block cxreim0 cxreim

block cxmakecx0 cxmakecx

param arg 0
param float 0
param arg 1
block resmpl0 resmpl

param arg 0
param float 0
param arg 1
block resmpl1 resmpl

connect input 0 cxreim0 0   	
connect cxreim0 0 resmpl0 0  	
connect cxreim0 1 resmpl1 0  	
connect cxmakecx0 0 output 0  	
connect resmpl0 0 cxmakecx0 0  	
connect resmpl1 0 cxmakecx0 1  	


