# Graphics info for galaxy svdmimo_2x2_cordic_fp

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


gblock intlvrMapperPilots1
	xLoc: 447  	yLoc: 208
	xDel: 210  	yDel: 30


gblock intlvrMapperPilots0
	xLoc: 439  	yLoc: 121
	xDel: 210  	yDel: 30


gblock ifftofdmsvd0
	xLoc: 669  	yLoc: 175
	xDel: 140  	yDel: 30


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


gblock cxmimo_2x2_svd_fp0
	xLoc: 781  	yLoc: 493
	xDel: 200  	yDel: 30


gblock prcxmat0
	xLoc: 918  	yLoc: 379
	xDel: 100  	yDel: 30


gblock scatter0
	xLoc: 926  	yLoc: 481
	xDel: 50  	yDel: 30


gblock scatter1
	xLoc: 932  	yLoc: 535
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


gconnect demux0 0  intlvrMapperPilots0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	303  	124
	312  	124
	312  	124
	319  	124
	319  	121
	334  	121


gconnect demux0 1  intlvrMapperPilots1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	303  	152
	317  	152
	317  	208
	327  	208
	327  	208
	342  	208


gconnect intlvrMapperPilots1 0  ifftofdmsvd0 2
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	552  	208
	561  	208
	561  	208
	576  	208
	576  	198
	599  	198


gconnect intlvrMapperPilots0 0  ifftofdmsvd0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	544  	121
	580  	121
	580  	172
	580  	172
	580  	172
	599  	172


gconnect ifftofdmsvd0 0  cxmimoch0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 1 
	pathPts(x,y): 6
	740  	148
	781  	148
	781  	390
	39  	390
	39  	481
	66  	480


gconnect ifftofdmsvd0 1  cxmimoch0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 1 
	pathPts(x,y): 6
	741  	191
	766  	190
	765  	375
	28  	375
	28  	509
	68  	509


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


gconnect fwfft0 0  cxmimo_2x2_svd_fp0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	694  	444
	666  	444
	666  	468
	666  	468
	666  	468
	681  	468


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


gconnect fwfft1 0  cxmimo_2x2_svd_fp0 1
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	672  	508
	681  	508
	681  	508
	662  	508
	662  	507
	681  	507


gconnect cxmimo_2x2_svd_fp0 0  prcxmat0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	881  	464
	853  	464
	853  	464
	853  	464
	853  	379
	868  	379


gconnect cxmimo_2x2_svd_fp0 1  scatter0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	881  	491
	895  	491
	895  	491
	886  	491
	886  	481
	901  	481


gconnect cxmimo_2x2_svd_fp0 2  scatter1 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 0 
	pathPts(x,y): 6
	881  	518
	900  	518
	900  	535
	892  	535
	892  	535
	907  	535


gconnect prcxmat0 0  ifftofdmsvd0 0
	termType: 0  	probeType: 0 	pacerFlag: 0	autoConnect: 1 
	pathPts(x,y): 6
	969  	376
	979  	376
	979  	117
	584  	115
	585  	147
	600  	146


