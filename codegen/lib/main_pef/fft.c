/*
 * File: fft.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "fft.h"
#include "bluesteinSetup.h"
#include "fft1.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                double varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void b_fft(const emxArray_real_T *x, double varargin_1, emxArray_creal_T *y)
{
  int n1_tmp;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxArray_creal_T *wwc;
  emxArray_creal_T *fv;
  emxArray_creal_T *b_fv;
  boolean_T useRadix2;
  int j;
  int iheight;
  int xidx;
  int minNrowsNx;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int ju;
  int temp_re_tmp;
  int i;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  n1_tmp = (int)varargin_1;
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  emxInit_creal_T(&wwc, 1);
  emxInit_creal_T(&fv, 1);
  emxInit_creal_T(&b_fv, 1);
  if ((x->size[0] == 0) || (n1_tmp == 0)) {
    j = y->size[0];
    y->size[0] = n1_tmp;
    emxEnsureCapacity_creal_T(y, j);
    if (n1_tmp > x->size[0]) {
      j = y->size[0];
      y->size[0] = n1_tmp;
      emxEnsureCapacity_creal_T(y, j);
      for (j = 0; j < n1_tmp; j++) {
        y->data[j].re = 0.0;
        y->data[j].im = 0.0;
      }
    }
  } else {
    useRadix2 = ((n1_tmp & (n1_tmp - 1)) == 0);
    get_algo_sizes((int)varargin_1, useRadix2, &iheight, &xidx);
    generate_twiddle_tables(xidx, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      iheight = x->size[0];
      if (iheight >= n1_tmp) {
        iheight = n1_tmp;
      }

      nRowsM2 = n1_tmp - 2;
      nRowsD2 = n1_tmp / 2;
      nRowsD4 = nRowsD2 / 2;
      j = y->size[0];
      y->size[0] = n1_tmp;
      emxEnsureCapacity_creal_T(y, j);
      if (n1_tmp > x->size[0]) {
        j = y->size[0];
        y->size[0] = n1_tmp;
        emxEnsureCapacity_creal_T(y, j);
        for (j = 0; j < n1_tmp; j++) {
          y->data[j].re = 0.0;
          y->data[j].im = 0.0;
        }
      }

      minNrowsNx = 0;
      ju = 0;
      xidx = 0;
      for (i = 0; i <= iheight - 2; i++) {
        y->data[xidx].re = x->data[minNrowsNx];
        y->data[xidx].im = 0.0;
        xidx = n1_tmp;
        useRadix2 = true;
        while (useRadix2) {
          xidx >>= 1;
          ju ^= xidx;
          useRadix2 = ((ju & xidx) == 0);
        }

        xidx = ju;
        minNrowsNx++;
      }

      y->data[xidx].re = x->data[minNrowsNx];
      y->data[xidx].im = 0.0;
      if (n1_tmp > 1) {
        for (i = 0; i <= nRowsM2; i += 2) {
          temp_re = y->data[i + 1].re;
          temp_im = y->data[i + 1].im;
          twid_im = y->data[i].re;
          twid_re = y->data[i].im;
          y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
          y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
          twid_im += temp_re;
          twid_re += temp_im;
          y->data[i].re = twid_im;
          y->data[i].im = twid_re;
        }
      }

      xidx = 2;
      minNrowsNx = 4;
      iheight = ((nRowsD4 - 1) << 2) + 1;
      while (nRowsD4 > 0) {
        for (i = 0; i < iheight; i += minNrowsNx) {
          temp_re_tmp = i + xidx;
          temp_re = y->data[temp_re_tmp].re;
          temp_im = y->data[temp_re_tmp].im;
          y->data[temp_re_tmp].re = y->data[i].re - y->data[temp_re_tmp].re;
          y->data[temp_re_tmp].im = y->data[i].im - y->data[temp_re_tmp].im;
          y->data[i].re += temp_re;
          y->data[i].im += temp_im;
        }

        ju = 1;
        for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
          twid_re = costab->data[j];
          twid_im = sintab->data[j];
          i = ju;
          nRowsM2 = ju + iheight;
          while (i < nRowsM2) {
            temp_re_tmp = i + xidx;
            temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
              data[temp_re_tmp].im;
            temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
              data[temp_re_tmp].re;
            y->data[temp_re_tmp].re = y->data[i].re - temp_re;
            y->data[temp_re_tmp].im = y->data[i].im - temp_im;
            y->data[i].re += temp_re;
            y->data[i].im += temp_im;
            i += minNrowsNx;
          }

          ju++;
        }

        nRowsD4 /= 2;
        xidx = minNrowsNx;
        minNrowsNx += minNrowsNx;
        iheight -= xidx;
      }
    } else {
      bluesteinSetup(n1_tmp, wwc);
      minNrowsNx = x->size[0];
      if (n1_tmp < minNrowsNx) {
        minNrowsNx = n1_tmp;
      }

      j = y->size[0];
      y->size[0] = n1_tmp;
      emxEnsureCapacity_creal_T(y, j);
      if (n1_tmp > x->size[0]) {
        j = y->size[0];
        y->size[0] = n1_tmp;
        emxEnsureCapacity_creal_T(y, j);
        for (j = 0; j < n1_tmp; j++) {
          y->data[j].re = 0.0;
          y->data[j].im = 0.0;
        }
      }

      xidx = 0;
      for (ju = 0; ju < minNrowsNx; ju++) {
        temp_re_tmp = (n1_tmp + ju) - 1;
        y->data[ju].re = wwc->data[temp_re_tmp].re * x->data[xidx];
        y->data[ju].im = wwc->data[temp_re_tmp].im * -x->data[xidx];
        xidx++;
      }

      j = minNrowsNx + 1;
      for (ju = j; ju <= n1_tmp; ju++) {
        y->data[ju - 1].re = 0.0;
        y->data[ju - 1].im = 0.0;
      }

      r2br_r2dit_trig_impl(y, iheight, costab, sintab, fv);
      r2br_r2dit_trig_impl(wwc, iheight, costab, sintab, b_fv);
      j = b_fv->size[0];
      b_fv->size[0] = fv->size[0];
      emxEnsureCapacity_creal_T(b_fv, j);
      xidx = fv->size[0];
      for (j = 0; j < xidx; j++) {
        twid_re = fv->data[j].re * b_fv->data[j].im + fv->data[j].im *
          b_fv->data[j].re;
        b_fv->data[j].re = fv->data[j].re * b_fv->data[j].re - fv->data[j].im *
          b_fv->data[j].im;
        b_fv->data[j].im = twid_re;
      }

      r2br_r2dit_trig_impl(b_fv, iheight, costab, sintabinv, fv);
      if (fv->size[0] > 1) {
        twid_re = 1.0 / (double)fv->size[0];
        xidx = fv->size[0];
        for (j = 0; j < xidx; j++) {
          fv->data[j].re *= twid_re;
          fv->data[j].im *= twid_re;
        }
      }

      xidx = 0;
      j = wwc->size[0];
      for (ju = n1_tmp; ju <= j; ju++) {
        y->data[xidx].re = wwc->data[ju - 1].re * fv->data[ju - 1].re +
          wwc->data[ju - 1].im * fv->data[ju - 1].im;
        y->data[xidx].im = wwc->data[ju - 1].re * fv->data[ju - 1].im -
          wwc->data[ju - 1].im * fv->data[ju - 1].re;
        xidx++;
      }
    }
  }

  emxFree_creal_T(&b_fv);
  emxFree_creal_T(&fv);
  emxFree_creal_T(&wwc);
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                double varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void fft(const emxArray_real_T *x, double varargin_1, emxArray_creal_T *y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  boolean_T guard1 = false;
  int i;
  boolean_T useRadix2;
  int N2blue;
  int nRows;
  int loop_ub;
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  guard1 = false;
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    guard1 = true;
  } else {
    i = (int)varargin_1;
    if (i == 0) {
      guard1 = true;
    } else {
      useRadix2 = ((i & (i - 1)) == 0);
      get_algo_sizes((int)varargin_1, useRadix2, &N2blue, &nRows);
      generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
      if (useRadix2) {
        r2br_r2dit_trig(x, i, costab, sintab, y);
      } else {
        dobluesteinfft(x, N2blue, i, costab, sintab, sintabinv, y);
      }
    }
  }

  if (guard1) {
    i = (int)varargin_1;
    N2blue = y->size[0] * y->size[1];
    y->size[0] = i;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, N2blue);
    if (i > x->size[0]) {
      nRows = x->size[1];
      for (i = 0; i < nRows; i++) {
        loop_ub = y->size[0];
        for (N2blue = 0; N2blue < loop_ub; N2blue++) {
          y->data[N2blue + y->size[0] * i].re = 0.0;
          y->data[N2blue + y->size[0] * i].im = 0.0;
        }
      }
    }
  }

  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
