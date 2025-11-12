# Graphics info for galaxy Tx80211a

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 871
Scroll Window Height: 337


gblock dataField0
	xLoc: 220  	yLoc: 100
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


gblock interlr0
	xLoc: 830  	yLoc: 160
	xDel: 100  	yDel: 30


gblock FQAM_64map0
	xLoc: 970  	yLoc: 190
	xDel: 130  	yDel: 30


gblock pilot0
	xLoc: 1108  	yLoc: 189
	xDel: 80  	yDel: 30


gblock ifftofdm540
	xLoc: 1260  	yLoc: 190
	xDel: 130  	yDel: 30


gconnect input 0  dataField0 0
	termType: -1  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	40  	100
	45  	100
	45  	100
	145  	100
	145  	100
	160  	100


gconnect dataField0 0  scramble0 0
	termType: 0  	probeType: 1 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	280  	100
	310  	100
	310  	160
	310  	160
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


gconnect puncture0 0  interlr0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	735  	160
	744  	160
	744  	160
	765  	160
	765  	160
	780  	160


gconnect interlr0 0  FQAM_64map0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	880  	160
	890  	160
	890  	190
	890  	190
	890  	190
	905  	190


gconnect FQAM_64map0 0  pilot0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1035  	190
	1044  	190
	1044  	190
	1053  	190
	1053  	189
	1068  	189


gconnect pilot0 0  ifftofdm540 0
	termType: 0  	probeType: 1 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1148  	189
	1157  	189
	1157  	190
	1180  	190
	1180  	190
	1195  	190


gconnect ifftofdm540 0  output 0
	termType: 1  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1325  	190
	1334  	190
	1334  	190
	1335  	190
	1335  	190
	1350  	190


