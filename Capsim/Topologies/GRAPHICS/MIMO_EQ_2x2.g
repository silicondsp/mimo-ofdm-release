# Graphics info for galaxy MIMO_EQ_2x2

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 1014
Scroll Window Height: 527


gblock bdata0
	xLoc: 34  	yLoc: 132
	xDel: 50  	yDel: 30


gblock Encoder0
	xLoc: 147  	yLoc: 137
	xDel: 100  	yDel: 30


gblock demux0
	xLoc: 263  	yLoc: 143
	xDel: 80  	yDel: 30


gblock intlvrMapperiFFT0
	xLoc: 427  	yLoc: 144
	xDel: 189  	yDel: 30


gblock intlvrMapperiFFT1
	xLoc: 431  	yLoc: 251
	xDel: 189  	yDel: 30


gblock cxgain0
	xLoc: 604  	yLoc: 250
	xDel: 89  	yDel: 30


gblock cxgain1
	xLoc: 600  	yLoc: 165
	xDel: 89  	yDel: 30


gblock cxmimoch0
	xLoc: 122  	yLoc: 500
	xDel: 110  	yDel: 30


gblock cxaddnoise0
	xLoc: 311  	yLoc: 458
	xDel: 130  	yDel: 30


gblock rmcpfx0
	xLoc: 491  	yLoc: 445
	xDel: 89  	yDel: 30


gblock fwfft0
	xLoc: 654  	yLoc: 444
	xDel: 80  	yDel: 30


gblock cxaddnoise1
	xLoc: 315  	yLoc: 499
	xDel: 130  	yDel: 30


gblock rmcpfx1
	xLoc: 498  	yLoc: 501
	xDel: 89  	yDel: 30


gblock fwfft1
	xLoc: 632  	yLoc: 508
	xDel: 80  	yDel: 30


gblock cxmimoeqzf0
	xLoc: 781  	yLoc: 493
	xDel: 130  	yDel: 30


gblock scatter0
	xLoc: 903  	yLoc: 484
	xDel: 50  	yDel: 30


gblock scatter1
	xLoc: 903  	yLoc: 524
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


gconnect Encoder0 0  demux0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	197  	137
	206  	137
	206  	143
	208  	143
	208  	143
	223  	143


gconnect demux0 0  intlvrMapperiFFT0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	303  	124
	312  	124
	312  	144
	318  	144
	318  	144
	333  	144


gconnect demux0 1  intlvrMapperiFFT1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	303  	152
	317  	152
	317  	251
	322  	251
	322  	251
	337  	251


gconnect intlvrMapperiFFT0 0  cxgain1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	522  	144
	531  	144
	531  	165
	541  	165
	541  	165
	556  	165


gconnect intlvrMapperiFFT1 0  cxgain0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	526  	251
	535  	251
	535  	251
	545  	251
	545  	250
	560  	250


gconnect cxgain0 0  cxmimoch0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 1 
	pathPts(x,y): 6
	651  	253
	675  	251
	675  	315
	8  	315
	8  	511
	69  	511


gconnect cxgain1 0  cxmimoch0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 1 
	pathPts(x,y): 6
	646  	165
	693  	165
	693  	341
	26  	341
	26  	473
	68  	475


gconnect cxmimoch0 0  cxaddnoise0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	177  	481
	186  	481
	186  	481
	231  	481
	231  	458
	246  	458


gconnect cxmimoch0 1  cxaddnoise1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	177  	509
	191  	509
	191  	509
	235  	509
	235  	499
	250  	499


gconnect cxaddnoise0 0  rmcpfx0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	376  	458
	385  	458
	385  	458
	432  	458
	432  	445
	447  	445


gconnect rmcpfx0 0  fwfft0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	536  	445
	545  	445
	545  	445
	599  	445
	599  	444
	614  	444


gconnect fwfft0 0  cxmimoeqzf0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	694  	444
	701  	444
	701  	474
	701  	474
	701  	474
	716  	474


gconnect cxaddnoise1 0  rmcpfx1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	380  	499
	389  	499
	389  	501
	439  	501
	439  	501
	454  	501


gconnect rmcpfx1 0  fwfft1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	543  	501
	552  	501
	552  	508
	577  	508
	577  	508
	592  	508


gconnect fwfft1 0  cxmimoeqzf0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	672  	508
	681  	508
	681  	508
	697  	508
	697  	501
	716  	501


gconnect cxmimoeqzf0 0  scatter0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	846  	474
	855  	474
	855  	484
	863  	484
	863  	484
	878  	484


gconnect cxmimoeqzf0 1  scatter1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	846  	502
	860  	502
	860  	524
	863  	524
	863  	524
	878  	524


