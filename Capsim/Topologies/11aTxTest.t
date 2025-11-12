
# topology file:  11aTxTest.t

#--------------------------------------------------- 
# Title: ------   
# Author: ------   
# Date: ------   
# Description: ------   
#--------------------------------------------------- 

inform title ------  
inform author Sasan Ardalan  
inform date 2002  
inform descrip ------  

arg 0 int 8000 "Bits per packet"

param int 8000    num_of_samples   "total number of samples to output"
param int 7    initialize   "Initialization for shift register"
param float 1    pace_rate   "pace rate to determine how many samples to output"
param int 128    samples_first_time   "number of samples on the first call if paced"
block bdata0 bdata

param arg 0    (null)   "Bits per packet"
hblock Encoder0 Encoder.t

param arg 0    (null)   "Bits per packet"
hblock intlvrMapperiFFT0 intlvrMapperiFFT.t

block cxreim0 cxreim

param int 128    npts   "Number of points ( dynamic window size )"
param int 0    skip   "Number of points to skip"
param file Spectrum    title   "Plot title"
param int 0    dbFlag   "Linear = 0, dB = 1"
param int 0    windFlag   "Window:0= Rec.,1=Hamm,2=Hann,3=Blackman"
param int 1    plotStyleParam   "Plot Style: 1=Line,2=Points,5=Bar Chart"
param int 1    timeFlag   "Time Domain On/Off (1/0)"
param float 0    sampFreq   "Sampling Rate (Bin Number if zero,Normalized if Negative"
param int 1    control   "Control: 1=On, 0=Off"
param int 0    bufferType   "Buffer type:0= Float,1= Complex, 2=Integer"
param int 0    mode   "0=Static,1=Dynamic"
param string "Frequency"    xLabelSpectrum   "Spectrum X Axis  Label "
param string "Time"    xLabelTime   "Time X Axis  Label "
block prbspectrum0394 spectrum

block sink0 sink

connect bdata0 0 Encoder0 0  	
connect Encoder0 0 intlvrMapperiFFT0 0  	
connect intlvrMapperiFFT0 0 cxreim0 0  	{intlvrMapperiFFT0:NULL:NULL,cxreim0:x:complex}
connect cxreim0 0 prbspectrum0394 0  	
connect cxreim0 1 sink0 0  	

