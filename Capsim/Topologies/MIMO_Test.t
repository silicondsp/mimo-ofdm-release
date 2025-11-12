
# topology file:  MIMO_Test.t

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

param float 1    factorReal   "Gain factor real part"
param float 0    factorImag   "Gain factor imaginary part"
block cxgain0 cxgain

param float 1    factorReal   "Gain factor real part"
param float 0    factorImag   "Gain factor imaginary part"
block cxgain1 cxgain

param float 20    sampRateMHz   "Sampling Rate (MHz)"
param float 5    delaySprdNsec   "Delay Spread (ns)"
param int 725443    seedParam   "Seed"
block cxmimoch0 cxmimoch

param int 80    symbolLength   "Symbol  Length "
param int 16    cycPrefixLength   "Cyclic Prefix  Length "
block rmcpfx0 rmcpfx

param int 80    symbolLength   "Symbol  Length "
param int 16    cycPrefixLength   "Cyclic Prefix  Length "
block rmcpfx1 rmcpfx

param int 64    fftLength   " FFT Length "
block fwfft0 fwfft

param int 64    fftLength   " FFT Length "
block fwfft1 fwfft

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

param int 128    npts   "Number of points ( dynamic plot window)"
param int 0    skip   "Number of points to skip"
param file Scatter2    title   "Title"
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

param int 80    symbolLength   "Symbol  Length "
param int 16    cycPrefixLength   "Cyclic Prefix  Length "
block rmcpfx2 rmcpfx

param int 64    fftLength   " FFT Length "
block fwfft2 fwfft

param int 128    npts   "Number of points ( dynamic plot window)"
param int 0    skip   "Number of points to skip"
param file Scatter1    title   "Title"
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
block scatter2 scattertxt

connect bdata0 0 Encoder0 0  	
connect Encoder0 0 demux0 0  	{Encoder0:NULL:NULL,demux0:x:float}
connect demux0 0 intlvrMapperiFFT0 0  	
connect demux0 1 intlvrMapperiFFT1 0  	
connect intlvrMapperiFFT0 0 cxgain1 0  	{intlvrMapperiFFT0:NULL:NULL,cxgain1:x:complex}
connect intlvrMapperiFFT1 0 cxgain0 0  	{intlvrMapperiFFT1:NULL:NULL,cxgain0:x:complex}
connect cxgain0 0 cxmimoch0 1  	
connect cxgain1 0 cxmimoch0 0  	
connect cxmimoch0 0 rmcpfx0 0  	{cxmimoch0:NULL:NULL,rmcpfx0: X : complex }
connect cxmimoch0 1 rmcpfx1 0  	{cxmimoch0:NULL:NULL,rmcpfx1: X : complex }
connect cxmimoch0 2 rmcpfx2 0  	{cxmimoch0:NULL:NULL,rmcpfx2: X : complex }
connect rmcpfx0 0 fwfft0 0  	{rmcpfx0: y : complex ,fwfft0: X : complex }
connect rmcpfx1 0 fwfft1 0  	{rmcpfx1: y : complex ,fwfft1: X : complex }
connect fwfft0 0 scatter0 0  	
connect fwfft1 0 scatter1 0  	
connect rmcpfx2 0 fwfft2 0  	{rmcpfx2: y : complex ,fwfft2: X : complex }
connect fwfft2 0 scatter2 0  	

