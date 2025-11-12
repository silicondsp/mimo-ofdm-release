# Graphics info for galaxy MIMO_Test

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 1227
Scroll Window Height: 710


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
	xLoc: 734  	yLoc: 206
	xDel: 110  	yDel: 30


gblock rmcpfx0
	xLoc: 862  	yLoc: 150
	xDel: 90  	yDel: 30


gblock rmcpfx1
	xLoc: 869  	yLoc: 206
	xDel: 90  	yDel: 30


gblock fwfft0
	xLoc: 1025  	yLoc: 149
	xDel: 80  	yDel: 30


gblock fwfft1
	xLoc: 1003  	yLoc: 213
	xDel: 80  	yDel: 30


gblock scatter0
	xLoc: 1132  	yLoc: 152
	xDel: 50  	yDel: 30


gblock scatter1
	xLoc: 1121  	yLoc: 207
	xDel: 50  	yDel: 30


gblock rmcpfx2
	xLoc: 869  	yLoc: 276
	xDel: 90  	yDel: 30


gblock fwfft2
	xLoc: 1004  	yLoc: 275
	xDel: 80  	yDel: 30


gblock scatter2
	xLoc: 1116  	yLoc: 277
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
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	649  	250
	658  	250
	658  	250
	660  	250
	660  	220
	679  	220


gconnect cxgain1 0  cxmimoch0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	645  	165
	654  	165
	654  	181
	664  	181
	664  	181
	679  	181


gconnect cxmimoch0 0  rmcpfx0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	789  	177
	798  	177
	798  	177
	802  	177
	802  	150
	817  	150


gconnect cxmimoch0 1  rmcpfx1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	789  	204
	803  	204
	803  	206
	809  	206
	809  	206
	824  	206


gconnect cxmimoch0 2  rmcpfx2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	789  	231
	808  	231
	808  	276
	809  	276
	809  	276
	824  	276


gconnect rmcpfx0 0  fwfft0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	907  	150
	916  	150
	916  	150
	970  	150
	970  	149
	985  	149


gconnect rmcpfx1 0  fwfft1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	914  	206
	923  	206
	923  	213
	948  	213
	948  	213
	963  	213


gconnect fwfft0 0  scatter0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1065  	149
	1074  	149
	1074  	152
	1092  	152
	1092  	152
	1107  	152


gconnect fwfft1 0  scatter1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1043  	213
	1052  	213
	1052  	213
	1081  	213
	1081  	207
	1096  	207


gconnect rmcpfx2 0  fwfft2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	914  	276
	923  	276
	923  	276
	949  	276
	949  	275
	964  	275


gconnect fwfft2 0  scatter2 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1044  	275
	1053  	275
	1053  	277
	1076  	277
	1076  	277
	1091  	277


