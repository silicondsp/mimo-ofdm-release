
# topology file:  intlvrMapperPilots.t

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

block interlr0 interlr

block FQAM_64map0 FQAM_64map

param int 0    numOfBits   " number of input bits per packet "
block pilot0 pilot

connect input 0 interlr0 0   	
connect interlr0 0 FQAM_64map0 0  	{interlr0: y : int ,FQAM_64map0: x : int }
connect FQAM_64map0 0 pilot0 0  	{FQAM_64map0: output : complex ,pilot0: x : complex }
connect pilot0 0 output 0  	

