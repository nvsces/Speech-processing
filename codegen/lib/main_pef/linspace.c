/*
 * File: linspace.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "linspace.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */

/*
 * Arguments    : double d2
 *                double n1
 *                emxArray_real_T *y
 * Return Type  : void
 */
void linspace(double d2, double n1, emxArray_real_T *y)
{
  int y_tmp;
  int i;
  int k;
  double delta1;
  y_tmp = y->size[0] * y->size[1];
  y->size[0] = 1;
  i = (int)floor(n1);
  y->size[1] = i;
  emxEnsureCapacity_real_T(y, y_tmp);
  y_tmp = i - 1;
  y->data[y_tmp] = d2;
  if (y->size[1] >= 2) {
    y->data[0] = 0.0;
    if (y->size[1] >= 3) {
      if ((0.0 == -d2) && (i > 2)) {
        for (k = 2; k <= y_tmp; k++) {
          y->data[k - 1] = d2 * ((double)(((k << 1) - i) - 1) / ((double)i - 1.0));
        }

        if ((i & 1) == 1) {
          y->data[i >> 1] = 0.0;
        }
      } else if ((d2 < 0.0) && (fabs(d2) > 8.9884656743115785E+307)) {
        delta1 = d2 / ((double)y->size[1] - 1.0);
        y_tmp = y->size[1];
        for (k = 0; k <= y_tmp - 3; k++) {
          y->data[k + 1] = delta1 * ((double)k + 1.0);
        }
      } else {
        delta1 = d2 / ((double)y->size[1] - 1.0);
        y_tmp = y->size[1];
        for (k = 0; k <= y_tmp - 3; k++) {
          y->data[k + 1] = ((double)k + 1.0) * delta1;
        }
      }
    }
  }
}

/*
 * File trailer for linspace.c
 *
 * [EOF]
 */
