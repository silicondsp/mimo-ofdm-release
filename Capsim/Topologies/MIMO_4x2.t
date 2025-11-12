
# topology file:  MIMO_4x2.t

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

arg 0 float 200 "Sampling Rate MHz"

param int 128    length   "Enter number of samples"
block impulse0 impulse

param int 128    length   "Enter number of samples"
block impulse1 impulse

param float 1    factor   "Gain factor"
block gain0 gain

block cxmakecx1 cxmakecx

param float 1    factor   "Gain factor"
block gain1 gain

block cxmakecx0 cxmakecx

param int 128    length   "Enter number of samples"
block impulse2 impulse

param int 128    length   "Enter number of samples"
block impulse3 impulse

param float 1    factor   "Gain factor"
block gain2 gain

param float 1    factor   "Gain factor"
block gain3 gain

block cxmakecx2 cxmakecx

block cxmakecx3 cxmakecx

param arg 0    sampRateMHz   "Sampling Rate MHz"
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

param int 128    npts   "Number of points in each plot (dynamic window size)"
param int 0    skip   "Points to skip before first plot"
param file ComplexPlot    title   "Plot title"
param file Samples    x_axis   "X-Axis label"
param file Y    y_axis   "Y-Axis label"
param int 1    plotStyleParam   "Plot Style: 1=Color,2=Dashed,1=Same"
param int 0    plotType   "0=Real/Imaginary  1=Mag/Phase Plot"
param int 1    control   "Control: 1=On, 0=Off"
block cxplot1 cxplot

param int 128    npts   "Number of points ( dynamic window size )"
param int 0    skip   "Number of points to skip"
param file Spectrum    title   "Plot title"
param int 0    dbFlag   "Linear = 0, dB = 1"
param int 0    windFlag   "Window:0= Rec.,1=Hamm,2=Hann,3=Blackman"
param int 1    plotStyleParam   "Plot Style: 1=Line,2=Points,5=Bar Chart"
param int 1    timeFlag   "Time Domain On/Off (1/0)"
param arg 0    sampFreq   "Sampling Rate MHz"
param int 1    control   "Control: 1=On, 0=Off"
param int 1    bufferType   "Buffer type:0= Float,1= Complex, 2=Integer"
param int 0    mode   "0=Static,1=Dynamic"
param string "Frequency"    xLabelSpectrum   "Spectrum X Axis  Label "
param string "Time"    xLabelTime   "Time X Axis  Label "
block prbspectrum0840 spectrum

connect impulse0 0 gain1 0  	{impulse0:NULL:NULL,gain1:x:float}
connect impulse1 0 gain0 0  	{impulse1:NULL:NULL,gain0:x:float}
connect gain0 0 cxmakecx1 0  	
connect cxmakecx1 0 cxmimoch0 1  	
connect gain1 0 cxmakecx0 0  	
connect cxmakecx0 0 cxmimoch0 0  	
connect impulse2 0 gain2 0  	{impulse2:NULL:NULL,gain2:x:float}
connect impulse3 0 gain3 0  	{impulse3:NULL:NULL,gain3:x:float}
connect gain2 0 cxmakecx2 0  	
connect gain3 0 cxmakecx3 0  	
connect cxmakecx2 0 cxmimoch0 2  	
connect cxmakecx3 0 cxmimoch0 3  	
connect cxmimoch0 0 cxplot0 0  	
connect cxmimoch0 1 cxplot1 0  	
connect cxplot0 0 prbspectrum0840 0  	

