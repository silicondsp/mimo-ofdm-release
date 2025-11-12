
# topology file:  svd_fp_2x2_mimo.t

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
arg 1 float 1e-05 "Noise Power"

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
hblock intlvrMapperPilots1 intlvrMapperPilots.t

param arg 0    (null)   "Bits per packet"
hblock intlvrMapperPilots0 intlvrMapperPilots.t

param int 16    cyclicSamples   "  Cyclic extension samples  "
param int 0    training   "  Include training 1=doit, 0 don't  "
param int 0    signalField   "  Include SIGNAL field 1=doit, 0 don't  "
param arg 0    length   "Bits per packet"
param int 5    rate   "  data rate  "
param int 1000000    numberOFDMSymbols   "  Number of packet.At 64QAM number of bits=numberOFDMSymbols*48*6  "
param int 0    padZeroes   "  Number of zereos to pad at end of packet "
block ifftofdmsvd0 ifftofdmsvd

param float 20    sampRateMHz   "Sampling Rate (MHz)"
param float 50    delaySprdNsec   "Delay Spread (ns)"
param int 725443    seedParam   "Seed"
block cxmimoch0 cxmimoch

param arg 1    power   "Noise Power"
param int 333    seed   "Seed for random number generator"
block cxaddnoise0 cxaddnoise

param int 80    symbolLength   "Symbol  Length "
param int 16    cycPrefixLength   "Cyclic Prefix  Length "
block rmcpfx0 rmcpfx

param int 64    fftLength   " FFT Length "
block fwfft0 fwfft

param arg 1    power   "Noise Power"
param int 23965    seed   "Seed for random number generator"
block cxaddnoise1 cxaddnoise

param int 80    symbolLength   "Symbol  Length "
param int 16    cycPrefixLength   "Cyclic Prefix  Length "
block rmcpfx1 rmcpfx

param int 64    fftLength   " FFT Length "
block fwfft1 fwfft

param int 2    numberTxAntennas   "Number of Transmit Antennas"
param int 64    lengthFFT   "FFT Length"
param file cxmimoch0.taps    HMatrixFileName   "File Name with Channel H Matrix"
block cxmimo_2x2_svd_fp0 cxmimo_2x2_svd_fp

param int 1    printControl   " Print Control (0=off, 1=on) "
block prcxmat0 prcxmat

param int 128    npts   "Number of points ( dynamic plot window)"
param int 0    skip   "Number of points to skip"
param file Scatter    title   "Title"
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
param file Scatter    title   "Title"
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

connect bdata0 0 Encoder0 0  	
connect Encoder0 0 demux0 0  	{Encoder0:NULL:NULL,demux0:x:float}
connect demux0 0 intlvrMapperPilots0 0  	
connect demux0 1 intlvrMapperPilots1 0  	
connect intlvrMapperPilots1 0 ifftofdmsvd0 2  	
connect intlvrMapperPilots0 0 ifftofdmsvd0 1  	
connect ifftofdmsvd0 0 cxmimoch0 0  	
connect ifftofdmsvd0 1 cxmimoch0 1  	
connect cxmimoch0 0 cxaddnoise0 0  	{cxmimoch0:NULL:NULL,cxaddnoise0:inp:complex}
connect cxmimoch0 1 cxaddnoise1 0  	{cxmimoch0:NULL:NULL,cxaddnoise1:inp:complex}
connect cxaddnoise0 0 rmcpfx0 0  	{cxaddnoise0:out:complex,rmcpfx0: X : complex }
connect rmcpfx0 0 fwfft0 0  	{rmcpfx0: y : complex ,fwfft0: X : complex }
connect fwfft0 0 cxmimo_2x2_svd_fp0 0  	
connect cxaddnoise1 0 rmcpfx1 0  	{cxaddnoise1:out:complex,rmcpfx1: X : complex }
connect rmcpfx1 0 fwfft1 0  	{rmcpfx1: y : complex ,fwfft1: X : complex }
connect fwfft1 0 cxmimo_2x2_svd_fp0 1  	
connect cxmimo_2x2_svd_fp0 0 prcxmat0 0  	
connect cxmimo_2x2_svd_fp0 1 scatter0 0  	
connect cxmimo_2x2_svd_fp0 2 scatter1 0  	
connect prcxmat0 0 ifftofdmsvd0 0  	

