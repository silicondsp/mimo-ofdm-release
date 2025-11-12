
# topology file:  MIMO_2x1.t

#--------------------------------------------------- 
# Title: ------   
# Author: ------   
# Date: ------   
# Description: ------   
#--------------------------------------------------- 

inform title ------  
inform author Sasan Ardalan  
inform date 2006  
inform descrip ------  

arg -1 (none)

param int 128    length   "Enter number of samples"
block impulse0 impulse

block cxmakecx0 cxmakecx

param float 200    sampRateMHz   "Sampling Rate (MHz)"
param float 50    delaySprdNsec   "Delay Spread (ns)"
param int 725443    seedParam   "Seed"
block cxmimoch0 cxmimoch

param int 128    npts   "Number of points in each plot (dynamic window size)"
param int 0    skip   "Points to skip before first plot"
param file ComplexPlot    title   "Plot title"
param file Samples    x_axis   "X-Axis label"
param file Y    y_axis   "Y-Axis label"
param int 1    plotStyleParam   "Plot Style: 1=Color,2=Dashed,1=Same"
param int 0    plotType   "0=Real/Imaginary  1=Mag/Phase Plot"
param int 1    control   "Control: 1=On, 0=Off"
block cxplot0 cxplot

param int 128    length   "Enter number of samples"
block impulse1 impulse

param float 1    factor   "Gain factor"
block gain0 gain

block cxmakecx1 cxmakecx

connect impulse0 0 cxmakecx0 0  	
connect cxmakecx0 0 cxmimoch0 0  	
connect cxmimoch0 0 cxplot0 0  	
connect impulse1 0 gain0 0  	{impulse1:NULL:NULL,gain0:x:float}
connect gain0 0 cxmakecx1 0  	
connect cxmakecx1 0 cxmimoch0 1  	

