 
#ifdef LICENSE


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


#endif
 
#ifdef SHORT_DESCRIPTION

Calculate EVM

#endif
 
#ifdef PROGRAMMERS

#endif






#include <stdio.h>
#include <math.h>

/* Note: these paths are installation dependent! */
#include <capsim.h>
#include <stars.h>



 

#include <tcl.h>


 

#define BLOCK_SIZE 1024
#define STATIC 0
#define DYNAMIC 1
#define FLOAT_BUFFER 0
#define COMPLEX_BUFFER 1
#define INTEGER_BUFFER 2


/*
 *           STATES STRUCTURE 
 */ 
typedef struct {
      int  __numberInputBuffers;
      int  __numberOutputBuffers;
      float*  __xx_P;
      float*  __yy_P;
      int  __count;
      int  __totalCount;
      int  __displayed;
      int  __blockOff;
      int  __bufi;
      complex*  __idealConstellation_P;
      double  __ANormIdeal;
     } state_t,*state_Pt;

/*
 *         STATE DEFINES 
 */ 
#define numberInputBuffers (state_P->__numberInputBuffers)
#define numberOutputBuffers (state_P->__numberOutputBuffers)
#define xx_P (state_P->__xx_P)
#define yy_P (state_P->__yy_P)
#define count (state_P->__count)
#define totalCount (state_P->__totalCount)
#define displayed (state_P->__displayed)
#define blockOff (state_P->__blockOff)
#define bufi (state_P->__bufi)
#define idealConstellation_P (state_P->__idealConstellation_P)
#define ANormIdeal (state_P->__ANormIdeal)

/*         
 *    PARAMETER DEFINES 
 */ 
#define N (param_P[0]->value.d)
#define idealFile (param_P[1]->value.s)
#define npts (param_P[2]->value.d)
#define skip (param_P[3]->value.d)
#define fileName (param_P[4]->value.s)
#define x_axis (param_P[5]->value.s)
#define y_axis (param_P[6]->value.s)
#define plotStyleParam (param_P[7]->value.d)
#define fixed (param_P[8]->value.d)
#define minx (param_P[9]->value.f)
#define maxx (param_P[10]->value.f)
#define miny (param_P[11]->value.f)
#define maxy (param_P[12]->value.f)
#define markerType (param_P[13]->value.d)
#define control (param_P[14]->value.d)
#define bufferType (param_P[15]->value.d)
#define mode (param_P[16]->value.d)
#define zeroMag (param_P[17]->value.f)
/*-------------- BLOCK CODE ---------------*/
 int  evm(int run_state,block_Pt block_P)

{
	param_Pt *param_P = block_P->param_AP;
	star_Pt star_P = block_P->star_P;

     
	state_Pt state_P = (state_Pt)star_P->state_P;
     
/*
 *              Declarations 
 */
 

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

switch (run_state) {

 
 


 
case PARAM_INIT: 
    {
      int indexModel88 = block_P->model_index;
     char   *pdef0 = "Number of constellation points (power of 2)";
     char   *ptype0 = "int";
     char   *pval0 = "64";
     char   *pname0 = "N";
     char   *pdef1 = "File with Ideal Constellation";
     char   *ptype1 = "file";
     char   *pval1 = "ideal_constellation.dat";
     char   *pname1 = "idealFile";
     char   *pdef2 = "Number of points ( dynamic plot window)";
     char   *ptype2 = "int";
     char   *pval2 = "128";
     char   *pname2 = "npts";
     char   *pdef3 = "Number of points to skip";
     char   *ptype3 = "int";
     char   *pval3 = "0";
     char   *pname3 = "skip";
     char   *pdef4 = "Title";
     char   *ptype4 = "file";
     char   *pval4 = "EVM";
     char   *pname4 = "fileName";
     char   *pdef5 = "x Axis";
     char   *ptype5 = "file";
     char   *pval5 = "X";
     char   *pname5 = "x_axis";
     char   *pdef6 = "y Axis";
     char   *ptype6 = "file";
     char   *pval6 = "Y";
     char   *pname6 = "y_axis";
     char   *pdef7 = "Plot Style: 1=Line,2=Points,5=Bar Chart";
     char   *ptype7 = "int";
     char   *pval7 = "2";
     char   *pname7 = "plotStyleParam";
     char   *pdef8 = "Fixed Bounds ( 0=none, 1=fixed)";
     char   *ptype8 = "int";
     char   *pval8 = "0";
     char   *pname8 = "fixed";
     char   *pdef9 = "Minimum x";
     char   *ptype9 = "float";
     char   *pval9 = "-1.2";
     char   *pname9 = "minx";
     char   *pdef10 = "Maximum x";
     char   *ptype10 = "float";
     char   *pval10 = "1.2";
     char   *pname10 = "maxx";
     char   *pdef11 = "Minimum y";
     char   *ptype11 = "float";
     char   *pval11 = "-1.2";
     char   *pname11 = "miny";
     char   *pdef12 = "Maximum y";
     char   *ptype12 = "float";
     char   *pval12 = "1.2";
     char   *pname12 = "maxy";
     char   *pdef13 = "Marker type:0=dot,1=O,2=+,3=X,4=*,5=square,6=diamond,7=triangle";
     char   *ptype13 = "int";
     char   *pval13 = "0";
     char   *pname13 = "markerType";
     char   *pdef14 = "Control: 1=On, 0=Off";
     char   *ptype14 = "int";
     char   *pval14 = "1";
     char   *pname14 = "control";
     char   *pdef15 = "Buffer type:0= Float,1= Complex, 2=Integer";
     char   *ptype15 = "int";
     char   *pval15 = "0";
     char   *pname15 = "bufferType";
     char   *pdef16 = "0=Static,1=Dynamic";
     char   *ptype16 = "int";
     char   *pval16 = "0";
     char   *pname16 = "mode";
     char   *pdef17 = "zero threshold";
     char   *ptype17 = "float";
     char   *pval17 = "0.01";
     char   *pname17 = "zeroMag";
KrnModelParam(indexModel88,0 ,pdef0,ptype0,pval0,pname0);
KrnModelParam(indexModel88,1 ,pdef1,ptype1,pval1,pname1);
KrnModelParam(indexModel88,2 ,pdef2,ptype2,pval2,pname2);
KrnModelParam(indexModel88,3 ,pdef3,ptype3,pval3,pname3);
KrnModelParam(indexModel88,4 ,pdef4,ptype4,pval4,pname4);
KrnModelParam(indexModel88,5 ,pdef5,ptype5,pval5,pname5);
KrnModelParam(indexModel88,6 ,pdef6,ptype6,pval6,pname6);
KrnModelParam(indexModel88,7 ,pdef7,ptype7,pval7,pname7);
KrnModelParam(indexModel88,8 ,pdef8,ptype8,pval8,pname8);
KrnModelParam(indexModel88,9 ,pdef9,ptype9,pval9,pname9);
KrnModelParam(indexModel88,10 ,pdef10,ptype10,pval10,pname10);
KrnModelParam(indexModel88,11 ,pdef11,ptype11,pval11,pname11);
KrnModelParam(indexModel88,12 ,pdef12,ptype12,pval12,pname12);
KrnModelParam(indexModel88,13 ,pdef13,ptype13,pval13,pname13);
KrnModelParam(indexModel88,14 ,pdef14,ptype14,pval14,pname14);
KrnModelParam(indexModel88,15 ,pdef15,ptype15,pval15,pname15);
KrnModelParam(indexModel88,16 ,pdef16,ptype16,pval16,pname16);
KrnModelParam(indexModel88,17 ,pdef17,ptype17,pval17,pname17);

      }
break;
   


/*
 *        SYSTEM INITIALIZATION CODE 
 */
case SYSTEM_INIT:
     
	star_P->state_P = (char*)calloc(1,sizeof(state_t));
	state_P = (state_Pt)star_P->state_P;
            count=0;
       totalCount=0;
       displayed=FALSE;
       blockOff=0;
       bufi=0;
       idealConstellation_P=0;
       ANormIdeal=0;

break;

/*
 *               USER INITIALIZATION CODE 
 */
case USER_INIT: 

 

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


break;

/* 
 *             MAIN CODE 
 */
case MAIN_CODE: 

 


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



break;

/*             
 *            WRAPUP CODE 
 */
case WRAPUP: 

 

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


break;
}
return(0);
}
