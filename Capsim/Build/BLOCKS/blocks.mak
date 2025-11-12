all:libblock.a 

carroffset.c:carroffset.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar carroffset.s $(CAPSIM)/TOOLS/blockgen.xsl>carroffset.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a carroffset.s

carroffset.o:carroffset.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include carroffset.c

convenca.c:convenca.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar convenca.s $(CAPSIM)/TOOLS/blockgen.xsl>convenca.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a convenca.s

convenca.o:convenca.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include convenca.c

cxagc.c:cxagc.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar cxagc.s $(CAPSIM)/TOOLS/blockgen.xsl>cxagc.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a cxagc.s

cxagc.o:cxagc.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include cxagc.c

cxavgchannel.c:cxavgchannel.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar cxavgchannel.s $(CAPSIM)/TOOLS/blockgen.xsl>cxavgchannel.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a cxavgchannel.s

cxavgchannel.o:cxavgchannel.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include cxavgchannel.c

cxchmodel.c:cxchmodel.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar cxchmodel.s $(CAPSIM)/TOOLS/blockgen.xsl>cxchmodel.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a cxchmodel.s

cxchmodel.o:cxchmodel.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include cxchmodel.c

cxequalizezf.c:cxequalizezf.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar cxequalizezf.s $(CAPSIM)/TOOLS/blockgen.xsl>cxequalizezf.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a cxequalizezf.s

cxequalizezf.o:cxequalizezf.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include cxequalizezf.c

cxmimo_2x2_svd_fp.c:cxmimo_2x2_svd_fp.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar cxmimo_2x2_svd_fp.s $(CAPSIM)/TOOLS/blockgen.xsl>cxmimo_2x2_svd_fp.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a cxmimo_2x2_svd_fp.s

cxmimo_2x2_svd_fp.o:cxmimo_2x2_svd_fp.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include cxmimo_2x2_svd_fp.c

cxmimo_2x2_svd.c:cxmimo_2x2_svd.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar cxmimo_2x2_svd.s $(CAPSIM)/TOOLS/blockgen.xsl>cxmimo_2x2_svd.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a cxmimo_2x2_svd.s

cxmimo_2x2_svd.o:cxmimo_2x2_svd.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include cxmimo_2x2_svd.c

cxmimoch.c:cxmimoch.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar cxmimoch.s $(CAPSIM)/TOOLS/blockgen.xsl>cxmimoch.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a cxmimoch.s

cxmimoch.o:cxmimoch.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include cxmimoch.c

cxmimoeqzf.c:cxmimoeqzf.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar cxmimoeqzf.s $(CAPSIM)/TOOLS/blockgen.xsl>cxmimoeqzf.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a cxmimoeqzf.s

cxmimoeqzf.o:cxmimoeqzf.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include cxmimoeqzf.c

cxmimosvd.c:cxmimosvd.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar cxmimosvd.s $(CAPSIM)/TOOLS/blockgen.xsl>cxmimosvd.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a cxmimosvd.s

cxmimosvd.o:cxmimosvd.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include cxmimosvd.c

dataField.c:dataField.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar dataField.s $(CAPSIM)/TOOLS/blockgen.xsl>dataField.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a dataField.s

dataField.o:dataField.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include dataField.c

evm.c:evm.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar evm.s $(CAPSIM)/TOOLS/blockgen.xsl>evm.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a evm.s

evm.o:evm.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include evm.c

FQAM_64map.c:FQAM_64map.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar FQAM_64map.s $(CAPSIM)/TOOLS/blockgen.xsl>FQAM_64map.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a FQAM_64map.s

FQAM_64map.o:FQAM_64map.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include FQAM_64map.c

fwfft.c:fwfft.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar fwfft.s $(CAPSIM)/TOOLS/blockgen.xsl>fwfft.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a fwfft.s

fwfft.o:fwfft.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include fwfft.c

ifftofdm54.c:ifftofdm54.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar ifftofdm54.s $(CAPSIM)/TOOLS/blockgen.xsl>ifftofdm54.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a ifftofdm54.s

ifftofdm54.o:ifftofdm54.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include ifftofdm54.c

ifftofdmsvd.c:ifftofdmsvd.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar ifftofdmsvd.s $(CAPSIM)/TOOLS/blockgen.xsl>ifftofdmsvd.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a ifftofdmsvd.s

ifftofdmsvd.o:ifftofdmsvd.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include ifftofdmsvd.c

interlr.c:interlr.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar interlr.s $(CAPSIM)/TOOLS/blockgen.xsl>interlr.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a interlr.s

interlr.o:interlr.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include interlr.c

pilot.c:pilot.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar pilot.s $(CAPSIM)/TOOLS/blockgen.xsl>pilot.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a pilot.s

pilot.o:pilot.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include pilot.c

prcxmat.c:prcxmat.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar prcxmat.s $(CAPSIM)/TOOLS/blockgen.xsl>prcxmat.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a prcxmat.s

prcxmat.o:prcxmat.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include prcxmat.c

puncture.c:puncture.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar puncture.s $(CAPSIM)/TOOLS/blockgen.xsl>puncture.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a puncture.s

puncture.o:puncture.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include puncture.c

rmcpfx.c:rmcpfx.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar rmcpfx.s $(CAPSIM)/TOOLS/blockgen.xsl>rmcpfx.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a rmcpfx.s

rmcpfx.o:rmcpfx.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include rmcpfx.c

scramble.c:scramble.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar scramble.s $(CAPSIM)/TOOLS/blockgen.xsl>scramble.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a scramble.s

scramble.o:scramble.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include scramble.c

stmat2x4.c:stmat2x4.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar stmat2x4.s $(CAPSIM)/TOOLS/blockgen.xsl>stmat2x4.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a stmat2x4.s

stmat2x4.o:stmat2x4.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include stmat2x4.c

stmat4x2.c:stmat4x2.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar stmat4x2.s $(CAPSIM)/TOOLS/blockgen.xsl>stmat4x2.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a stmat4x2.s

stmat4x2.o:stmat4x2.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include stmat4x2.c

synchlong.c:synchlong.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar synchlong.s $(CAPSIM)/TOOLS/blockgen.xsl>synchlong.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a synchlong.s

synchlong.o:synchlong.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include synchlong.c

zdummy.c:zdummy.s
	java -jar $(CAPSIM)/TOOLS/saxon.jar zdummy.s $(CAPSIM)/TOOLS/blockgen.xsl>zdummy.c
	perl $(CAPSIM)/TOOLS/blockmaint.pl a zdummy.s

zdummy.o:zdummy.c
	cc -c -g  -I$(CAPSIM)/include -I$(CAPSIM)/include/TCL -I../include zdummy.c

libblock.a:carroffset.o convenca.o cxagc.o cxavgchannel.o cxchmodel.o cxequalizezf.o cxmimo_2x2_svd_fp.o cxmimo_2x2_svd.o cxmimoch.o cxmimoeqzf.o cxmimosvd.o dataField.o evm.o FQAM_64map.o fwfft.o ifftofdm54.o ifftofdmsvd.o interlr.o pilot.o prcxmat.o puncture.o rmcpfx.o scramble.o stmat2x4.o stmat4x2.o synchlong.o zdummy.o 
	ar -r libblock.a carroffset.o convenca.o cxagc.o cxavgchannel.o cxchmodel.o cxequalizezf.o cxmimo_2x2_svd_fp.o cxmimo_2x2_svd.o cxmimoch.o cxmimoeqzf.o cxmimosvd.o dataField.o evm.o FQAM_64map.o fwfft.o ifftofdm54.o ifftofdmsvd.o interlr.o pilot.o prcxmat.o puncture.o rmcpfx.o scramble.o stmat2x4.o stmat4x2.o synchlong.o zdummy.o 
	ranlib libblock.a
