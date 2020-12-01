/*
 * File: logspace.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "logspace.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "main_pef_rtwutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */

/*
 * Arguments    : double n
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_logspace(double n, emxArray_real_T *y)
{
  emxArray_real_T *b_y;
  int i;
  int nx;
  double delta1;
  int k;
  emxInit_real_T(&b_y, 2);
  i = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 1;
  nx = (int)floor(n);
  b_y->size[1] = nx;
  emxEnsureCapacity_real_T(b_y, i);
  if (nx >= 1) {
    b_y->data[nx - 1] = 1.0211892990699381;
    if (b_y->size[1] >= 2) {
      b_y->data[0] = -0.3010299956639812;
      if (b_y->size[1] >= 3) {
        delta1 = 1.3222192947339193 / ((double)b_y->size[1] - 1.0);
        i = b_y->size[1];
        for (k = 0; k <= i - 3; k++) {
          b_y->data[k + 1] = ((double)k + 1.0) * delta1 + -0.3010299956639812;
        }
      }
    }
  }

  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = b_y->size[1];
  emxEnsureCapacity_real_T(y, i);
  nx = b_y->size[1];
  for (k = 0; k < nx; k++) {
    y->data[k] = rt_powd_snf(10.0, b_y->data[k]);
  }

  emxFree_real_T(&b_y);
}

/*
 * Arguments    : double d2
 *                double n
 *                emxArray_real_T *y
 * Return Type  : void
 */
void logspace(double d2, double n, emxArray_real_T *y)
{
  emxArray_real_T *b_y;
  int nx;
  int i;
  int k;
  double delta1;
  double delta2;
  emxInit_real_T(&b_y, 2);
  nx = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 1;
  i = (int)floor(n);
  b_y->size[1] = i;
  emxEnsureCapacity_real_T(b_y, nx);
  if (i >= 1) {
    nx = i - 1;
    b_y->data[nx] = d2;
    if (b_y->size[1] >= 2) {
      b_y->data[0] = 1.0;
      if (b_y->size[1] >= 3) {
        if ((1.0 == -d2) && (i > 2)) {
          for (k = 2; k <= nx; k++) {
            b_y->data[k - 1] = d2 * ((double)(((k << 1) - i) - 1) / ((double)i -
              1.0));
          }

          if ((i & 1) == 1) {
            b_y->data[i >> 1] = 0.0;
          }
        } else if ((d2 < 0.0) && (fabs(d2) > 8.9884656743115785E+307)) {
          delta1 = 1.0 / ((double)b_y->size[1] - 1.0);
          delta2 = d2 / ((double)b_y->size[1] - 1.0);
          nx = b_y->size[1];
          for (k = 0; k <= nx - 3; k++) {
            b_y->data[k + 1] = (delta2 * ((double)k + 1.0) + 1.0) - delta1 *
              ((double)k + 1.0);
          }
        } else {
          delta1 = (d2 - 1.0) / ((double)b_y->size[1] - 1.0);
          nx = b_y->size[1];
          for (k = 0; k <= nx - 3; k++) {
            b_y->data[k + 1] = ((double)k + 1.0) * delta1 + 1.0;
          }
        }
      }
    }
  }

  nx = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = b_y->size[1];
  emxEnsureCapacity_real_T(y, nx);
  nx = b_y->size[1];
  for (k = 0; k < nx; k++) {
    y->data[k] = rt_powd_snf(10.0, b_y->data[k]);
  }

  emxFree_real_T(&b_y);
}

/*
 * File trailer for logspace.c
 *
 * [EOF]
 */
