/*
 * File: hamming.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "hamming.h"
#include "gencoswin.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "main_pef_rtwutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static int div_s32_floor(int numerator, int denominator);

/* Function Definitions */

/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }

  return quotient;
}

/*
 * Arguments    : double varargin_1
 *                emxArray_real_T *w
 * Return Type  : void
 */
void hamming(double varargin_1, emxArray_real_T *w)
{
  int w_size_idx_0;
  signed char w_data[1];
  int trivialwin;
  double L;
  int i;
  double r;
  emxArray_real_T *b_w;
  int loop_ub;
  int b_loop_ub;
  w_size_idx_0 = 1;
  w_data[0] = 0;
  trivialwin = 0;
  if (varargin_1 == floor(varargin_1)) {
    L = varargin_1;
  } else {
    L = rt_roundd_snf(varargin_1);
  }

  if (L == 0.0) {
    w_size_idx_0 = 0;
    trivialwin = 1;
  } else {
    if (L == 1.0) {
      w_data[0] = 1;
      trivialwin = 1;
    }
  }

  i = w->size[0];
  w->size[0] = w_size_idx_0;
  emxEnsureCapacity_real_T(w, i);
  for (i = 0; i < w_size_idx_0; i++) {
    w->data[0] = w_data[0];
  }

  if (trivialwin == 0) {
    if (rtIsNaN(L + 1.0) || rtIsInf(L + 1.0)) {
      r = rtNaN;
    } else {
      r = fmod(L + 1.0, 2.0);
      if (r == 0.0) {
        r = 0.0;
      }
    }

    emxInit_real_T(&b_w, 1);
    if (r == 0.0) {
      calc_window((L + 1.0) / 2.0, L + 1.0, w);
      if (2 > w->size[0]) {
        i = 0;
        w_size_idx_0 = 1;
        trivialwin = -1;
      } else {
        i = w->size[0] - 1;
        w_size_idx_0 = -1;
        trivialwin = 1;
      }

      loop_ub = div_s32_floor(trivialwin - i, w_size_idx_0);
      trivialwin = b_w->size[0];
      b_w->size[0] = (w->size[0] + loop_ub) + 1;
      emxEnsureCapacity_real_T(b_w, trivialwin);
      b_loop_ub = w->size[0];
      for (trivialwin = 0; trivialwin < b_loop_ub; trivialwin++) {
        b_w->data[trivialwin] = w->data[trivialwin];
      }

      for (trivialwin = 0; trivialwin <= loop_ub; trivialwin++) {
        b_w->data[trivialwin + w->size[0]] = w->data[i + w_size_idx_0 *
          trivialwin];
      }

      i = w->size[0];
      w->size[0] = b_w->size[0];
      emxEnsureCapacity_real_T(w, i);
      loop_ub = b_w->size[0];
      for (i = 0; i < loop_ub; i++) {
        w->data[i] = b_w->data[i];
      }
    } else {
      calc_window(((L + 1.0) + 1.0) / 2.0, L + 1.0, w);
      if (2 > w->size[0] - 1) {
        i = 0;
        w_size_idx_0 = 1;
        trivialwin = -1;
      } else {
        i = w->size[0] - 2;
        w_size_idx_0 = -1;
        trivialwin = 1;
      }

      loop_ub = div_s32_floor(trivialwin - i, w_size_idx_0);
      trivialwin = b_w->size[0];
      b_w->size[0] = (w->size[0] + loop_ub) + 1;
      emxEnsureCapacity_real_T(b_w, trivialwin);
      b_loop_ub = w->size[0];
      for (trivialwin = 0; trivialwin < b_loop_ub; trivialwin++) {
        b_w->data[trivialwin] = w->data[trivialwin];
      }

      for (trivialwin = 0; trivialwin <= loop_ub; trivialwin++) {
        b_w->data[trivialwin + w->size[0]] = w->data[i + w_size_idx_0 *
          trivialwin];
      }

      i = w->size[0];
      w->size[0] = b_w->size[0];
      emxEnsureCapacity_real_T(w, i);
      loop_ub = b_w->size[0];
      for (i = 0; i < loop_ub; i++) {
        w->data[i] = b_w->data[i];
      }
    }

    emxFree_real_T(&b_w);
  }
}

/*
 * File trailer for hamming.c
 *
 * [EOF]
 */
