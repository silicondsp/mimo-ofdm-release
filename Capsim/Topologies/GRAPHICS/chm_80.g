# Graphics info for galaxy chm_80

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 658
Scroll Window Height: 125


gblock cxrsmpl0
	xLoc: 176  	yLoc: 39
	xDel: 100  	yDel: 30


gblock cxchmodel0
	xLoc: 334  	yLoc: 43
	xDel: 110  	yDel: 30


gblock cxdecim0
	xLoc: 491  	yLoc: 47
	xDel: 100  	yDel: 30


gconnect input 0  cxrsmpl0 0
	termType: -1  	probeType: 0 	pacerFlag: 0 	autoConnect: 0
	pathPts(x,y): 6
	26  	39
	31  	39
	31  	39
	111  	39
	111  	39
	126  	39


gconnect cxrsmpl0 0  cxchmodel0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0
	pathPts(x,y): 6
	226  	39
	235  	39
	235  	43
	264  	43
	264  	43
	279  	43


gconnect cxchmodel0 0  cxdecim0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0
	pathPts(x,y): 6
	389  	43
	398  	43
	398  	47
	426  	47
	426  	47
	441  	47


gconnect cxdecim0 0  output 0
	termType: 1  	probeType: 0 	pacerFlag: 0	autoConnect: 0
	pathPts(x,y): 6
	541  	47
	550  	47
	550  	47
	566  	47
	566  	47
	581  	47


