
# topology file:  siso_eq.t

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

param arg 0    (null)   "Bits per packet"
hblock intlvrMapperiFFT0 intlvrMapperiFFT.t

param float 1    factorReal   "Gain factor real part"
param float 0    factorImag   "Gain factor imaginary part"
block cxgain1 cxgain

param float 20    sampRateMHz   "Sampling Rate (MHz)"
param float 50    delaySprdNsec   "Delay Spread (ns)"
param int 725443    seedParam   "Seed"
block cxmimoch0 cxmimoch

param float 1e-05    power   "Noise power"
param int 333    seed   "Seed for random number generator"
block cxaddnoise0 cxaddnoise

param int 80    symbolLength   "Symbol  Length "
param int 16    cycPrefixLength   "Cyclic Prefix  Length "
block rmcpfx0 rmcpfx

param int 64    fftLength   " FFT Length "
block fwfft0 fwfft

param int 128    npts   "Number of points ( dynamic plot window)"
param int 0    skip   "Number of points to skip"
param file ScatterPriorEq    title   "Title"
param file X    x_axis   "x Axis"
param file Y    y_axis   "y Axis"
param int 2    plotStyleParam   "Plot Style: 1=Line,2=Points,5=Bar Chart"
param int 0    fixed   "Fixed Bounds ( 0=none, 1=fixed)"
param float -1.2    minx   "Minimum x"
param float 1.2    maxx   "Maximum x"
param float -1.2    miny   "Minimum y"
param float 1.2    maxy   "Maximum y"
param int 0    markerType   "Marker type:0=dot,1=O,2=+,3=X,4=*,5=square,6=diamond,7=triangle"
param int 1    control   "Control: 1=On, 0=Off"
param int 1    bufferType   "Buffer type:0= Float,1= Complex, 2=Integer"
param int 0    mode   "0=Static,1=Dynamic"
block scatter1 scattertxt

param int 1    numberTxAntennas   "Number of Transmit Antennas"
param int 64    lengthFFT   "FFT Length"
param file cxmimoch0.taps    HMatrixFileName   "File Name with Channel H Matrix"
block cxmimoeqzf0 cxmimoeqzf

param int 128    npts   "Number of points ( dynamic plot window)"
param int 0    skip   "Number of points to skip"
param file Scatter0    title   "Title"
param file X    x_axis   "x Axis"
param file Y    y_axis   "y Axis"
param int 2    plotStyleParam   "Plot Style: 1=Line,2=Points,5=Bar Chart"
param int 0    fixed   "Fixed Bounds ( 0=none, 1=fixed)"
param float -1.2    minx   "Minimum x"
param float 1.2    maxx   "Maximum x"
param float -1.2    miny   "Minimum y"
param float 1.2    maxy   "Maximum y"
param int 0    markerType   "Marker type:0=dot,1=O,2=+,3=X,4=*,5=square,6=diamond,7=triangle"
param int 1    control   "Control: 1=On, 0=Off"
param int 1    bufferType   "Buffer type:0= Float,1= Complex, 2=Integer"
param int 0    mode   "0=Static,1=Dynamic"
block scatter0 scattertxt

connect bdata0 0 Encoder0 0  	
connect Encoder0 0 intlvrMapperiFFT0 0  	
connect intlvrMapperiFFT0 0 cxgain1 0  	{intlvrMapperiFFT0:NULL:NULL,cxgain1:x:complex}
connect cxgain1 0 cxmimoch0 0  	
connect cxmimoch0 0 cxaddnoise0 0  	{cxmimoch0:NULL:NULL,cxaddnoise0:inp:complex}
connect cxaddnoise0 0 rmcpfx0 0  	{cxaddnoise0:out:complex,rmcpfx0: X : complex }
connect rmcpfx0 0 fwfft0 0  	{rmcpfx0: y : complex ,fwfft0: X : complex }
connect fwfft0 0 scatter1 0  	
connect scatter1 0 cxmimoeqzf0 0  	
connect cxmimoeqzf0 0 scatter0 0  	

