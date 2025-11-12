# Graphics info for galaxy 2x3_mimo_eq_strong_weak

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 1607
Scroll Window Height: 537


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
	xLoc: 237  	yLoc: 403
	xDel: 110  	yDel: 30


gblock cxaddnoise0
	xLoc: 426  	yLoc: 361
	xDel: 130  	yDel: 30


gblock rmcpfx0
	xLoc: 577  	yLoc: 356
	xDel: 90  	yDel: 30


gblock fwfft0
	xLoc: 748  	yLoc: 358
	xDel: 80  	yDel: 30


gblock cxaddnoise1
	xLoc: 430  	yLoc: 402
	xDel: 130  	yDel: 30


gblock rmcpfx1
	xLoc: 580  	yLoc: 403
	xDel: 90  	yDel: 30


gblock fwfft1
	xLoc: 747  	yLoc: 411
	xDel: 80  	yDel: 30


gblock cxaddnoise2
	xLoc: 430  	yLoc: 451
	xDel: 130  	yDel: 30


gblock rmcpfx2
	xLoc: 573  	yLoc: 453
	xDel: 90  	yDel: 30


gblock fwfft2
	xLoc: 748  	yLoc: 473
	xDel: 80  	yDel: 30


gblock cxmimoeqzf0
	xLoc: 951  	yLoc: 418
	xDel: 130  	yDel: 30


gblock scatter0
	xLoc: 1116  	yLoc: 390
	xDel: 50  	yDel: 30


gblock scatter1
	xLoc: 1117  	yLoc: 435
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
	650  	250
	675  	250
	675  	303
	115  	302
	115  	420
	181  	419


gconnect cxgain1 0  cxmimoch0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 1 
	pathPts(x,y): 6
	643  	164
	688  	164
	688  	317
	147  	318
	147  	376
	181  	376


gconnect cxmimoch0 0  cxaddnoise0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	292  	374
	301  	374
	301  	374
	346  	374
	346  	361
	361  	361


gconnect cxmimoch0 1  cxaddnoise1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	292  	401
	306  	401
	306  	402
	350  	402
	350  	402
	365  	402


gconnect cxmimoch0 2  cxaddnoise2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	292  	428
	311  	428
	311  	451
	350  	451
	350  	451
	365  	451


gconnect cxaddnoise0 0  rmcpfx0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	491  	361
	500  	361
	500  	361
	517  	361
	517  	356
	532  	356


gconnect rmcpfx0 0  fwfft0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	622  	356
	631  	356
	631  	358
	693  	358
	693  	358
	708  	358


gconnect fwfft0 0  cxmimoeqzf0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	788  	358
	797  	358
	797  	389
	871  	389
	871  	389
	886  	389


gconnect cxaddnoise1 0  rmcpfx1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	495  	402
	504  	402
	504  	403
	520  	403
	520  	403
	535  	403


gconnect rmcpfx1 0  fwfft1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	625  	403
	634  	403
	634  	411
	692  	411
	692  	411
	707  	411


gconnect fwfft1 0  cxmimoeqzf0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	787  	411
	796  	411
	796  	415
	867  	415
	867  	415
	886  	415


gconnect cxaddnoise2 0  rmcpfx2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	495  	451
	504  	451
	504  	453
	513  	453
	513  	453
	528  	453


gconnect rmcpfx2 0  fwfft2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	618  	453
	627  	453
	627  	473
	693  	473
	693  	473
	708  	473


gconnect fwfft2 0  cxmimoeqzf0 2
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	788  	473
	797  	473
	797  	473
	863  	473
	863  	441
	886  	441


gconnect cxmimoeqzf0 0  scatter0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1016  	393
	1025  	393
	1025  	393
	1076  	393
	1076  	390
	1091  	390


gconnect cxmimoeqzf0 1  scatter1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1016  	433
	1030  	433
	1030  	435
	1077  	435
	1077  	435
	1092  	435


