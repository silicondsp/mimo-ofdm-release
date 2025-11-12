# Graphics info for galaxy 2streamTx

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 1067
Scroll Window Height: 581


gblock bdata0
	xLoc: 34  	yLoc: 132
	xDel: 50  	yDel: 30


gblock Encoder0
	xLoc: 147  	yLoc: 137
	xDel: 100  	yDel: 30


gblock demux0
	xLoc: 269  	yLoc: 141
	xDel: 80  	yDel: 30


gblock intlvrMapperiFFT0
	xLoc: 503  	yLoc: 148
	xDel: 190  	yDel: 30


gblock cxreim0
	xLoc: 680  	yLoc: 144
	xDel: 90  	yDel: 30


gblock prbspectrum0394
	xLoc: 849  	yLoc: 150
	xDel: 70  	yDel: 30


gblock sink0
	xLoc: 789  	yLoc: 200
	xDel: 40  	yDel: 30


gblock intlvrMapperiFFT1
	xLoc: 507  	yLoc: 251
	xDel: 190  	yDel: 30


gblock cxreim1
	xLoc: 699  	yLoc: 280
	xDel: 90  	yDel: 30


gblock prbspectrum0840
	xLoc: 848  	yLoc: 299
	xDel: 70  	yDel: 30


gblock sink1
	xLoc: 820  	yLoc: 351
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


gconnect Encoder0 0  demux0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	197  	137
	206  	137
	206  	141
	214  	141
	214  	141
	229  	141


gconnect demux0 0  intlvrMapperiFFT0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	309  	122
	318  	122
	318  	148
	393  	148
	393  	148
	408  	148


gconnect demux0 1  intlvrMapperiFFT1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	309  	150
	323  	150
	323  	251
	397  	251
	397  	251
	412  	251


gconnect intlvrMapperiFFT0 0  cxreim0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	598  	148
	607  	148
	607  	148
	620  	148
	620  	144
	635  	144


gconnect cxreim0 0  prbspectrum0394 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	725  	125
	734  	125
	734  	150
	799  	150
	799  	150
	814  	150


gconnect cxreim0 1  sink0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	725  	153
	739  	153
	739  	200
	754  	200
	754  	200
	769  	200


gconnect intlvrMapperiFFT1 0  cxreim1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	602  	251
	611  	251
	611  	280
	639  	280
	639  	280
	654  	280


gconnect cxreim1 0  prbspectrum0840 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	744  	261
	753  	261
	753  	299
	798  	299
	798  	299
	813  	299


gconnect cxreim1 1  sink1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	744  	289
	758  	289
	758  	351
	785  	351
	785  	351
	800  	351


