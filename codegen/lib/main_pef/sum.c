/*
 * File: sum.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "sum.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void sum(const emxArray_real_T *x, emxArray_real_T *y)
{
  int vstride;
  int j;
  if (x->size[0] == 0) {
    y->size[0] = 0;
  } else {
    vstride = x->size[0];
    j = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, j);
    for (j = 0; j < vstride; j++) {
      y->data[j] = x->data[j];
    }
  }
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
