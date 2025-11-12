# Graphics info for galaxy MIMOTx

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 1176
Scroll Window Height: 580


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


gblock intlvrMapperiFFT1
	xLoc: 507  	yLoc: 251
	xDel: 190  	yDel: 30


gblock cxmimoch0
	xLoc: 712  	yLoc: 210
	xDel: 110  	yDel: 30


gblock cxreim0
	xLoc: 876  	yLoc: 145
	xDel: 90  	yDel: 30


gblock prbspectrum0394
	xLoc: 1045  	yLoc: 151
	xDel: 70  	yDel: 30


gblock sink0
	xLoc: 985  	yLoc: 201
	xDel: 40  	yDel: 30


gblock cxreim1
	xLoc: 882  	yLoc: 314
	xDel: 90  	yDel: 30


gblock prbspectrum0840
	xLoc: 1031  	yLoc: 333
	xDel: 70  	yDel: 30


gblock sink1
	xLoc: 1003  	yLoc: 385
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


gconnect intlvrMapperiFFT0 0  cxmimoch0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	598  	148
	642  	148
	642  	191
	642  	191
	642  	191
	657  	191


gconnect intlvrMapperiFFT1 0  cxmimoch0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	602  	251
	611  	251
	611  	251
	638  	251
	638  	218
	657  	218


gconnect cxmimoch0 0  cxreim0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	767  	191
	776  	191
	776  	191
	816  	191
	816  	145
	831  	145


gconnect cxmimoch0 1  cxreim1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	767  	219
	781  	219
	781  	314
	822  	314
	822  	314
	837  	314


gconnect cxreim0 0  prbspectrum0394 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	921  	126
	930  	126
	930  	151
	995  	151
	995  	151
	1010  	151


gconnect cxreim0 1  sink0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	921  	154
	935  	154
	935  	201
	950  	201
	950  	201
	965  	201


gconnect cxreim1 0  prbspectrum0840 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	927  	295
	936  	295
	936  	333
	981  	333
	981  	333
	996  	333


gconnect cxreim1 1  sink1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	927  	323
	941  	323
	941  	385
	968  	385
	968  	385
	983  	385


