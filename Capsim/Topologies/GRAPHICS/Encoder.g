# Graphics info for galaxy Encoder

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 871
Scroll Window Height: 337


gblock dataField0
	xLoc: 218  	yLoc: 167
	xDel: 120  	yDel: 30


gblock scramble0
	xLoc: 380  	yLoc: 160
	xDel: 110  	yDel: 30


gblock convenca0
	xLoc: 530  	yLoc: 160
	xDel: 110  	yDel: 30


gblock puncture0
	xLoc: 680  	yLoc: 160
	xDel: 110  	yDel: 30


gconnect input 0  dataField0 0
	termType: -1  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	38  	167
	43  	167
	43  	167
	143  	167
	143  	167
	158  	167


gconnect dataField0 0  scramble0 0
	termType: 0  	probeType: 1 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	278  	167
	287  	167
	287  	167
	310  	167
	310  	160
	325  	160


gconnect scramble0 0  convenca0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	435  	160
	444  	160
	444  	160
	460  	160
	460  	160
	475  	160


gconnect convenca0 0  puncture0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	585  	141
	594  	141
	594  	141
	610  	141
	610  	141
	625  	141


gconnect convenca0 1  puncture0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	585  	169
	599  	169
	599  	169
	606  	169
	606  	168
	625  	168


gconnect puncture0 0  output 0
	termType: 1  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	735  	160
	744  	160
	744  	160
	755  	160
	755  	160
	770  	160


