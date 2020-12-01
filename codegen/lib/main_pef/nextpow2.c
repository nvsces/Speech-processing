/*
 * File: nextpow2.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "nextpow2.h"
#include "main_pef.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */

/*
 * Arguments    : double n
 * Return Type  : double
 */
double nextpow2(double n)
{
  double p;
  double f;
  int eint;
  p = fabs(n);
  if ((!rtIsInf(p)) && (!rtIsNaN(p))) {
    f = frexp(p, &eint);
    p = eint;
    if (f == 0.5) {
      p = (double)eint - 1.0;
    }
  }

  return p;
}

/*
 * File trailer for nextpow2.c
 *
 * [EOF]
 */
