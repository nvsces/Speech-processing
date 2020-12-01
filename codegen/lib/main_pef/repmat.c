/*
 * File: repmat.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "repmat.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *a
 *                double varargin_2
 *                emxArray_creal_T *b
 * Return Type  : void
 */
void b_repmat(const emxArray_creal_T *a, double varargin_2, emxArray_creal_T *b)
{
  int nrows;
  int i;
  int jtilecol;
  int ibtile;
  int k;
  nrows = b->size[0] * b->size[1];
  b->size[0] = a->size[0];
  i = (int)varargin_2;
  b->size[1] = i;
  emxEnsureCapacity_creal_T(b, nrows);
  nrows = a->size[0];
  for (jtilecol = 0; jtilecol < i; jtilecol++) {
    ibtile = jtilecol * nrows;
    for (k = 0; k < nrows; k++) {
      b->data[ibtile + k] = a->data[k];
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *a
 *                double varargin_2
 *                emxArray_real_T *b
 * Return Type  : void
 */
void repmat(const emxArray_real_T *a, double varargin_2, emxArray_real_T *b)
{
  int nrows;
  int i;
  int jtilecol;
  int ibtile;
  int k;
  nrows = b->size[0] * b->size[1];
  b->size[0] = a->size[0];
  i = (int)varargin_2;
  b->size[1] = i;
  emxEnsureCapacity_real_T(b, nrows);
  nrows = a->size[0];
  for (jtilecol = 0; jtilecol < i; jtilecol++) {
    ibtile = jtilecol * nrows;
    for (k = 0; k < nrows; k++) {
      b->data[ibtile + k] = a->data[k];
    }
  }
}

/*
 * File trailer for repmat.c
 *
 * [EOF]
 */
