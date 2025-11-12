 #
#	Makefile for libsub.a
#	  ljfaber 7/88



CFLAGS = -I../include -I$(CAPSIM)/include  -I$(CAPSIM)/include/TCL

 
libsubs.a : *.c
	gcc -c -g  $(CFLAGS) $?
	ar rv libsubs.a  *.o
	ranlib libsubs.a

	

