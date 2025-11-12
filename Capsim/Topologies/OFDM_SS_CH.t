
# topology file:  OFDM_SS_CH.t

#--------------------------------------------------- 
# Title: 802.11a  
# Author: Sasan Ardalan 
# Date: September 19, 2001 
# Description: End to End 54 Mbps OFDM based on IEEE 802.11a 
#--------------------------------------------------- 

inform title 802.11a 
inform author  Sasan Ardalan
inform date September 19, 2001
inform descrip End to End 54 Mbps OFDM based on IEEE 802.11a

arg 0 int 8000 "Number of bits"
arg 1 int 8018 "Viterni Frame Size"

param arg 0    num_of_samples   "Number of bits"
param int 7    initialize   "Initialization for shift register"
param float 1    pace_rate   "pace rate to determine how many samples to output"
param int 128    samples_first_time   "number of samples on the first call if paced"
block bdata0 bdata

param arg 0    (null)   "Number of bits"
hblock Tx80211a0 Tx80211a.t

param float 50    (null)   "Delay Spread (ns)"
param int 1487230    (null)   "Channel Seed SISO"
hblock chm_800 chm_80.t

param float 1    factorReal   "Gain factor real part"
param float 0    factorImag   "Gain factor imaginary part"
block cxgain0 cxgain

param float 0    offset   " Carrier offset "
param float 2e+07    fs   " Sampling Rate "
block carroffset0 carroffset

param float 100    snr   "SNR, dB"
param int 160    preambleSize   "Preamble Size"
param int 100    windowSize   "Window Size"
param float 1e-06    silenceThreshold   "Silence Threshold"
param int 544377    seed   "Seed for random number generator"
param int 0    verbose   "Verbose"
block cxsetsnr0 cxsetsnr

param float 0.08    targetRMS   " Target rms "
param int 0    skip   " Points to skip "
param int 32    agcWindowSize   " Window size "
block cxagc0 cxagc

block cxnode0 cxnode

block cxmag1 cxmag

param int 128    npts   "Number of points in each plot (dynamic window size)"
param int 0    skip   "Points to skip before first plot"
param file PacketMag    title   "Plot title"
param file Samples    x_axis   "X Axis label"
param file Y    y_axis   "Y-Axis label"
param int 1    plotStyleParam   "Plot Style: 1=Line,2=Points,5=Bar Chart"
param int 1    control   "Control: 1=On, 0=Off"
param int 0    mode   "0=Static,1=Dynamic"
param int 1    samplingRate   "Sampling Rate"
block prbplot140 plot

param int 193    skipCount   " Samples to Skip "
block synchlong0 synchlong

block cxnode1 cxnode

param int 80    symbolLength   "Symbol  Length "
param int 16    cycPrefixLength   "Cyclic Prefix  Length "
block rmcpfx0 rmcpfx

param int 64    fftLength   " FFT Length "
block fwfft0 fwfft

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

block cxmag3 cxmag

param int 128    npts   "Number of points in each plot (dynamic window size)"
param int 0    skip   "Points to skip before first plot"
param file plot    title   "Plot title"
param file Samples    x_axis   "X Axis label"
param file Y    y_axis   "Y-Axis label"
param int 1    plotStyleParam   "Plot Style: 1=Line,2=Points,5=Bar Chart"
param int 0    control   "Control: 1=On, 0=Off"
param int 0    mode   "0=Static,1=Dynamic"
param int 1    samplingRate   "Sampling Rate"
block prbplot040 plot

block cxnode4 cxnode

param int 64    numberOfCarriers   " Number of Carriers "
block cxavgchannel0 cxavgchannel

block cxnode2 cxnode

param int 64    fftLength   " FFT Length "
block fwfft1 fwfft

block cxmag2 cxmag

param int 128    npts   "Number of points in each plot (dynamic window size)"
param int 0    skip   "Points to skip before first plot"
param file Long    title   "Plot title"
param file Samples    x_axis   "X Axis label"
param file Y    y_axis   "Y-Axis label"
param int 1    plotStyleParam   "Plot Style: 1=Line,2=Points,5=Bar Chart"
param int 1    control   "Control: 1=On, 0=Off"
param int 0    mode   "0=Static,1=Dynamic"
param int 1    samplingRate   "Sampling Rate"
block prbplot2 plot

block cxmag4 cxmag

param int 128    npts   "Number of points in each plot (dynamic window size)"
param int 0    skip   "Points to skip before first plot"
param file plot    title   "Plot title"
param file Samples    x_axis   "X Axis label"
param file Y    y_axis   "Y-Axis label"
param int 1    plotStyleParam   "Plot Style: 1=Line,2=Points,5=Bar Chart"
param int 0    control   "Control: 1=On, 0=Off"
param int 0    mode   "0=Static,1=Dynamic"
param int 1    samplingRate   "Sampling Rate"
block prbplot0821 plot

param file channelest_ss_fwfft.dat    file_name   "Name of output file"
param int 1    control   "Print output control (0/Off, 1/On)"
param int 1    bufferType   "Buffer type:0= Float,1= Complex, 2=Integer"
block prfile3 prfile

block cxnode3 cxnode

block cxmag0 cxmag

param int 128    npts   "Number of points in each plot (dynamic window size)"
param int 0    skip   "Points to skip before first plot"
param file Mag    title   "Plot title"
param file Samples    x_axis   "X Axis label"
param file Y    y_axis   "Y-Axis label"
param int 1    plotStyleParam   "Plot Style: 1=Line,2=Points,5=Bar Chart"
param int 1    control   "Control: 1=On, 0=Off"
param int 0    mode   "0=Static,1=Dynamic"
param int 1    samplingRate   "Sampling Rate"
block prbplot1 plot

param int 64    numberOfCarriers   " Number of Carriers "
param int 1    doEqualization   " Do Equalization (1:yes 0:no) "
block cxequalizezf0 cxequalizezf

param int 128    npts   "Number of points ( dynamic plot window)"
param int 0    skip   "Number of points to skip"
param file Equalized    title   "Title"
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

param file zz    file_name   "Name of output file"
param int 1    control   "Print output control (0/Off, 1/On)"
param int 1    bufferType   "Buffer type:0= Float,1= Complex, 2=Integer"
block prbprfile0 prfile

connect bdata0 0 Tx80211a0 0  	
connect Tx80211a0 0 chm_800 0  	
connect chm_800 0 cxgain0 0  	{chm_800:NULL:NULL,cxgain0:x:complex}
connect cxgain0 0 carroffset0 0  	{cxgain0:NULL:NULL,carroffset0: x : complex }
connect carroffset0 0 cxsetsnr0 0  	{carroffset0:NULL:NULL,cxsetsnr0:inp:complex}
connect cxsetsnr0 0 cxagc0 0  	{cxsetsnr0:out:complex,cxagc0: x : complex }
connect cxagc0 0 cxnode0 0  	{cxagc0: y : complex ,cxnode0:x:complex}
connect cxnode0 0 synchlong0 0  	{cxnode0:NULL:NULL,synchlong0: x : complex }
connect cxnode0 1 cxmag1 0  	{cxnode0:NULL:NULL,cxmag1:x:complex}
connect cxmag1 0 prbplot140 0  	
connect synchlong0 0 cxnode1 0  	{synchlong0: ofdmsym : complex ,cxnode1:x:complex}
connect synchlong0 1 cxnode4 0  	{synchlong0: longsym : complex ,cxnode4:x:complex}
connect cxnode1 0 rmcpfx0 0  	{cxnode1:NULL:NULL,rmcpfx0: X : complex }
connect cxnode1 1 cxmag3 0  	{cxnode1:NULL:NULL,cxmag3:x:complex}
connect rmcpfx0 0 fwfft0 0  	{rmcpfx0: y : complex ,fwfft0: X : complex }
connect fwfft0 0 scatter0 0  	
connect scatter0 0 cxequalizezf0 1  	{scatter0:NULL:NULL,cxequalizezf0: symbols : complex }
connect cxmag3 0 prbplot040 0  	
connect cxnode4 0 cxavgchannel0 0  	{cxnode4:NULL:NULL,cxavgchannel0: x : complex }
connect cxnode4 1 cxmag4 0  	{cxnode4:NULL:NULL,cxmag4:x:complex}
connect cxavgchannel0 0 cxnode2 0  	{cxavgchannel0: y : complex ,cxnode2:x:complex}
connect cxnode2 0 fwfft1 0  	{cxnode2:NULL:NULL,fwfft1: X : complex }
connect cxnode2 1 cxmag2 0  	{cxnode2:NULL:NULL,cxmag2:x:complex}
connect fwfft1 0 prfile3 0  	
connect cxmag2 0 prbplot2 0  	
connect cxmag4 0 prbplot0821 0  	
connect prfile3 0 cxnode3 0  	{prfile3:NULL:NULL,cxnode3:x:complex}
connect cxnode3 0 cxmag0 0  	{cxnode3:NULL:NULL,cxmag0:x:complex}
connect cxnode3 1 cxequalizezf0 0  	{cxnode3:NULL:NULL,cxequalizezf0: channEstimates : complex }
connect cxmag0 0 prbplot1 0  	
connect cxequalizezf0 0 scatter1 0  	
connect scatter1 0 prbprfile0 0  	

