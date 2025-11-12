# Graphics info for galaxy MIMO_EQ

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 1252
Scroll Window Height: 706


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
	xDel: 190  	yDel: 30


gblock intlvrMapperiFFT1
	xLoc: 431  	yLoc: 251
	xDel: 190  	yDel: 30


gblock cxgain0
	xLoc: 604  	yLoc: 250
	xDel: 90  	yDel: 30


gblock cxgain1
	xLoc: 600  	yLoc: 165
	xDel: 90  	yDel: 30


gblock cxmimoch0
	xLoc: 122  	yLoc: 500
	xDel: 110  	yDel: 30


gblock cxaddnoise0
	xLoc: 311  	yLoc: 458
	xDel: 130  	yDel: 30


gblock rmcpfx0
	xLoc: 491  	yLoc: 445
	xDel: 90  	yDel: 30


gblock fwfft0
	xLoc: 654  	yLoc: 444
	xDel: 80  	yDel: 30


gblock cxaddnoise1
	xLoc: 315  	yLoc: 499
	xDel: 130  	yDel: 30


gblock rmcpfx1
	xLoc: 498  	yLoc: 501
	xDel: 90  	yDel: 30


gblock fwfft1
	xLoc: 632  	yLoc: 508
	xDel: 80  	yDel: 30


gblock cxaddnoise2
	xLoc: 315  	yLoc: 548
	xDel: 130  	yDel: 30


gblock rmcpfx2
	xLoc: 498  	yLoc: 571
	xDel: 90  	yDel: 30


gblock fwfft2
	xLoc: 633  	yLoc: 570
	xDel: 80  	yDel: 30


gblock cxmimoeqzf0
	xLoc: 836  	yLoc: 515
	xDel: 130  	yDel: 30


gblock scatter0
	xLoc: 966  	yLoc: 488
	xDel: 50  	yDel: 30


gblock scatter1
	xLoc: 968  	yLoc: 529
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
	317  	144
	317  	144
	332  	144


gconnect demux0 1  intlvrMapperiFFT1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	303  	152
	317  	152
	317  	251
	321  	251
	321  	251
	336  	251


gconnect intlvrMapperiFFT0 0  cxgain1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	522  	144
	531  	144
	531  	165
	540  	165
	540  	165
	555  	165


gconnect intlvrMapperiFFT1 0  cxgain0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	526  	251
	535  	251
	535  	251
	544  	251
	544  	250
	559  	250


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
	177  	471
	186  	471
	186  	471
	231  	471
	231  	458
	246  	458


gconnect cxmimoch0 1  cxaddnoise1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	177  	498
	191  	498
	191  	499
	235  	499
	235  	499
	250  	499


gconnect cxmimoch0 2  cxaddnoise2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	177  	525
	196  	525
	196  	548
	235  	548
	235  	548
	250  	548


gconnect cxaddnoise0 0  rmcpfx0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	376  	458
	385  	458
	385  	458
	431  	458
	431  	445
	446  	445


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
	703  	444
	703  	486
	756  	486
	756  	486
	771  	486


gconnect cxaddnoise1 0  rmcpfx1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	380  	499
	389  	499
	389  	501
	438  	501
	438  	501
	453  	501


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
	681  	512
	752  	512
	752  	512
	771  	512


gconnect cxaddnoise2 0  rmcpfx2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	380  	548
	389  	548
	389  	571
	438  	571
	438  	571
	453  	571


gconnect rmcpfx2 0  fwfft2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	543  	571
	552  	571
	552  	571
	578  	571
	578  	570
	593  	570


gconnect fwfft2 0  cxmimoeqzf0 2
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	673  	570
	682  	570
	682  	570
	748  	570
	748  	538
	771  	538


gconnect cxmimoeqzf0 0  scatter0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	901  	490
	910  	490
	910  	490
	926  	490
	926  	488
	941  	488


gconnect cxmimoeqzf0 1  scatter1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	901  	530
	915  	530
	915  	530
	928  	530
	928  	529
	943  	529


