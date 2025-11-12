# Graphics info for galaxy MIMO_4x2

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 840
Scroll Window Height: 645


gblock impulse0
	xLoc: 30  	yLoc: 141
	xDel: 35  	yDel: 15


gblock impulse1
	xLoc: 22  	yLoc: 263
	xDel: 35  	yDel: 15


gblock gain0
	xLoc: 91  	yLoc: 261
	xDel: 35  	yDel: 15


gblock cxmakecx1
	xLoc: 197  	yLoc: 257
	xDel: 110  	yDel: 30


gblock gain1
	xLoc: 87  	yLoc: 142
	xDel: 35  	yDel: 15


gblock cxmakecx0
	xLoc: 182  	yLoc: 144
	xDel: 110  	yDel: 30


gblock impulse2
	xLoc: 25  	yLoc: 360
	xDel: 35  	yDel: 15


gblock impulse3
	xLoc: 30  	yLoc: 459
	xDel: 35  	yDel: 15


gblock gain2
	xLoc: 96  	yLoc: 359
	xDel: 35  	yDel: 15


gblock gain3
	xLoc: 109  	yLoc: 463
	xDel: 35  	yDel: 15


gblock cxmakecx2
	xLoc: 188  	yLoc: 362
	xDel: 110  	yDel: 30


gblock cxmakecx3
	xLoc: 195  	yLoc: 460
	xDel: 110  	yDel: 30


gblock cxmimoch0
	xLoc: 344  	yLoc: 145
	xDel: 110  	yDel: 30


gblock cxplot0
	xLoc: 494  	yLoc: 72
	xDel: 90  	yDel: 30


gblock cxplot1
	xLoc: 496  	yLoc: 145
	xDel: 90  	yDel: 30


gblock prbspectrum0840
	xLoc: 659  	yLoc: 74
	xDel: 70  	yDel: 30


gconnect impulse0 0  gain1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	48  	141
	57  	141
	57  	142
	55  	142
	55  	142
	70  	142


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
	270  	131
	289  	131


gconnect gain1 0  cxmakecx0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	105  	142
	114  	142
	114  	144
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
	274  	106
	289  	106


gconnect impulse2 0  gain2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	43  	360
	52  	360
	52  	360
	64  	360
	64  	359
	79  	359


gconnect impulse3 0  gain3 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	48  	459
	57  	459
	57  	463
	77  	463
	77  	463
	92  	463


gconnect gain2 0  cxmakecx2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	114  	359
	123  	359
	123  	362
	118  	362
	118  	362
	133  	362


gconnect gain3 0  cxmakecx3 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	127  	463
	136  	463
	136  	463
	125  	463
	125  	460
	140  	460


gconnect cxmakecx2 0  cxmimoch0 2
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	243  	362
	266  	362
	266  	156
	266  	156
	266  	156
	289  	156


gconnect cxmakecx3 0  cxmimoch0 3
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	250  	460
	262  	460
	262  	181
	262  	181
	262  	181
	289  	181


gconnect cxmimoch0 0  cxplot0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	399  	114
	408  	114
	408  	114
	434  	114
	434  	72
	449  	72


gconnect cxmimoch0 1  cxplot1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	399  	166
	413  	166
	413  	166
	436  	166
	436  	145
	451  	145


gconnect cxplot0 0  prbspectrum0840 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	539  	72
	548  	72
	548  	74
	609  	74
	609  	74
	624  	74


