# Graphics info for galaxy mimo_mrc

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 1227
Scroll Window Height: 422


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
	xLoc: 95  	yLoc: 348
	xDel: 110  	yDel: 30


gblock cxaddnoise0
	xLoc: 276  	yLoc: 302
	xDel: 130  	yDel: 30


gblock rmcpfx0
	xLoc: 450  	yLoc: 303
	xDel: 90  	yDel: 30


gblock fwfft0
	xLoc: 580  	yLoc: 305
	xDel: 80  	yDel: 30


gblock scatter1
	xLoc: 671  	yLoc: 306
	xDel: 50  	yDel: 30


gblock rmcpfx1
	xLoc: 451  	yLoc: 376
	xDel: 90  	yDel: 30


gblock fwfft1
	xLoc: 570  	yLoc: 377
	xDel: 80  	yDel: 30


gblock cxmimoeqzf0
	xLoc: 790  	yLoc: 307
	xDel: 130  	yDel: 30


gblock scatter0
	xLoc: 920  	yLoc: 312
	xDel: 50  	yDel: 30


gblock cxaddnoise1
	xLoc: 278  	yLoc: 378
	xDel: 130  	yDel: 30


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
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 1 
	pathPts(x,y): 6
	560  	143
	574  	143
	574  	238
	16  	239
	17  	350
	41  	350


gconnect cxmimoch0 0  cxaddnoise0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	150  	329
	159  	329
	159  	329
	196  	329
	196  	302
	211  	302


gconnect cxmimoch0 1  cxaddnoise1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	150  	357
	164  	357
	164  	378
	198  	378
	198  	378
	213  	378


gconnect cxaddnoise0 0  rmcpfx0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	341  	302
	350  	302
	350  	303
	390  	303
	390  	303
	405  	303


gconnect rmcpfx0 0  fwfft0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	495  	303
	504  	303
	504  	305
	525  	305
	525  	305
	540  	305


gconnect fwfft0 0  scatter1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	620  	305
	629  	305
	629  	306
	631  	306
	631  	306
	646  	306


gconnect scatter1 0  cxmimoeqzf0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	696  	306
	705  	306
	705  	306
	710  	306
	710  	288
	725  	288


gconnect rmcpfx1 0  fwfft1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	496  	376
	505  	376
	505  	377
	515  	377
	515  	377
	530  	377


gconnect fwfft1 0  cxmimoeqzf0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	610  	377
	619  	377
	619  	377
	706  	377
	706  	315
	725  	315


gconnect cxmimoeqzf0 0  scatter0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	855  	307
	864  	307
	864  	312
	880  	312
	880  	312
	895  	312


gconnect cxaddnoise1 0  rmcpfx1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	343  	378
	352  	378
	352  	378
	391  	378
	391  	376
	406  	376


