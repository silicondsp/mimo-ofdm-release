# Graphics info for galaxy MIMO_2x2

zoomFactor: 1.000000 
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


gblock impulse1
	xLoc: 22  	yLoc: 263
	xDel: 35  	yDel: 15


gblock gain0
	xLoc: 91  	yLoc: 261
	xDel: 35  	yDel: 15


gblock cxmakecx1
	xLoc: 197  	yLoc: 257
	xDel: 110  	yDel: 30


gblock cxmimoch0
	xLoc: 344  	yLoc: 145
	xDel: 110  	yDel: 30


gblock cxplot0
	xLoc: 496  	yLoc: 146
	xDel: 90  	yDel: 30


gblock cxplot1
	xLoc: 494  	yLoc: 224
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
	246  	144
	274  	144
	274  	126
	289  	126


gconnect impulse1 0  gain0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	40  	263
	49  	263
	49  	263
	59  	263
	59  	261
	74  	261


gconnect gain0 0  cxmakecx1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	109  	261
	118  	261
	118  	261
	127  	261
	127  	257
	142  	257


gconnect cxmakecx1 0  cxmimoch0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	252  	257
	261  	257
	261  	257
	270  	257
	270  	153
	289  	153


gconnect cxmimoch0 0  cxplot0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	399  	126
	408  	126
	408  	146
	436  	146
	436  	146
	451  	146


gconnect cxmimoch0 1  cxplot1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	399  	154
	413  	154
	413  	224
	434  	224
	434  	224
	449  	224


