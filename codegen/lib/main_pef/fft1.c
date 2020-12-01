/*
 * File: fft1.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "fft1.h"
#include "bluesteinSetup.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                int N2
 *                int n1
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *sintabinv
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void dobluesteinfft(const emxArray_real_T *x, int N2, int n1, const
                    emxArray_real_T *costab, const emxArray_real_T *sintab,
                    const emxArray_real_T *sintabinv, emxArray_creal_T *y)
{
  emxArray_creal_T *wwc;
  unsigned int sx_idx_1;
  int nChan;
  int k;
  int loop_ub;
  emxArray_creal_T *rwork;
  int minNrowsNx;
  int xidx;
  emxArray_creal_T *fv;
  int a_re_tmp;
  emxArray_creal_T *b_fv;
  int b_k;
  int i;
  int i1;
  double im;
  emxInit_creal_T(&wwc, 1);
  sx_idx_1 = (unsigned int)x->size[1];
  nChan = (int)sx_idx_1;
  bluesteinSetup(n1, wwc);
  k = y->size[0] * y->size[1];
  y->size[0] = n1;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, k);
  if (n1 > x->size[0]) {
    loop_ub = x->size[1];
    for (k = 0; k < loop_ub; k++) {
      xidx = y->size[0];
      for (a_re_tmp = 0; a_re_tmp < xidx; a_re_tmp++) {
        y->data[a_re_tmp + y->size[0] * k].re = 0.0;
        y->data[a_re_tmp + y->size[0] * k].im = 0.0;
      }
    }
  }

  emxInit_creal_T(&rwork, 1);
  if (0 <= (int)sx_idx_1 - 1) {
    minNrowsNx = x->size[0];
    if (n1 < minNrowsNx) {
      minNrowsNx = n1;
    }

    i = minNrowsNx + 1;
    i1 = wwc->size[0];
  }

  emxInit_creal_T(&fv, 1);
  emxInit_creal_T(&b_fv, 1);
  for (b_k = 0; b_k < nChan; b_k++) {
    k = rwork->size[0];
    rwork->size[0] = n1;
    emxEnsureCapacity_creal_T(rwork, k);
    if (n1 > x->size[0]) {
      k = rwork->size[0];
      rwork->size[0] = n1;
      emxEnsureCapacity_creal_T(rwork, k);
      for (k = 0; k < n1; k++) {
        rwork->data[k].re = 0.0;
        rwork->data[k].im = 0.0;
      }
    }

    xidx = b_k * x->size[0];
    for (k = 0; k < minNrowsNx; k++) {
      a_re_tmp = (n1 + k) - 1;
      rwork->data[k].re = wwc->data[a_re_tmp].re * x->data[xidx];
      rwork->data[k].im = wwc->data[a_re_tmp].im * -x->data[xidx];
      xidx++;
    }

    for (k = i; k <= n1; k++) {
      rwork->data[k - 1].re = 0.0;
      rwork->data[k - 1].im = 0.0;
    }

    r2br_r2dit_trig_impl(rwork, N2, costab, sintab, fv);
    r2br_r2dit_trig_impl(wwc, N2, costab, sintab, b_fv);
    k = b_fv->size[0];
    b_fv->size[0] = fv->size[0];
    emxEnsureCapacity_creal_T(b_fv, k);
    loop_ub = fv->size[0];
    for (k = 0; k < loop_ub; k++) {
      im = fv->data[k].re * b_fv->data[k].im + fv->data[k].im * b_fv->data[k].re;
      b_fv->data[k].re = fv->data[k].re * b_fv->data[k].re - fv->data[k].im *
        b_fv->data[k].im;
      b_fv->data[k].im = im;
    }

    r2br_r2dit_trig_impl(b_fv, N2, costab, sintabinv, fv);
    if (fv->size[0] > 1) {
      im = 1.0 / (double)fv->size[0];
      loop_ub = fv->size[0];
      for (k = 0; k < loop_ub; k++) {
        fv->data[k].re *= im;
        fv->data[k].im *= im;
      }
    }

    xidx = 0;
    for (k = n1; k <= i1; k++) {
      rwork->data[xidx].re = wwc->data[k - 1].re * fv->data[k - 1].re +
        wwc->data[k - 1].im * fv->data[k - 1].im;
      rwork->data[xidx].im = wwc->data[k - 1].re * fv->data[k - 1].im -
        wwc->data[k - 1].im * fv->data[k - 1].re;
      xidx++;
    }

    for (xidx = 0; xidx < n1; xidx++) {
      y->data[xidx + y->size[0] * b_k] = rwork->data[xidx];
    }
  }

  emxFree_creal_T(&b_fv);
  emxFree_creal_T(&fv);
  emxFree_creal_T(&rwork);
  emxFree_creal_T(&wwc);
}

/*
 * Arguments    : int nRows
 *                boolean_T useRadix2
 *                emxArray_real_T *costab
 *                emxArray_real_T *sintab
 *                emxArray_real_T *sintabinv
 * Return Type  : void
 */
void generate_twiddle_tables(int nRows, boolean_T useRadix2, emxArray_real_T
  *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  int n;
  int i;
  int nd2;
  int k;
  emxInit_real_T(&costab1q, 2);
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i);
  costab1q->data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q->data[k + 1] = cos(e * ((double)k + 1.0));
  }

  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q->data[k] = sin(e * (double)(n - k));
  }

  costab1q->data[n] = 0.0;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    i = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i);
    for (k = 0; k < n; k++) {
      sintabinv->data[k + 1] = costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      sintabinv->data[k] = costab1q->data[k - n];
    }

    for (k = 0; k < n; k++) {
      costab->data[k + 1] = costab1q->data[k + 1];
      sintab->data[k + 1] = -costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab->data[k + 1] = costab1q->data[k + 1];
      sintab->data[k + 1] = -costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }

    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }

  emxFree_real_T(&costab1q);
}

/*
 * Arguments    : int n1
 *                boolean_T useRadix2
 *                int *N2blue
 *                int *nRows
 * Return Type  : void
 */
void get_algo_sizes(int n1, boolean_T useRadix2, int *N2blue, int *nRows)
{
  int n;
  int pmax;
  int pmin;
  boolean_T exitg1;
  int k;
  int pow2p;
  *N2blue = 1;
  if (useRadix2) {
    *nRows = n1;
  } else {
    n = (n1 + n1) - 1;
    pmax = 31;
    if (n <= 1) {
      pmax = 0;
    } else {
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        k = (pmin + pmax) >> 1;
        pow2p = 1 << k;
        if (pow2p == n) {
          pmax = k;
          exitg1 = true;
        } else if (pow2p > n) {
          pmax = k;
        } else {
          pmin = k;
        }
      }
    }

    *N2blue = 1 << pmax;
    *nRows = *N2blue;
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void r2br_r2dit_trig(const emxArray_real_T *x, int n1_unsigned, const
                     emxArray_real_T *costab, const emxArray_real_T *sintab,
                     emxArray_creal_T *y)
{
  unsigned int sx_idx_1;
  int nChan;
  int k;
  int iy;
  emxArray_creal_T *rwork;
  int nRowsM1;
  int iDelta;
  int b_k;
  int ju;
  int ix;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  int j;
  int ihi;
  sx_idx_1 = (unsigned int)x->size[1];
  nChan = (int)sx_idx_1;
  k = y->size[0] * y->size[1];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, k);
  if (n1_unsigned > x->size[0]) {
    iy = x->size[1];
    for (k = 0; k < iy; k++) {
      iDelta = y->size[0];
      for (ju = 0; ju < iDelta; ju++) {
        y->data[ju + y->size[0] * k].re = 0.0;
        y->data[ju + y->size[0] * k].im = 0.0;
      }
    }
  }

  emxInit_creal_T(&rwork, 1);
  if (0 <= (int)sx_idx_1 - 1) {
    nRowsM1 = x->size[0];
    if (nRowsM1 >= n1_unsigned) {
      nRowsM1 = n1_unsigned;
    }

    nRowsM2 = n1_unsigned - 2;
    nRowsD2 = n1_unsigned / 2;
    nRowsD4 = nRowsD2 / 2;
  }

  for (b_k = 0; b_k < nChan; b_k++) {
    ix = b_k * x->size[0];
    k = rwork->size[0];
    rwork->size[0] = n1_unsigned;
    emxEnsureCapacity_creal_T(rwork, k);
    if (n1_unsigned > x->size[0]) {
      k = rwork->size[0];
      rwork->size[0] = n1_unsigned;
      emxEnsureCapacity_creal_T(rwork, k);
      for (k = 0; k < n1_unsigned; k++) {
        rwork->data[k].re = 0.0;
        rwork->data[k].im = 0.0;
      }
    }

    ju = 0;
    iy = 0;
    for (i = 0; i <= nRowsM1 - 2; i++) {
      rwork->data[iy].re = x->data[ix];
      rwork->data[iy].im = 0.0;
      iDelta = n1_unsigned;
      tst = true;
      while (tst) {
        iDelta >>= 1;
        ju ^= iDelta;
        tst = ((ju & iDelta) == 0);
      }

      iy = ju;
      ix++;
    }

    rwork->data[iy].re = x->data[ix];
    rwork->data[iy].im = 0.0;
    if (n1_unsigned > 1) {
      for (i = 0; i <= nRowsM2; i += 2) {
        temp_re = rwork->data[i + 1].re;
        temp_im = rwork->data[i + 1].im;
        twid_re = rwork->data[i].re;
        twid_im = rwork->data[i].im;
        rwork->data[i + 1].re = rwork->data[i].re - rwork->data[i + 1].re;
        rwork->data[i + 1].im = rwork->data[i].im - rwork->data[i + 1].im;
        twid_re += temp_re;
        twid_im += temp_im;
        rwork->data[i].re = twid_re;
        rwork->data[i].im = twid_im;
      }
    }

    iDelta = 2;
    iy = 4;
    k = nRowsD4;
    ju = ((nRowsD4 - 1) << 2) + 1;
    while (k > 0) {
      for (i = 0; i < ju; i += iy) {
        temp_re_tmp = i + iDelta;
        temp_re = rwork->data[temp_re_tmp].re;
        temp_im = rwork->data[temp_re_tmp].im;
        rwork->data[temp_re_tmp].re = rwork->data[i].re - rwork->
          data[temp_re_tmp].re;
        rwork->data[temp_re_tmp].im = rwork->data[i].im - rwork->
          data[temp_re_tmp].im;
        rwork->data[i].re += temp_re;
        rwork->data[i].im += temp_im;
      }

      ix = 1;
      for (j = k; j < nRowsD2; j += k) {
        twid_re = costab->data[j];
        twid_im = sintab->data[j];
        i = ix;
        ihi = ix + ju;
        while (i < ihi) {
          temp_re_tmp = i + iDelta;
          temp_re = twid_re * rwork->data[temp_re_tmp].re - twid_im *
            rwork->data[temp_re_tmp].im;
          temp_im = twid_re * rwork->data[temp_re_tmp].im + twid_im *
            rwork->data[temp_re_tmp].re;
          rwork->data[temp_re_tmp].re = rwork->data[i].re - temp_re;
          rwork->data[temp_re_tmp].im = rwork->data[i].im - temp_im;
          rwork->data[i].re += temp_re;
          rwork->data[i].im += temp_im;
          i += iy;
        }

        ix++;
      }

      k /= 2;
      iDelta = iy;
      iy += iy;
      ju -= iDelta;
    }

    for (iy = 0; iy < n1_unsigned; iy++) {
      y->data[iy + y->size[0] * b_k] = rwork->data[iy];
    }
  }

  emxFree_creal_T(&rwork);
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int unsigned_nRows
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y)
{
  int istart;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  int ihi;
  istart = x->size[0];
  if (istart >= unsigned_nRows) {
    istart = unsigned_nRows;
  }

  nRowsM2 = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, iy);
  if (unsigned_nRows > x->size[0]) {
    iy = y->size[0];
    y->size[0] = unsigned_nRows;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= istart - 2; i++) {
    y->data[iy] = x->data[ix];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      twid_re = y->data[i].re;
      twid_im = y->data[i].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y->data[i].re = twid_re;
      y->data[i].im = twid_im;
    }
  }

  iy = 2;
  ix = 4;
  ju = ((nRowsD4 - 1) << 2) + 1;
  while (nRowsD4 > 0) {
    for (i = 0; i < ju; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - y->data[temp_re_tmp].re;
      y->data[temp_re_tmp].im = y->data[i].im - y->data[temp_re_tmp].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    istart = 1;
    for (nRowsM2 = nRowsD4; nRowsM2 < nRowsD2; nRowsM2 += nRowsD4) {
      twid_re = costab->data[nRowsM2];
      twid_im = sintab->data[nRowsM2];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    nRowsD4 /= 2;
    iy = ix;
    ix += ix;
    ju -= iy;
  }
}

/*
 * File trailer for fft1.c
 *
 * [EOF]
 */
