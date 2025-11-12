# Graphics info for galaxy intlvrMapperiFFT

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 803
Scroll Window Height: 366


gblock interlr0
	xLoc: 198  	yLoc: 188
	xDel: 100  	yDel: 30


gblock FQAM_64map0
	xLoc: 350  	yLoc: 189
	xDel: 130  	yDel: 30


gblock pilot0
	xLoc: 488  	yLoc: 188
	xDel: 80  	yDel: 30


gblock ifftofdm540
	xLoc: 640  	yLoc: 189
	xDel: 130  	yDel: 30


gconnect input 0  interlr0 0
	termType: -1  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	48  	188
	53  	188
	53  	188
	133  	188
	133  	188
	148  	188


gconnect interlr0 0  FQAM_64map0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	248  	188
	257  	188
	257  	189
	270  	189
	270  	189
	285  	189


gconnect FQAM_64map0 0  pilot0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	415  	189
	424  	189
	424  	189
	433  	189
	433  	188
	448  	188


gconnect pilot0 0  ifftofdm540 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	528  	188
	537  	188
	537  	189
	560  	189
	560  	189
	575  	189


gconnect ifftofdm540 0  output 0
	termType: 1  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	705  	189
	714  	189
	714  	189
	715  	189
	715  	189
	730  	189


