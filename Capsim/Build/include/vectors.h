//#include "dsp_cx.h"
//


/*  Capsim (r) Text Mode Kernel (TMK) Blocks Library 
    Copyright (C) 2002-2017   Silicon DSP  Corporation

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    http://www.silicondsp.com
*/


#define VECTOR_TYPE_NAME "mvrcx"
#define IIP_TYPE_NAME "iip"


#define KRN_TCL_TYPE_SHORT_VECTOR 0
#define KRN_TCL_TYPE_BYTE_VECTOR 1
#define KRN_TCL_TYPE_REAL_VECTOR 2
#define KRN_TCL_TYPE_COMPLEX_VECTOR 3
#define KRN_TCL_TYPE_REAL_MATRIX  4
#define KRN_TCL_TYPE_COMPLEX_MATRIX  5
#define KRN_TCL_TYPE_COMPLEX_SCALAR  6
#define KRN_TCL_TYPE_CAP_CPX_MATRIX 7

typedef struct {
                double   re, im;
} cx_t;


typedef struct {
                float   re, im;
} cxFloat_t;


typedef struct {
                double   re, im;
} complex;

 

typedef struct short_type {
        short   type;
        int     length;
        short   *vector_P;
} shortVector_t, *shortVector_Pt;

typedef struct short_vector {
        short   type;
} short_t, *short_Pt;

typedef struct byte_vector {
        short   type;
        int     length;
        unsigned char   *vector_P;
} byteVector_t, *byteVector_Pt;

typedef struct double_vector {
        short   type;
	short   transpose;
        int     length;
        double   *vector_P;
} doubleVector_t, *doubleVector_Pt;

typedef struct doublecx_vector {
        short   type;
	short   transpose;
        int     length;
        cx_t   *vector_P;
} cxVector_t, *cxVector_Pt;



typedef struct {
                short   type;
                int     width;
                int     height;

                double   **matrix_PP;
} dsp_Matrix_t, *dsp_Matrix_Pt;


typedef struct {
                int     width;
                int     height;

                float   **matrix_PP;
} dsp_floatMatrix_t, *dsp_floatMatrix_Pt;


typedef struct {
                short   type;
                int     width;
                int     height;

                cx_t   **matrix_PP;
} dsp_cxMatrix_t, *dsp_cxMatrix_Pt;


typedef struct complex_scalar {
        short   type;
        cx_t   value;
} cxScalar_t, *cxScalar_Pt;



#if 0000
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef short INT16;
typedef unsigned char boolean;
typedef long int INT32;
#endif

cx_t Dsp_Cx_Complex(double a, double b);
cx_t Dsp_Cx_Add( cx_t x, cx_t y);
cx_t Dsp_Cx_Sub(cx_t x, cx_t y);
cx_t Dsp_Cx_Mult(cx_t x, cx_t y);
cx_t Dsp_Cx_Div(cx_t x,  cx_t y);
cx_t Dsp_Cx_Exp( cx_t x);
cx_t Dsp_Cx_Tanh(cx_t x);
cx_t Dsp_Cx_Sqrt(cx_t x);


extern Tcl_ObjType *krn_vecObjType_P;
extern Tcl_ObjType *krn_iipObjType_P;

short_t *Krn_GetPtr(Tcl_Obj *obj_P);
void VectorRegisterTypes(Tcl_Interp *interp );
void IIPRegisterTypes(Tcl_Interp *interp );
int Krn_VectorFromString(Tcl_Interp *interp, Tcl_Obj *obj_P);


int Krn_VectorFromFile(Tcl_Interp *interp,Tcl_Obj *obj_P,char *fileName,int nolen);
int Krn_MatrixFromFile(Tcl_Interp *interp,Tcl_Obj *obj_P,char *fileName);
int Krn_CxMatrixFromFile(Tcl_Interp *interp,Tcl_Obj *obj_P,char *fileName);
int Krn_CxVectorFromFile(Tcl_Interp *interp,Tcl_Obj *obj_P,char *fileName, int nolen);


void Krn_StringFromObject(Tcl_Obj *obj_P);
doubleVector_t *Krn_GetVector(Tcl_Obj *resultPtr);
dsp_Matrix_t *Krn_GetMatrix(Tcl_Obj *obj_P);
cxScalar_t *Krn_GetCxScalar(Tcl_Obj *obj_P);

int Krn_MatrixFromString(Tcl_Interp *interp, Tcl_Obj *obj_P);

cxVector_t *Krn_GetCxVector(Tcl_Obj *obj_P);
int Krn_CxMatrixFromString(Tcl_Interp *interp, Tcl_Obj *obj_P);


int
VectorObjPrintCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int
VectorObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

		int
VectorObjPlotCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int MatrixObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixObjPrintCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorCxObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int VectorCxObjPrintCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int CxMatrixObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CxMatrixObjPrintCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int MatrixObjSVDCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int MatrixObjEigenCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixObjHermitianCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int MatrixObjMultiplyCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixObjQRCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int DiagonalCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ReadVectorObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int ReadMatrixObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int ReadCxVectorObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int ReadCxMatrixObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int MatrixObjDisplayCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int InverseComplex(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int InverseReal(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int QRComplex(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixCreate(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixCreateComplex(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int SetMatrixElementReal(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int GetMatrixElementReal(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int GetVectorElementReal(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int SetVectorElementReal(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorCreate(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorComplexCreate(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjDotProductCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

//int ScalarComplexObjCmd(ClientData clientData, Tcl_Interp *interp,
//		int objc, Tcl_Obj *CONST objv[]);

 int ScalarComplexObjCmd(ClientData clientData, Tcl_Interp *interp,
 		int objc, char * objv[]);


int ScalarComplexDuplicateObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ScalarComplexConjugateObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ScalarComplexExtractObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ScalarComplexSqrtObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ScalarComplexTanhObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ScalarComplexExpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ScalarComplexDivObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int ScalarComplexSubObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ScalarComplexAddObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ScalarComplexMultObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int SetVectorElementComplex(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int GetVectorElementComplex(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixObjEdgeDetectionCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixObjFilterCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int MatrixObjForwardFFTCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixObjInverseFFTCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorInverseFFT(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorFFT(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjSAXPYtCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjGAXPYtCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjConvolveCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixObjInverseCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixObjExtractVectorCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixObjExtractSubMatrixCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixOuterProductUpdateCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjExtractSubVectorCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int MatrixLinearSystemAxEqBUpdateCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int ScalarComplexPolarObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ScalarComplexFromPolarObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveObjInfoCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int CurveFromFileDoubleColumnCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int CurveMarkerItemCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurvePenItemCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

//COMMAND_SYNT newsmithchart  name
int VectorObjNewSmithChartCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);




int CurveFromFileSingleColumnCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveSetFixedBoundsCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveSetYAxisLogCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveSetXAxisLogCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveHideAllCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveShowAllCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveSetGridOffCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveSetGridOnCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveSetXLabelCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveSetYLabelCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveSetSubTitleCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveSetTitleCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveNewCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveCircCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveRectCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveInfoItemCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveErrorBarCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveLineCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveTextItemCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
int CurveFromComplexVectorCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveScatterFromComplexVectorCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ReadTiffImageObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int SetColorMapFromMatrix(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int
CreateTiffFromMatrix(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int  MatrixLinearSystemUpdateCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);
//+++++++++ Transmission Line Commands   +++++++++++++/
int Trc_ScalarComplexPolarObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_ScalarComplexFromPolarObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_LoadTopologyCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_PrintTopologyCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int Trc_CalcTopologyCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_NodeInfoCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int Trc_NodeCalcValuesCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_NodeZ0GammaCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_ScalarComplexInverseObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_ScalarComplexZParallelObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int Trc_NetImpulseResponseCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_NetLineLengthCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_NodeSetRLCGCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_NodeSetLengthCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_NodeGetRLCGCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_NodeGetLengthCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int Trc_VSWRObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int Trc_ScalarComplexReflectionCoefficientObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjPlotPolarCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


int Trc_THelpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_VHelpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Trc_CXHelpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

//+++++++++ End Transmission Line Commands   +++++++++++++/


//++SmithChart               +++++++++++++
int VectorObjPlotSmithChartCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


//+++++++++++++++++

void Krn_PrintCxVector(cxVector_t *vec_P,char format[], FILE *fp, int twocol) ;
void Krn_PrintVector(doubleVector_t *vec_P,char format[], FILE *fp, int nolen) ;

Tcl_Obj  *IIP_PlotFromVector(Tcl_Interp *interp,doubleVector_t *vec_P,char *varCurveName, int varCurveNameLength);

int Krn_CxVectorFromString(Tcl_Interp *interp, Tcl_Obj *obj_P);


int Krn_VHelpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Krn_CXHelpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Krn_MatrixHelpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Krn_CurveHelpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Krn_HelpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Krn_CapsimHelpObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjSpectrogramCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int ReadAIFFObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjWriteAIFFCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjLPCCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjCepstrumCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjSLPCCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int VectorObjSCepstrumCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

  //COMMAND_SYNT
int Krn_DeleteStackedCurvesObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int Krn_DeleteAllCurvesObjCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveRedrawCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveFixXCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveFixYCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveSciYCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveSciXCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveSetHeightWidthCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);

int CurveSetScreenXYCmd(ClientData clientData, Tcl_Interp *interp,
		int objc, Tcl_Obj *CONST objv[]);


//CurveSetScreenXYCmd crvsetscreenloc
//CurveSetHeightWidthCmd  crvsetwh




void Krn_PrintCxMatrix(dsp_cxMatrix_t *mat_P,char format[], FILE *fp);
void Krn_PrintMatrix(dsp_Matrix_t *mat_P,char format[], FILE *fp);
void Krn_PrintComplexScalar(cxScalar_t *x_P,char format[], FILE *fp);



dsp_cxMatrix_t *Krn_GetCxMatrix(Tcl_Obj *obj_P);
int Krn_ComputeSVDRealMatrix(dsp_Matrix_t *mat_P, doubleVector_t *ss_P,dsp_Matrix_t *u_P, dsp_Matrix_t *v_P);
int Krn_ComputeSVDCxMatrix(dsp_cxMatrix_t *mat_P, doubleVector_t *ss_P,dsp_cxMatrix_t *u_P, dsp_cxMatrix_t *v_P);

doubleVector_t* Dsp_AllocateVector(int length);
cxVector_t* Dsp_AllocateCxVector(int length);
dsp_Matrix_Pt Dsp_AllocateRealMatrix(int width,int height);
dsp_cxMatrix_Pt Dsp_AllocateCxMatrix(int width,int height);

int Krn_ComputeEigenvalueRealMatrix(dsp_Matrix_t *mat_P,cxVector_t *e_P,dsp_Matrix_t *vl_P,dsp_Matrix_t *vr_P );
int Krn_ComputeEigenvalueComplexMatrix(dsp_cxMatrix_t *mat_P,cxVector_t *e_P,dsp_cxMatrix_t *vl_P,dsp_cxMatrix_t *vr_P );

void Krn_TransposeRealMatrix(dsp_Matrix_t *mat_P);
int Dsp_CopyRealMatrix(dsp_Matrix_t *mat_P,dsp_Matrix_t *dup_P);
void Dsp_MultiplyRealMatrices(dsp_Matrix_t *a_P,dsp_Matrix_t *b_P,dsp_Matrix_t *c_P);
void Dsp_MultiplyComplexMatrices(dsp_cxMatrix_t *a_P,dsp_cxMatrix_t *b_P,dsp_cxMatrix_t *c_P);
int Dsp_CopyComplexMatrix(dsp_cxMatrix_t *mat_P,dsp_cxMatrix_t *dup_P);
void Krn_TransposeConjugateMatrix(dsp_cxMatrix_t *mat_P) ;
void Krn_TransposeConjugateMatrix(dsp_cxMatrix_t *mat_P);

void Dsp_MultiplyRealVectorRealMatrices(doubleVector_t *va_P,dsp_Matrix_t *br_P,doubleVector_t *vc_P);
void Dsp_MultiplyRealMatrixRealVector(dsp_Matrix_t *ar_P,doubleVector_t *vb_P,doubleVector_t *vc_P);
void Dsp_MultiplyComplexMatricesComplexVector(dsp_cxMatrix_t *a_P,cxVector_t *vbx_P,cxVector_t *vcx_P);
void Dsp_MultiplyComplexMatricesRealVector(dsp_cxMatrix_t *a_P,doubleVector_t*vb_P,cxVector_t *vcx_P);
void Dsp_MultiplyComplexVectorComplexMatrices(cxVector_t*vax_P,dsp_cxMatrix_t *b_P,cxVector_t *vcx_P);
void Dsp_MultiplyRealVectorComplexMatrices(doubleVector_t *va_P,dsp_cxMatrix_t *b_P,cxVector_t *vcx_P);
void Dsp_MultiplyRealMatrixComplexMatrices(dsp_Matrix_t *ar_P,dsp_cxMatrix_t *b_P,dsp_cxMatrix_t *c_P);
void Dsp_MultiplyComplexMatrixRealMatrices(dsp_cxMatrix_t *a_P,dsp_Matrix_t *br_P,dsp_cxMatrix_t *c_P);
int Krn_ComputeInverseCxMatrix(dsp_cxMatrix_t *mat_P, dsp_cxMatrix_t *inverse_P);
int Krn_ComputeInverseRealMatrix(dsp_Matrix_t *mat_P, dsp_Matrix_t *inverse_P);
int Krn_ComputeQRCxMatrix(dsp_cxMatrix_t *mat_P,dsp_cxMatrix_t *Q_P, dsp_cxMatrix_t *R_P);

int Dsp_GenGaussMatrix(dsp_Matrix_t *mat_P,float std,float mean, long seedIn);
int Dsp_GenGaussComplexMatrix(dsp_cxMatrix_t *mat_P,float std,float mean, long seedIn);
int Dsp_GenGaussComplexVector(cxVector_t *vec_P,float std,float mean, long seedIn);
int Dsp_GenGaussVector(doubleVector_t *vec_P,float std,float mean, long seedIn);
int Dsp_DotComplexComplex(cxVector_t * x, cxVector_t *y, cxScalar_t *z);
int Dsp_DotRealReal(doubleVector_t * x, doubleVector_t *y, double *z);


int Krn_InitRegExp(Tcl_Interp *interp);


dsp_Matrix_t  *Dsp_ConvolveRealMatrices(dsp_Matrix_t *matrix_P,dsp_Matrix_t *kernel_P);
void  Dsp_FreeRealMatrix(dsp_Matrix_t *matrix_P);
dsp_Matrix_Pt  Dsp_EdgeDetectionMatrix(dsp_Matrix_t *matrix_P);
 dsp_cxMatrix_t  *Dsp_MatrixForwardFFT(dsp_Matrix_t *matrix_P,float* window_P,int length,int centerFlag);
  dsp_Matrix_t  *Dsp_MatrixInverseFFT(dsp_cxMatrix_t *matrix_P,int length);
 doubleVector_t  *Dsp_VectorInverseFFT(cxVector_t *vec_P);
 cxVector_t  *Dsp_VectorFFT(doubleVector_t *vec_P);
int Dsp_SAXPYComplex(cxVector_t *vx_P,cxVector_t *vy_P,cxScalar_t *alpha);
int Dsp_SAXPYReal(doubleVector_t *vx_P,doubleVector_t *vy_P,double alpha);
int Dsp_GAXPYComplex(cxVector_t *vx_P,cxVector_t *vy_P,dsp_cxMatrix_t *A_P);
int Dsp_GAXPYReal(doubleVector_t *vx_P,doubleVector_t *vy_P,dsp_Matrix_t *A_P);

int Dsp_MOPUComplex(cxVector_t *vx_P,cxVector_t *vy_P,dsp_cxMatrix_t *A_P);
int Dsp_MOPUReal(doubleVector_t *vx_P,doubleVector_t *vy_P,dsp_Matrix_t *A_P);


int Dsp_ConvolveReal(doubleVector_t *vx_P,doubleVector_t *vf_P,doubleVector_t *vy_P);
int Dsp_ConvolveComplex(cxVector_t *vx_P,cxVector_t *vf_P,cxVector_t *vy_P);

int IIP_CurveTCLObjInfo(Tcl_Obj  *obj_P);



int IIP_CurveTCLObjSetXAxisLog(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjSetYAxisLog(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjSetXAxisLinear(Tcl_Obj  *obj_P,int format,int width,int ticks);
int IIP_CurveTCLObjSetYAxisLinear(Tcl_Obj  *obj_P,int format,int width,int ticks);
int IIP_CurveTCLObjSetFixedBounds(Tcl_Obj  *obj_P,double xMin,double xMax,double yMin,double yMax);
int IIP_CurveTCLObjSetAuto(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjSetGridOff(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjSetGridOn(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjSetMarker(Tcl_Obj  *obj_P, int style);
int IIP_CurveTCLObjSetLineStyle(Tcl_Obj  *obj_P, int style);
int IIP_CurveTCLObjSetStyle(Tcl_Obj  *obj_P, int style);
int IIP_CurveTCLObjSetZLabel(Tcl_Obj  *obj_P, char *zLabel);
int IIP_CurveTCLObjSetYLabel(Tcl_Obj  *obj_P, char *yLabel);
int IIP_CurveTCLObjSetXLabel(Tcl_Obj  *obj_P, char *xLabel);
int IIP_CurveTCLObjSetSubTitle(Tcl_Obj  *obj_P, char *subTitle);
int IIP_CurveTCLObjSetTitle(Tcl_Obj  *obj_P, char *title);
Tcl_Obj  *IIP_PlotFromFilePolarChart(Tcl_Interp *interp,char *fileName,int mode,int rectPolarFlag,int numLabels,
		int numRadials,int symbol,int numSymbols, double rmin,double rmax);
Tcl_Obj  *IIP_PlotFromFileDoubleColumn(Tcl_Interp *interp,char *fileName);
Tcl_Obj  *IIP_PlotFromFileSingleColumn(Tcl_Interp *interp,char *fileName);
int IIP_CurveTCLObjSetMargins(Tcl_Obj  *obj_P, int left,int right,int top,int bottom);
int IIP_CurveTCLObjSetTextFont(Tcl_Obj  *obj_P, int textItem,int font,int style,int size,int alignmnt);
int IIP_CurveTCLObjSetColor(Tcl_Obj  *obj_P, int item, int color);
int IIP_CurveTCLObjShowAll(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjHideAll(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjShowRightYAxis(Tcl_Obj  *obj_P, int flag);
int IIP_CurveTCLObjShowTopXAxis(Tcl_Obj  *obj_P, int flag);
int IIP_CurveTCLObjShowXAxis(Tcl_Obj  *obj_P, int flag);
int IIP_CurveTCLObjShowYAxis(Tcl_Obj  *obj_P, int flag);
int  IIP_CurveTCLObjErrorBar(Tcl_Obj *obj_P,double x,double y,double width,double height, int color);
int  IIP_CurveTCLObjCircle(Tcl_Obj *obj_P,double x,double y,double radius,int color,int flag,int fill);
int  IIP_CurveTCLObjRectangle(Tcl_Obj *obj_P,double x,double y,double xx,double yy,double  width,double height, int color,int flag,int fill);
int  IIP_CurveTCLObjArrow(Tcl_Obj  *obj_P,double x,double y,double xx,double yy,int color,int arrowFlag,char *text);
double IIP_CurveTCLObjGetSamplingRate(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjSetXAxisLabel(Tcl_Obj  *obj_P,char *xLabel);
int IIP_CurveTCLObjHideAxis(Tcl_Obj  *obj_P);
Tcl_Obj  *IIP_NewCurveObject(Tcl_Interp *interp,char *title);
int  IIP_CurveTCLObjInfoItem(Tcl_Obj *obj_P,char *text, int arrowFlag, double xb,double yb,double xe,double ye);
int  IIP_CurveTCLObjTextItem(Tcl_Obj *obj_P,float x,float y,int color,char *text);
int  IIP_CurveTCLObjLineItem(Tcl_Obj *obj_P,float x,float y,float xx,float yy,int color);
Tcl_Obj *IIP_CreateComplexCurveFromComplexVector(Tcl_Interp *interp,Tcl_Obj *obj_P);
Tcl_Obj *IIP_CreateScatterCurveFromComplexVector(Tcl_Interp *interp,Tcl_Obj *obj_P, int markerType, int plotStyle);
cxVector_t *Krn_ReadComplexVectorNoLength(char *fileName);
doubleVector_t *Krn_ReadRealVectorNoLength(char *fileName);
dsp_floatMatrix_Pt Dsp_AllocateRealFloatMatrix(int height ,int width);
dsp_floatMatrix_t *IIP_ReadTIFFMatrix(char *fileName);
void IIP_InstallColorMapMatrix(dsp_Matrix_t *colorMap_P);
dsp_Matrix_t   *IIP_StoreColormap(char *fileName);
int Krn_ComputeLinearSystemCxMatrix(dsp_cxMatrix_t *mat_P,cxVector_t *b_P, cxVector_t *x_P);
int Krn_ComputeLinearSystemRealMatrix(dsp_Matrix_t *mat_P,doubleVector_t *b_P, doubleVector_t *x_P);
int Krn_ComputeQRRealMatrix(dsp_Matrix_t *mat_P,dsp_Matrix_t *Q_P, dsp_Matrix_t *R_P);
int Krn_ComputeSystemCxMatrix(dsp_cxMatrix_t *mat_P,cxVector_t *b_P, cxVector_t *x_P);
int Krn_ComputeSystemRealMatrix(dsp_Matrix_t *mat_P,doubleVector_t *b_P, doubleVector_t *x_P);

int IIP_WriteMatrixTIFF(float **mat_PP,int pwidth,int pheight,char *fileName);
Tcl_Obj  *IIP_PlotPolarFromVector(Tcl_Interp *interp,cxVector_t *vec_P,char *varCurveName, int varCurveNameLength);

Tcl_Obj  *IIP_PlotSmithChartFromVector(Tcl_Interp *interp,cxVector_t *vec_P,char *varCurveName, int varCurveNameLength);

 void  Dsp_MatrixStats(dsp_floatMatrix_Pt	 matrix_P,float	*min_P,float	*max_P,float	*mean_P,float	*variance_P);
void  Dsp_MatrixNormalize(dsp_floatMatrix_Pt	 matrix_P,int level);
void  Dsp_MatrixNormalizeDB(dsp_floatMatrix_Pt	matrix_P,int	level,float	dBFloor,float *min_P, float *max_P);
void  Dsp_MatrixNormalizeDBInverse(dsp_floatMatrix_Pt	matrix_P,int	level,float	dBFloor,float *min_P, float *max_P);
int  Dsp_MatrixHistogram(dsp_floatMatrix_Pt	 matrix_P,int level,float	**hist_PP);
int  Dsp_MatrixHistogramEq(dsp_floatMatrix_Pt	matrix_P,int level);
 void Dsp_MatrixAddNoise(dsp_floatMatrix_Pt matrix_P,int type,char* expression,float param1,float param2);
 dsp_floatMatrix_Pt Dsp_MatrixOperate(dsp_floatMatrix_Pt	 matrix_P,int operation,int level);
 int Dsp_CalculateMatrix(dsp_floatMatrix_Pt	matrix1_P,dsp_floatMatrix_Pt	matrix2_P,
		int operation,int wOffset,int hOffset,int level);
int  Dsp_FillMatrix(dsp_floatMatrix_Pt	matrix_P,float value);
dsp_floatMatrix_Pt	 Dsp_GenMatrix(int width,int height,int rectWidth,int rectHeight,
			int widthOffset,int heightOffset,
			float pixel,int complexFlag,int complementFlag);

int Dsp_Spectrogram(doubleVector_t *vec_P,int windowLength,int overlap,int zeropad,float samplingRate,
	int windowType,float threshold,int surfaceFlag,int imageFlag,int indBFlag,int fileFlag,char *fileName);

int	IIP_CreateVectorFromAIFF(char *fileName,float *vector_P, int *length_P, float *samplingRate_P,char *info);



void IIP_DisplayMatrix(dsp_floatMatrix_Pt matrix_P,float minx,float maxx,float miny,float maxy,char *title );


void IIP_SaveAIFF(char *fileName, double *vector_P, int length, int bits, float samplingRate);

void IIP_LPCAnalysis(float *y_P,int points, char *title,int method,int m,int windowSize,int npts,int overlap,
		float samplingRate, int dBInFlag,int expandFlag,int surfaceFlag,
		int imageFlag,int stackChoice,int residualFlag,
		int poleZeroFlag,int formantFlag,int zeroCrossingFlag,int lpcFileFlag,char *fileName,
		int pzFileFlag,char *pzfileName);


void  IIP_Cepstrum(float *y_P,int points, char *theTitle, int windowLength,int overlap,int mask,
         float samplingRate,int windowType,int plotStackedCepstrum,int surfaceFlag,
	     int imageFlag,int indBFlag,int fileFlag,char *fileName);

int Dsp_LPCAnalysisTCL(Tcl_Interp *interp,char *name,
          float *x_P,int windowSize, int m, int method, float samplingRate, int pzFormat);

int    Dsp_Cepstrum(Tcl_Interp *interp,char *name,double *y_P, int windowLength,int mask,
         float samplingRate,int windowType);


int IIP_CurveTCLObjXSci(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjYSci(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjYFixed(Tcl_Obj  *obj_P);
int IIP_CurveTCLObjXFixed(Tcl_Obj  *obj_P);

int IIP_CurveTCLObjSetScreenLocation(Tcl_Obj  *obj_P, int screenX, int screenY);
int IIP_CurveTCLObjSetWidthHeight(Tcl_Obj  *obj_P, int width, int height);
int  IIP_CurveTCLObjMarkerItem(Tcl_Obj *obj_P,float x,float y,int color,int marker);
int  IIP_CurveTCLObjPenItem(Tcl_Obj *obj_P,int color,int dash);
Tcl_Obj  *IIP_PlotSmithChartNew(Tcl_Interp *interp,char *varCurveName, int varCurveNameLength);

int  Dsp_Cepstrum(Tcl_Interp *interp,char *name,double *y_P, int windowLength,int mask,
         float samplingRate,int windowType);
         doubleVector_t* Dsp_AllocateDoubleVector(int n);
doubleVector_t* Dsp_AllocateVector(int length);
cxVector_t* Dsp_AllocateCxVector(int length);
int Dsp_GenGaussVector(doubleVector_t *vec_P,float std,float mean, long seedIn);
int Dsp_GenGaussComplexVector(cxVector_t *vec_P,float std,float mean, long seedIn);
int Dsp_DotRealReal(doubleVector_t *x_P, doubleVector_t *y_P, double *z);
int Dsp_SAXPYReal(doubleVector_t *vx_P,doubleVector_t *vy_P,double alpha);
int Dsp_SAXPYComplex(cxVector_t *vx_P,cxVector_t *vy_P,cxScalar_t *alpha); 
int Dsp_ConvolveReal(doubleVector_t *vx_P,doubleVector_t *vf_P,doubleVector_t *vy_P);
int Dsp_ConvolveComplex(cxVector_t *vx_P,cxVector_t *vf_P,cxVector_t *vy_P);


dsp_floatMatrix_Pt  Dsp_MatrixInterpolate(dsp_floatMatrix_Pt matrix_P,int intWidth,int intHeight);
 int	Dsp_ZeroCrossing(float	*x_P,int n);
  void Dsp_Piksrt(int n,float arr[]);
  int Dsp_Covar(int n,float* x_P,int m,float* a_P,float* alpha_P,float* grc_P);
  int Dsp_Auto(int n,float* x_P,int m,float* a_P,float* alpha_P,float* rc_P);
  void Dsp_PCtolsp(float a[],int m,float freq[], int *lspflag);
  void Dsp_LatticeFilter(float*	x_P,float*	y_P,int points,float*	k_P,int p);
int	Dsp_PolyRoot(float	*a_P,int m,cx_t *roots_P);
dsp_Matrix_t *Dsp_AllocateMatrix(int width,int height);

