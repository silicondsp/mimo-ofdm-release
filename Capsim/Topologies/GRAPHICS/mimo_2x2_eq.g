# Graphics info for galaxy mimo_2x2_eq

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 1362
Scroll Window Height: 366


gblock bdata0
	xLoc: 47  	yLoc: 140
	xDel: 50  	yDel: 30


gblock Encoder0
	xLoc: 147  	yLoc: 137
	xDel: 100  	yDel: 30


gblock demux0
	xLoc: 263  	yLoc: 143
	xDel: 80  	yDel: 30


gblock intlvrMapperiFFT0
	xLoc: 426  	yLoc: 129
	xDel: 190  	yDel: 30


gblock intlvrMapperiFFT1
	xLoc: 432  	yLoc: 179
	xDel: 190  	yDel: 30


gblock cxmimoch0
	xLoc: 629  	yLoc: 156
	xDel: 110  	yDel: 30


gblock cxaddnoise0
	xLoc: 786  	yLoc: 122
	xDel: 130  	yDel: 30


gblock rmcpfx0
	xLoc: 919  	yLoc: 123
	xDel: 90  	yDel: 30


gblock fwfft0
	xLoc: 1036  	yLoc: 123
	xDel: 80  	yDel: 30


gblock cxaddnoise1
	xLoc: 787  	yLoc: 163
	xDel: 130  	yDel: 30


gblock rmcpfx1
	xLoc: 921  	yLoc: 165
	xDel: 90  	yDel: 30


gblock fwfft1
	xLoc: 1034  	yLoc: 166
	xDel: 80  	yDel: 30


gblock cxmimoeqzf0
	xLoc: 1185  	yLoc: 176
	xDel: 130  	yDel: 30


gblock scatter0
	xLoc: 1309  	yLoc: 146
	xDel: 50  	yDel: 30


gblock scatter1
	xLoc: 1308  	yLoc: 196
	xDel: 50  	yDel: 30


gblock evm0
	xLoc: 1440  	yLoc: 140
	xDel: 60  	yDel: 30


gblock evm1
	xLoc: 1442  	yLoc: 196
	xDel: 60  	yDel: 30


gconnect bdata0 0  Encoder0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	72  	140
	81  	140
	81  	140
	82  	140
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
	312  	129
	316  	129
	316  	129
	331  	129


gconnect demux0 1  intlvrMapperiFFT1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	303  	152
	317  	152
	317  	179
	322  	179
	322  	179
	337  	179


gconnect intlvrMapperiFFT0 0  cxmimoch0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	521  	129
	530  	129
	530  	137
	559  	137
	559  	137
	574  	137


gconnect intlvrMapperiFFT1 0  cxmimoch0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	527  	179
	536  	179
	536  	179
	555  	179
	555  	164
	574  	164


gconnect cxmimoch0 0  cxaddnoise0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	684  	137
	693  	137
	693  	137
	706  	137
	706  	122
	721  	122


gconnect cxmimoch0 1  cxaddnoise1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	684  	165
	698  	165
	698  	165
	707  	165
	707  	163
	722  	163


gconnect cxaddnoise0 0  rmcpfx0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	851  	122
	860  	122
	860  	123
	859  	123
	859  	123
	874  	123


gconnect rmcpfx0 0  fwfft0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	964  	123
	973  	123
	973  	123
	981  	123
	981  	123
	996  	123


gconnect fwfft0 0  cxmimoeqzf0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1076  	123
	1085  	123
	1085  	157
	1105  	157
	1105  	157
	1120  	157


gconnect cxaddnoise1 0  rmcpfx1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	852  	163
	861  	163
	861  	165
	861  	165
	861  	165
	876  	165


gconnect rmcpfx1 0  fwfft1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	966  	165
	975  	165
	975  	166
	979  	166
	979  	166
	994  	166


gconnect fwfft1 0  cxmimoeqzf0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1074  	166
	1083  	166
	1083  	184
	1101  	184
	1101  	184
	1120  	184


gconnect cxmimoeqzf0 0  scatter0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1250  	157
	1259  	157
	1259  	157
	1269  	157
	1269  	146
	1284  	146


gconnect cxmimoeqzf0 1  scatter1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1250  	185
	1264  	185
	1264  	196
	1268  	196
	1268  	196
	1283  	196


gconnect scatter0 0  evm0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1334  	146
	1343  	146
	1343  	146
	1395  	146
	1395  	140
	1410  	140


gconnect scatter1 0  evm1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	1333  	196
	1342  	196
	1342  	196
	1397  	196
	1397  	196
	1412  	196


