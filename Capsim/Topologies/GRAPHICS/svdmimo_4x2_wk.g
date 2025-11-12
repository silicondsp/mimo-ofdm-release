# Graphics info for galaxy svdmimo_4x2_wk

zoomFactor: 1.000000 
Vertical Scroll Bar: 0
Horizontal Scroll Bar: 0
Scroll Window Width: 1014
Scroll Window Height: 527


gblock bdata0
	xLoc: 80  	yLoc: 147
	xDel: 50  	yDel: 30


gblock Encoder0
	xLoc: 186  	yLoc: 151
	xDel: 100  	yDel: 30


gblock demux0
	xLoc: 301  	yLoc: 148
	xDel: 80  	yDel: 30


gblock intlvrMapperPilots1
	xLoc: 474  	yLoc: 192
	xDel: 210  	yDel: 30


gblock intlvrMapperPilots0
	xLoc: 473  	yLoc: 126
	xDel: 210  	yDel: 30


gblock stmat2x40
	xLoc: 660  	yLoc: 165
	xDel: 110  	yDel: 30


gblock ifftofdmsvd0
	xLoc: 877  	yLoc: 169
	xDel: 140  	yDel: 30


gblock cxmimoch0
	xLoc: 122  	yLoc: 450
	xDel: 110  	yDel: 30


gblock cxaddnoise0
	xLoc: 277  	yLoc: 458
	xDel: 130  	yDel: 30


gblock rmcpfx0
	xLoc: 414  	yLoc: 455
	xDel: 90  	yDel: 30


gblock fwfft0
	xLoc: 524  	yLoc: 454
	xDel: 80  	yDel: 30


gblock cxaddnoise1
	xLoc: 281  	yLoc: 499
	xDel: 130  	yDel: 30


gblock rmcpfx1
	xLoc: 418  	yLoc: 504
	xDel: 90  	yDel: 30


gblock fwfft1
	xLoc: 523  	yLoc: 503
	xDel: 80  	yDel: 30


gblock cxmimo_2x2_svd0
	xLoc: 647  	yLoc: 486
	xDel: 170  	yDel: 30


gblock prcxmat0
	xLoc: 708  	yLoc: 322
	xDel: 100  	yDel: 30


gblock stmat4x20
	xLoc: 804  	yLoc: 486
	xDel: 110  	yDel: 30


gblock scatter0
	xLoc: 918  	yLoc: 475
	xDel: 50  	yDel: 30


gblock scatter1
	xLoc: 920  	yLoc: 509
	xDel: 50  	yDel: 30


gconnect bdata0 0  Encoder0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	105  	147
	114  	147
	114  	151
	121  	151
	121  	151
	136  	151


gconnect Encoder0 0  demux0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	236  	151
	245  	151
	245  	151
	246  	151
	246  	148
	261  	148


gconnect demux0 0  intlvrMapperPilots0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	341  	129
	350  	129
	350  	129
	353  	129
	353  	126
	368  	126


gconnect demux0 1  intlvrMapperPilots1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	341  	157
	355  	157
	355  	192
	354  	192
	354  	192
	369  	192


gconnect intlvrMapperPilots1 0  stmat2x40 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	579  	192
	588  	192
	588  	192
	586  	192
	586  	185
	605  	185


gconnect intlvrMapperPilots0 0  stmat2x40 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	578  	126
	587  	126
	587  	134
	590  	134
	590  	134
	605  	134


gconnect stmat2x40 0  ifftofdmsvd0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	715  	126
	724  	126
	724  	145
	788  	145
	788  	145
	807  	145


gconnect stmat2x40 1  ifftofdmsvd0 2
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	715  	152
	729  	152
	729  	170
	784  	170
	784  	170
	807  	170


gconnect stmat2x40 2  ifftofdmsvd0 3
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	715  	178
	734  	178
	734  	195
	780  	195
	780  	195
	807  	195


gconnect stmat2x40 3  ifftofdmsvd0 4
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	715  	204
	739  	204
	739  	220
	776  	220
	776  	220
	807  	220


gconnect ifftofdmsvd0 0  cxmimoch0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	947  	124
	956  	124
	956  	534
	52  	534
	52  	411
	67  	411


gconnect ifftofdmsvd0 1  cxmimoch0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	947  	156
	961  	156
	961  	539
	48  	539
	48  	436
	67  	436


gconnect ifftofdmsvd0 2  cxmimoch0 2
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	947  	188
	966  	188
	966  	544
	44  	544
	44  	461
	67  	461


gconnect ifftofdmsvd0 3  cxmimoch0 3
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	947  	220
	971  	220
	971  	549
	40  	549
	40  	486
	67  	486


gconnect cxmimoch0 0  cxaddnoise0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	177  	419
	186  	419
	186  	458
	197  	458
	197  	458
	212  	458


gconnect cxmimoch0 1  cxaddnoise1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	177  	471
	191  	471
	191  	499
	201  	499
	201  	499
	216  	499


gconnect cxaddnoise0 0  rmcpfx0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	342  	458
	351  	458
	351  	458
	354  	458
	354  	455
	369  	455


gconnect rmcpfx0 0  fwfft0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	459  	455
	468  	455
	468  	455
	469  	455
	469  	454
	484  	454


gconnect fwfft0 0  cxmimo_2x2_svd0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	564  	454
	573  	454
	573  	461
	547  	461
	547  	461
	562  	461


gconnect cxaddnoise1 0  rmcpfx1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	346  	499
	355  	499
	355  	504
	358  	504
	358  	504
	373  	504


gconnect rmcpfx1 0  fwfft1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	463  	504
	472  	504
	472  	504
	468  	504
	468  	503
	483  	503


gconnect fwfft1 0  cxmimo_2x2_svd0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	563  	503
	572  	503
	572  	503
	543  	503
	543  	500
	562  	500


gconnect cxmimo_2x2_svd0 0  prcxmat0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 1 
	pathPts(x,y): 6
	709  	459
	730  	458
	730  	381
	631  	380
	631  	323
	656  	323


gconnect cxmimo_2x2_svd0 1  stmat4x20 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	732  	484
	746  	484
	746  	484
	734  	484
	734  	467
	749  	467


gconnect cxmimo_2x2_svd0 2  stmat4x20 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	732  	511
	751  	511
	751  	511
	730  	511
	730  	494
	749  	494


gconnect prcxmat0 0  ifftofdmsvd0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	758  	322
	767  	322
	767  	322
	792  	322
	792  	120
	807  	120


gconnect stmat4x20 0  scatter0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	859  	467
	868  	467
	868  	475
	878  	475
	878  	475
	893  	475


gconnect stmat4x20 1  scatter1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	859  	495
	873  	495
	873  	509
	880  	509
	880  	509
	895  	509


