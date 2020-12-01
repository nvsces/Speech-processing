/*
 * File: gencoswin.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "gencoswin.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */

/*
 * Arguments    : double m
 *                double n
 *                emxArray_real_T *w
 * Return Type  : void
 */
void calc_window(double m, double n, emxArray_real_T *w)
{
  emxArray_real_T *y;
  int nx;
  int loop_ub;
  emxInit_real_T(&y, 2);
  if (rtIsNaN(m - 1.0)) {
    nx = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, nx);
    y->data[0] = rtNaN;
  } else if (m - 1.0 < 0.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else if (rtIsInf(m - 1.0) && (0.0 == m - 1.0)) {
    nx = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, nx);
    y->data[0] = rtNaN;
  } else {
    nx = y->size[0] * y->size[1];
    y->size[0] = 1;
    loop_ub = (int)floor(m - 1.0);
    y->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(y, nx);
    for (nx = 0; nx <= loop_ub; nx++) {
      y->data[nx] = nx;
    }
  }

  nx = w->size[0];
  w->size[0] = y->size[1];
  emxEnsureCapacity_real_T(w, nx);
  loop_ub = y->size[1];
  for (nx = 0; nx < loop_ub; nx++) {
    w->data[nx] = 6.2831853071795862 * (y->data[nx] / (n - 1.0));
  }

  emxFree_real_T(&y);
  nx = w->size[0];
  for (loop_ub = 0; loop_ub < nx; loop_ub++) {
    w->data[loop_ub] = cos(w->data[loop_ub]);
  }

  loop_ub = w->size[0];
  for (nx = 0; nx < loop_ub; nx++) {
    w->data[nx] = 0.54 - 0.46 * w->data[nx];
  }
}

/*
 * File trailer for gencoswin.c
 *
 * [EOF]
 */
