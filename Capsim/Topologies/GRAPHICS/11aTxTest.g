# Graphics info for galaxy 11aTxTest

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 800
Scroll Window Height: 400


gblock bdata0
	xLoc: 34  	yLoc: 132
	xDel: 50  	yDel: 30


gblock Encoder0
	xLoc: 147  	yLoc: 137
	xDel: 100  	yDel: 30


gblock intlvrMapperiFFT0
	xLoc: 350  	yLoc: 141
	xDel: 190  	yDel: 30


gblock cxreim0
	xLoc: 546  	yLoc: 141
	xDel: 90  	yDel: 30


gblock prbspectrum0394
	xLoc: 715  	yLoc: 147
	xDel: 70  	yDel: 30


gblock sink0
	xLoc: 655  	yLoc: 197
	xDel: 40  	yDel: 30


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
	206  	141
	240  	141
	240  	141
	255  	141


gconnect intlvrMapperiFFT0 0  cxreim0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	445  	141
	454  	141
	454  	141
	486  	141
	486  	141
	501  	141


gconnect cxreim0 0  prbspectrum0394 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	591  	122
	600  	122
	600  	147
	665  	147
	665  	147
	680  	147


gconnect cxreim0 1  sink0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	591  	150
	605  	150
	605  	197
	620  	197
	620  	197
	635  	197


