
# topology file:  Tx80211a.t

#--------------------------------------------------- 
# Title: 802.11a  
# Author: Sasan Ardalan 
# Date: September 19, 2001 
# Description: End to End 54 Mbps OFDM based on IEEE 802.11a 
#--------------------------------------------------- 

inform title 802.11a 
inform author Sasan Ardalan 
inform date September 19, 2001
inform descrip End to End 54 Mbps OFDM based on IEEE 802.11a

arg 0 int 30000 "Bits per Packet"

param arg 0    numPSDU   "Bits per Packet"
block dataField0 dataField

param file dataField.dat    file_name   "Name of output file"
param int 1    control   "Print output control (0/Off, 1/On)"
param int 2    bufferType   "Buffer type:0= Float,1= Complex, 2=Integer"
block prfile3 prfile

param int 216    N   " Number of bytes to input "
block scramble0 scramble

param int 7    NWORDS   " Number of words to input "
block convenca0 convenca

param int 34    codingRate   " codingRates are 12 23 34. "
param int 54    dataRate   " dataRate=54 "
block puncture0 puncture

block interlr0 interlr

block FQAM_64map0 FQAM_64map

param int 0    numOfBits   " number of input bits per packet "
block pilot0 pilot

param file tx_prefft.dat    file_name   "Name of output file"
param int 1    control   "Print output control (0/Off, 1/On)"
param int 1    bufferType   "Buffer type:0= Float,1= Complex, 2=Integer"
block prfile0 prfile

param int 16    cyclicSamples   "  Cyclic extension samples  "
param int 1    training   "  Include training 1=doit, 0 don't  "
param int 0    signalField   "  Include SIGNAL field 1=doit, 0 don't  "
param arg 0    length   "Bits per Packet"
param int 5    rate   "  data rate  "
param int 10000    numberOFDMSymbols   "  Number of packet.At 64QAM number of bits=numberOFDMSymbols*48*6  "
param int 200    padZeroes   "  Number of zereos to pad at end of packet "
block ifftofdm540 ifftofdm54

connect input 0 dataField0 0   	
connect dataField0 0 prfile3 0  	
connect prfile3 0 scramble0 0  	{prfile3:NULL:NULL,scramble0: x : int }
connect scramble0 0 convenca0 0  	{scramble0: y : int ,convenca0: x : int }
connect convenca0 0 puncture0 0  	{convenca0: achan : int ,puncture0: dataA : int }
connect convenca0 1 puncture0 1  	{convenca0: bchan : int ,puncture0: dataB : int }
connect puncture0 0 interlr0 0  	{puncture0: BitStolen : int ,interlr0: x : int }
connect interlr0 0 FQAM_64map0 0  	{interlr0: y : int ,FQAM_64map0: x : int }
connect FQAM_64map0 0 pilot0 0  	{FQAM_64map0: output : complex ,pilot0: x : complex }
connect pilot0 0 prfile0 0  	
connect prfile0 0 ifftofdm540 0  	{prfile0:NULL:NULL,ifftofdm540: x : complex }
connect ifftofdm540 0 output 0  	

