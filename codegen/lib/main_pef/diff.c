/*
 * File: diff.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "diff.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  int dimSize;
  int ixLead;
  int iyLead;
  double work_data_idx_0;
  int m;
  double tmp1;
  double d;
  dimSize = x->size[1];
  ixLead = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1] - 1;
  emxEnsureCapacity_real_T(y, ixLead);
  ixLead = 1;
  iyLead = 0;
  work_data_idx_0 = x->data[0];
  for (m = 2; m <= dimSize; m++) {
    tmp1 = x->data[ixLead];
    d = tmp1;
    tmp1 -= work_data_idx_0;
    work_data_idx_0 = d;
    ixLead++;
    y->data[iyLead] = tmp1;
    iyLead++;
  }
}

/*
 * File trailer for diff.c
 *
 * [EOF]
 */
