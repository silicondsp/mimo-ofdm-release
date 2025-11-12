
# topology file:  MIMOTx.t

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

arg 0 int 4000 "Bits per packet"

param int 8000    num_of_samples   "total number of samples to output"
param int 7    initialize   "Initialization for shift register"
param float 1    pace_rate   "pace rate to determine how many samples to output"
param int 128    samples_first_time   "number of samples on the first call if paced"
block bdata0 bdata

param arg 0    (null)   "Bits per packet"
hblock Encoder0 Encoder.t

param int 2    N   "Ratio input rate/output rate,N"
param array 2  0  1    phases   "Array: Specifies the phase (delay in samples relative to first input sample) for each output."
block demux0 demux

param arg 0    (null)   "Bits per packet"
hblock intlvrMapperiFFT0 intlvrMapperiFFT.t

param int 30000    (null)   "Bits per Packet"
hblock intlvrMapperiFFT1 intlvrMapperiFFT.t

param float 200    sampRateMHz   "Sampling Rate (MHz)"
param float 50    delaySprdNsec   "Delay Spread (ns)"
param int 725443    seedParam   "Seed"
block cxmimoch0 cxmimoch

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

block cxreim1 cxreim

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
block prbspectrum0840 spectrum

block sink1 sink

connect bdata0 0 Encoder0 0  	
connect Encoder0 0 demux0 0  	{Encoder0:NULL:NULL,demux0:x:float}
connect demux0 0 intlvrMapperiFFT0 0  	
connect demux0 1 intlvrMapperiFFT1 0  	
connect intlvrMapperiFFT0 0 cxmimoch0 0  	
connect intlvrMapperiFFT1 0 cxmimoch0 1  	
connect cxmimoch0 0 cxreim0 0  	{cxmimoch0:NULL:NULL,cxreim0:x:complex}
connect cxmimoch0 1 cxreim1 0  	{cxmimoch0:NULL:NULL,cxreim1:x:complex}
connect cxreim0 0 prbspectrum0394 0  	
connect cxreim0 1 sink0 0  	
connect cxreim1 0 prbspectrum0840 0  	
connect cxreim1 1 sink1 0  	

