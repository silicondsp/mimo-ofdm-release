<BLOCK>
<LICENSE>

/*    
    Copyright (C) 2001-2016  Silicon DSP Corporation 

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    http://www.silicondsp.com
    Silicon DSP  Corporation
*/

</LICENSE>

<BLOCK_NAME>evm</BLOCK_NAME> 

<COMMENTS>
<![CDATA[ 

/* evm */
/**********************************************************************
                                evm()
***********************************************************************
	inputs:		Two I and Q channels
	outputs:	(optional feed-through of input channels)
	parameters:	int npts, the number of points to plot
			int skip, number of points to skip before first plot
			file fileName,  Results file name 
			file x_axis, the title for the x_axis
			file y_axis, the title for the y_axis
			int	plotQ 0=High, 1,2, ... Marker Type and Low Quality
*************************************************************************
This routine will produce a evm plot of the two input channels.
channels.  Optionally, the input channel data can 'flow through' to the
correspondingly numbered output channel.  This is useful if this block is
to be placed in line in a simulation (e.g. probe).

Programmer: 	Sasan Ardalan
Date: 		8/16/87
Modified:	March 30, 1988 ,(RANobakht)
Modified:	L.J. Faber 1/3/89.  Add flow through; general cleanup.
Modified:	Sasan Ardalan 1/20/89.  dynamic allocation of arrays.
Converted to EVM: Sasan Ardalan November 2006
*/

]]>
</COMMENTS> 

<DESC_SHORT>
Calculate EVM
</DESC_SHORT>

<INCLUDES>
<![CDATA[ 

#include <tcl.h>

]]>
</INCLUDES> 



<DEFINES> 

#define BLOCK_SIZE 1024
#define STATIC 0
#define DYNAMIC 1
#define FLOAT_BUFFER 0
#define COMPLEX_BUFFER 1
#define INTEGER_BUFFER 2

</DEFINES> 

           

<STATES>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>numberInputBuffers</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>numberOutputBuffers</NAME>
	</STATE>
	<STATE>
		<TYPE>float*</TYPE>
		<NAME>xx_P</NAME>
	</STATE>
	<STATE>
		<TYPE>float*</TYPE>
		<NAME>yy_P</NAME>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>count</NAME>
		<VALUE>0</VALUE>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>totalCount</NAME>
		<VALUE>0</VALUE>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>displayed</NAME>
		<VALUE>FALSE</VALUE>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>blockOff</NAME>
		<VALUE>0</VALUE>
	</STATE>
	<STATE>
		<TYPE>int</TYPE>
		<NAME>bufi</NAME>
		<VALUE>0</VALUE>
	</STATE>
	<STATE>
		<TYPE>complex*</TYPE>
		<NAME>idealConstellation_P</NAME>
		<VALUE>0</VALUE>
	</STATE>
	<STATE>
		<TYPE>double</TYPE>
		<NAME>ANormIdeal</NAME>
		<VALUE>0</VALUE>
	</STATE>
</STATES>
 
<DECLARATIONS> 

	int samples;
    	int i,j;
	int operState;
	FILE* file_F;
	complex	val;
	char	fname[100];
	char curveTitle[80];
        double rsq;
        double d,dmin;
        double evm,evmDB;
        double ANorm;
        int index;
        FILE* fp;
        float mag;
	char theVar[100];
	char theName[256];

#ifdef TCL_SUPPORT
        Tcl_Obj *varNameObj_P;
        Tcl_Obj *objVar_P;
#endif
</DECLARATIONS> 

                                 

<PARAMETERS>
<PARAM>
	<DEF>Number of constellation points (power of 2)</DEF>
	<TYPE>int</TYPE>
	<NAME>N</NAME>
	<VALUE>64</VALUE>
</PARAM>
<PARAM>
	<DEF>File with Ideal Constellation</DEF>
	<TYPE>file</TYPE>
	<NAME>idealFile</NAME>
	<VALUE>ideal_constellation.dat</VALUE>
</PARAM>
<PARAM>
	<DEF>Number of points ( dynamic plot window)</DEF>
	<TYPE>int</TYPE>
	<NAME>npts</NAME>
	<VALUE>128</VALUE>
</PARAM>
<PARAM>
	<DEF>Number of points to skip</DEF>
	<TYPE>int</TYPE>
	<NAME>skip</NAME>
	<VALUE>0</VALUE>
</PARAM>
<PARAM>
	<DEF>Title</DEF>
	<TYPE>file</TYPE>
	<NAME>fileName</NAME>
	<VALUE>EVM</VALUE>
</PARAM>
<PARAM>
	<DEF>x Axis</DEF>
	<TYPE>file</TYPE>
	<NAME>x_axis</NAME>
	<VALUE>X</VALUE>
</PARAM>
<PARAM>
	<DEF>y Axis</DEF>
	<TYPE>file</TYPE>
	<NAME>y_axis</NAME>
	<VALUE>Y</VALUE>
</PARAM>
<PARAM>
	<DEF>Plot Style: 1=Line,2=Points,5=Bar Chart</DEF>
	<TYPE>int</TYPE>
	<NAME>plotStyleParam</NAME>
	<VALUE>2</VALUE>
</PARAM>
<PARAM>
	<DEF>Fixed Bounds ( 0=none, 1=fixed)</DEF>
	<TYPE>int</TYPE>
	<NAME>fixed</NAME>
	<VALUE>0</VALUE>
</PARAM>
<PARAM>
	<DEF>Minimum x</DEF>
	<TYPE>float</TYPE>
	<NAME>minx</NAME>
	<VALUE> -1.2</VALUE>
</PARAM>
<PARAM>
	<DEF>Maximum x</DEF>
	<TYPE>float</TYPE>
	<NAME>maxx</NAME>
	<VALUE>  1.2</VALUE>
</PARAM>
<PARAM>
	<DEF>Minimum y</DEF>
	<TYPE>float</TYPE>
	<NAME>miny</NAME>
	<VALUE> -1.2</VALUE>
</PARAM>
<PARAM>
	<DEF>Maximum y</DEF>
	<TYPE>float</TYPE>
	<NAME>maxy</NAME>
	<VALUE>  1.2</VALUE>
</PARAM>
<PARAM>
	<DEF>Marker type:0=dot,1=O,2=+,3=X,4=*,5=square,6=diamond,7=triangle</DEF>
	<TYPE>int</TYPE>
	<NAME>markerType</NAME>
	<VALUE>0</VALUE>
</PARAM>
<PARAM>
	<DEF>Control: 1=On, 0=Off</DEF>
	<TYPE>int</TYPE>
	<NAME>control</NAME>
	<VALUE>1</VALUE>
</PARAM>
<PARAM>
	<DEF>Buffer type:0= Float,1= Complex, 2=Integer</DEF>
	<TYPE>int</TYPE>
	<NAME>bufferType</NAME>
	<VALUE>0</VALUE>
</PARAM>
<PARAM>
	<DEF>0=Static,1=Dynamic</DEF>
	<TYPE>int</TYPE>
	<NAME>mode</NAME>
	<VALUE>0</VALUE>
</PARAM>
<PARAM>
	<DEF>zero threshold</DEF>
	<TYPE>float</TYPE>
	<NAME>zeroMag</NAME>
	<VALUE>0.01</VALUE>
</PARAM>



</PARAMETERS>

<INIT_CODE>
<![CDATA[ 

	/* 
	 * store as state the number of input/output buffers 
 	 */
	if((numberInputBuffers = NO_INPUT_BUFFERS()) <= 0) {
		fprintf(stderr,"evm: no inputs connected\n");
		return(2);
	}
	if((numberOutputBuffers = NO_OUTPUT_BUFFERS()) > numberInputBuffers) {
		fprintf(stderr,"evm: too many outputs connected\n");
		return(3);
	}
	if(numberInputBuffers > 2) {
		fprintf(stderr,"evm: too many inputs connected\n");
		return(3);
	}


        fp=fopen(idealFile,"r");
        if(!fp) {
		fprintf(stderr,"evm: Could not open ideal constellation file:%s\n",idealFile);
		return(9);
        }
        idealConstellation_P=(complex*)calloc(N,sizeof(complex));
        if(!idealConstellation_P) {
		fprintf(stderr,"evm: Could not alloate space for ideal constellation \n");
		return(10);
 
        }
        ANormIdeal=0.0;
        for(i=0; i<N; i++) {
                fscanf(fp,"%f %f",&idealConstellation_P[i].re,&idealConstellation_P[i].im);
                //fprintf(stdout,"%d\t%f\t %f  \n",i,idealConstellation_P[i].re,idealConstellation_P[i].im);
                rsq=idealConstellation_P[i].re*idealConstellation_P[i].re+idealConstellation_P[i].im*idealConstellation_P[i].im;
                ANormIdeal += rsq;
        }
        ANormIdeal=sqrt((float)N/ANormIdeal);
        fprintf(stdout,"ANormIdeal=%f\n",ANormIdeal);
        
       for(i=0; i<N; i++) {

                idealConstellation_P[i].re=idealConstellation_P[i].re*ANormIdeal;
                idealConstellation_P[i].im=idealConstellation_P[i].im*ANormIdeal;

        }


	if(control && mode == DYNAMIC) {
		/*
		 * allocate arrays
		 */
		xx_P = (float* )calloc(npts,sizeof(float));
		if(xx_P == NULL) {
			fprintf(stderr,"Could not allocate space in evm\n");
			return(4);
		}
		yy_P = (float* )calloc(npts,sizeof(float));
		if(yy_P == NULL) {
			fprintf(stderr,"Could not allocate space in evm\n");
			return(5);
		}
	} else if(control && mode == STATIC) {
		/*
		 * allocate arrays
		 */
		xx_P = (float* )calloc(BLOCK_SIZE,sizeof(float));
		if(xx_P == NULL) {
			fprintf(stderr,"Could not allocate space in evm\n");
			return(4);
		}
		yy_P = (float* )calloc(BLOCK_SIZE,sizeof(float));
		if(yy_P == NULL) {
			fprintf(stderr,"Could not allocate space in evm\n");
			return(4);
		}
	}
    	count = 0;
	totalCount = 0;
	switch(bufferType) {
		case COMPLEX_BUFFER: 
			SET_CELL_SIZE_IN(0,sizeof(complex));
			if(numberOutputBuffers == 1)
				SET_CELL_SIZE_IN(0,sizeof(complex));
			break;
		case FLOAT_BUFFER: 
			if(numberInputBuffers == 1) {
				SET_CELL_SIZE_IN(0,sizeof(float));
				if(numberOutputBuffers == 1)
				   SET_CELL_SIZE_OUT(0,sizeof(float));
			}
			else {
				SET_CELL_SIZE_IN(0,sizeof(float));
				SET_CELL_SIZE_IN(1,sizeof(float));
				if(numberOutputBuffers == 2) {
				   SET_CELL_SIZE_OUT(0,sizeof(float));
				   SET_CELL_SIZE_OUT(1,sizeof(float));
				}
			}
			break;
		case INTEGER_BUFFER: 
			if(numberInputBuffers == 1) {
				SET_CELL_SIZE_IN(0,sizeof(int));
				if(numberOutputBuffers == 1)
				   SET_CELL_SIZE_OUT(0,sizeof(int));
			}
			else {
				SET_CELL_SIZE_IN(0,sizeof(int));
				SET_CELL_SIZE_IN(1,sizeof(int));
				if(numberOutputBuffers == 2) {
				    SET_CELL_SIZE_OUT(0,sizeof(int));
				    SET_CELL_SIZE_OUT(1,sizeof(int));
				}
			}
			break;
		default: 
			fprintf(stderr,"Bad buffer type specified in evm \n");
			return(5);
			break;
	}

]]>
</INIT_CODE> 


<MAIN_CODE>
<![CDATA[ 


	for(samples = MIN_AVAIL(); samples > 0; --samples) {




		   for(i=0; i<numberInputBuffers; ++i) {
	   		IT_IN(i);
			if(numberOutputBuffers > i) {
				if(IT_OUT(i)) {
					KrnOverflow("evm",i);
					return(99);
				}
				switch(bufferType) {
					case COMPLEX_BUFFER:
	 					OUTCX(i,0) = INCX(i,0);
						break;
					case INTEGER_BUFFER:
	 					OUTI(i,0) = INI(i,0);
						break;
					case FLOAT_BUFFER:
	 					OUTF(i,0) = INF(i,0);
						break;
				}
			}
	        }

		if(++totalCount > skip && control) {
                	if(mode == STATIC) 
				count = blockOff + bufi;
			bufi++;
		if (bufi == BLOCK_SIZE && mode==STATIC) {
			blockOff += BLOCK_SIZE;
			xx_P = (float *)realloc((char *) xx_P,
				sizeof(float) * (blockOff + BLOCK_SIZE));
			if(xx_P==NULL)
			{
				fprintf(stderr,"Could not allocate space in evm \n");
				return(7);
			}
			yy_P = (float *)realloc((char *) yy_P,
				sizeof(float) * (blockOff + BLOCK_SIZE));
			if(yy_P==NULL)
			{
				fprintf(stderr,"Could not allocate space in evm \n");
				return(7);
			}
			bufi=0;

		}

			switch(bufferType) {
				case COMPLEX_BUFFER:
					val=INCX(0,0);
           				yy_P[count] = val.im;
					xx_P[count] = val.re;
					break;
				case FLOAT_BUFFER:
           			if(numberInputBuffers==2)
					        yy_P[count] = INF(1,0);
					xx_P[count] = INF(0,0);
					break;
				case INTEGER_BUFFER:
           			if(numberInputBuffers==2)
						yy_P[count] = (float)INI(1,0);
					xx_P[count] = (float)INI(0,0);
					break;
			}
			if(mode == DYNAMIC)
					count++;
		}
	}

	return(0);


]]>
</MAIN_CODE> 

<WRAPUP_CODE>
<![CDATA[ 

if(control == 0) return(0);
if((totalCount - skip) > 0 ) {
     {
          //      strcpy(fname,title);
         //       strcat(fname,".sct");

                file_F = fopen(fileName,"w");
                printf("EVM File Name=%s\n",fileName);
                ANorm=0;
                j=0;
                for(i=0; i<count; i++) {
                         
                        
                        
                       
                        rsq=xx_P[i]*xx_P[i]+yy_P[i]*yy_P[i];
                        if(rsq < zeroMag) continue;
                        ANorm += rsq;
                        j++;

                }
                ANorm=sqrt((float)j/ANorm);
                for(i=0; i<count; i++) {
                        xx_P[i]=xx_P[i]*ANorm;
                        yy_P[i]=yy_P[i]*ANorm;

                        // fprintf(file_F,"%e %e\n",xx_P[i],yy_P[i]);
 
                }		
               // index_P=(int*)calloc(count,sizeof(int));
                evm=0.0;
                for(i=0; i<count; i++) {

                        mag=sqrt(xx_P[i]*xx_P[i]+yy_P[i]*yy_P[i]);
                        
                        if(mag < zeroMag) continue;

                        dmin=1e22;
                        index=0;
                        for(j=0; j<N; j++) {
                             d=(xx_P[i]-idealConstellation_P[j].re)*(xx_P[i]-idealConstellation_P[j].re)+(yy_P[i]-idealConstellation_P[j].im)*(yy_P[i]-idealConstellation_P[j].im);
                             if(d< dmin) {
                                  dmin=d;
                                  index=j;
                             }
                         }
                 //        index_P[i]=index;
                         evm += dmin;
                        dmin=sqrt(dmin);

                        fprintf(file_F,"EVM %d\t%d\t%f\t%f\t%f\n",i,index,xx_P[i],yy_P[i], (float)dmin);
 
                }                
                fprintf(stderr,"evm created file: %s \n",fileName);
		fclose(file_F);

                evm=evm/(float)count;
                evmDB=10.0*log10(evm);
                printf("EVM=%f\tEVM_DB=%f\n",evm,evmDB );
#ifdef TCL_SUPPORT
       if(!krn_TCL_Interp) {
          
	  return(0);
       }
       
       sprintf(theName,"%s_evm",STAR_NAME);

	varNameObj_P=Tcl_NewStringObj(theName, strlen(theName));
	objVar_P=Tcl_NewObj();
	Tcl_SetDoubleObj(objVar_P,evm);
	Tcl_ObjSetVar2(krn_TCL_Interp,varNameObj_P,NULL,objVar_P,TCL_NAMESPACE_ONLY);
        sprintf(theName,"%s_evmDB",STAR_NAME);

	varNameObj_P=Tcl_NewStringObj(theName, strlen(theName));
	objVar_P=Tcl_NewObj();
	Tcl_SetDoubleObj(objVar_P,evmDB);
	Tcl_ObjSetVar2(krn_TCL_Interp,varNameObj_P,NULL,objVar_P,TCL_NAMESPACE_ONLY);
#endif


		free(xx_P);
		free(yy_P);
      }
}

]]>
</WRAPUP_CODE> 



</BLOCK> 

