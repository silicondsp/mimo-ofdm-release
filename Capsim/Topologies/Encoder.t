
# topology file:  Encoder.t

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

connect input 0 dataField0 0   	
connect dataField0 0 prfile3 0  	
connect prfile3 0 scramble0 0  	{prfile3:NULL:NULL,scramble0: x : int }
connect scramble0 0 convenca0 0  	{scramble0: y : int ,convenca0: x : int }
connect convenca0 0 puncture0 0  	{convenca0: achan : int ,puncture0: dataA : int }
connect convenca0 1 puncture0 1  	{convenca0: bchan : int ,puncture0: dataB : int }
connect puncture0 0 output 0  	

