/*
 * File: _coder_main_pef_api.h
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

#ifndef _CODER_MAIN_PEF_API_H
#define _CODER_MAIN_PEF_API_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void main_pef(emxArray_real_T *x, real_T fs, emxArray_real_T *f0,
                     emxArray_real_T *conf);
extern void main_pef_api(const mxArray * const prhs[2], int32_T nlhs, const
  mxArray *plhs[2]);
extern void main_pef_atexit(void);
extern void main_pef_initialize(void);
extern void main_pef_terminate(void);
extern void main_pef_xil_shutdown(void);
extern void main_pef_xil_terminate(void);

#endif

/*
 * File trailer for _coder_main_pef_api.h
 *
 * [EOF]
 */
