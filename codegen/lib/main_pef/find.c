/*
 * File: find.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "find.h"
#include "main_pef.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_boolean_T *x
 *                int i_data[]
 *                int i_size[2]
 * Return Type  : void
 */
void eml_find(const emxArray_boolean_T *x, int i_data[], int i_size[2])
{
  int k;
  int ii;
  int idx;
  boolean_T exitg1;
  k = (1 <= x->size[1]);
  ii = x->size[1];
  idx = 0;
  i_size[0] = 1;
  i_size[1] = k;
  exitg1 = false;
  while ((!exitg1) && (ii > 0)) {
    if (x->data[ii - 1]) {
      idx = 1;
      i_data[0] = ii;
      exitg1 = true;
    } else {
      ii--;
    }
  }

  if (k == 1) {
    if (idx == 0) {
      i_size[0] = 1;
      i_size[1] = 0;
    }
  } else {
    i_size[1] = (1 <= idx);
  }
}

/*
 * File trailer for find.c
 *
 * [EOF]
 */
