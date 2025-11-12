# Graphics info for galaxy MIMO_SISO

zoomFactor: 0.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 800
Scroll Window Height: 400


gblock impulse0
	xLoc: 30  	yLoc: 141
	xDel: 35  	yDel: 15


gblock cxmakecx0
	xLoc: 182  	yLoc: 144
	xDel: 110  	yDel: 30


gblock cxmimoch0
	xLoc: 344  	yLoc: 145
	xDel: 110  	yDel: 30


gblock cxplot0
	xLoc: 496  	yLoc: 146
	xDel: 90  	yDel: 30


gconnect impulse0 0  cxmakecx0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	48  	141
	57  	141
	57  	144
	112  	144
	112  	144
	127  	144


gconnect cxmakecx0 0  cxmimoch0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	237  	144
	246  	144
	246  	145
	274  	145
	274  	145
	289  	145


gconnect cxmimoch0 0  cxplot0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	399  	145
	408  	145
	408  	146
	436  	146
	436  	146
	451  	146


