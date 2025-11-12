# Graphics info for galaxy siso_eq

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 1227
Scroll Window Height: 381


gblock bdata0
	xLoc: 34  	yLoc: 132
	xDel: 50  	yDel: 30


gblock Encoder0
	xLoc: 147  	yLoc: 137
	xDel: 100  	yDel: 30


gblock intlvrMapperiFFT0
	xLoc: 321  	yLoc: 142
	xDel: 190  	yDel: 30


gblock cxgain1
	xLoc: 512  	yLoc: 141
	xDel: 90  	yDel: 30


gblock cxmimoch0
	xLoc: 663  	yLoc: 144
	xDel: 110  	yDel: 30


gblock cxaddnoise0
	xLoc: 138  	yLoc: 302
	xDel: 130  	yDel: 30


gblock rmcpfx0
	xLoc: 312  	yLoc: 303
	xDel: 90  	yDel: 30


gblock fwfft0
	xLoc: 442  	yLoc: 305
	xDel: 80  	yDel: 30


gblock scatter1
	xLoc: 533  	yLoc: 306
	xDel: 50  	yDel: 30


gblock cxmimoeqzf0
	xLoc: 652  	yLoc: 307
	xDel: 130  	yDel: 30


gblock scatter0
	xLoc: 782  	yLoc: 312
	xDel: 50  	yDel: 30


gconnect bdata0 0  Encoder0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	59  	132
	68  	132
	68  	137
	82  	137
	82  	137
	97  	137


gconnect Encoder0 0  intlvrMapperiFFT0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	197  	137
	206  	137
	206  	142
	211  	142
	211  	142
	226  	142


gconnect intlvrMapperiFFT0 0  cxgain1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	416  	142
	425  	142
	425  	142
	452  	142
	452  	141
	467  	141


gconnect cxgain1 0  cxmimoch0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	557  	141
	566  	141
	566  	144
	593  	144
	593  	144
	608  	144


gconnect cxmimoch0 0  cxaddnoise0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	718  	144
	727  	144
	727  	332
	58  	332
	58  	302
	73  	302


gconnect cxaddnoise0 0  rmcpfx0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	203  	302
	212  	302
	212  	303
	252  	303
	252  	303
	267  	303


gconnect rmcpfx0 0  fwfft0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	357  	303
	366  	303
	366  	305
	387  	305
	387  	305
	402  	305


gconnect fwfft0 0  scatter1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	482  	305
	491  	305
	491  	306
	493  	306
	493  	306
	508  	306


gconnect scatter1 0  cxmimoeqzf0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	558  	306
	567  	306
	567  	307
	572  	307
	572  	307
	587  	307


gconnect cxmimoeqzf0 0  scatter0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	717  	307
	726  	307
	726  	312
	742  	312
	742  	312
	757  	312


