/*
 * File: ifft.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "ifft.h"
#include "fft1.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */

/*
 * Arguments    : const emxArray_creal_T *x
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void ifft(const emxArray_creal_T *x, emxArray_creal_T *y)
{
  int n1;
  emxArray_real_T *costab1q;
  int ihi;
  boolean_T useRadix2;
  int N2blue;
  int nd2;
  double twid_re;
  int idx;
  int k;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxArray_creal_T *rwork;
  emxArray_creal_T *wwc;
  unsigned int sx_idx_1;
  int nChan;
  int nRowsM1;
  int rt;
  int nInt2;
  int nRowsM2;
  int sz_idx_0;
  int minNrowsNx;
  int nRowsD4;
  int istart;
  int i;
  double nt_im;
  double nt_re;
  int b_k;
  emxArray_creal_T *fv;
  double twid_im;
  emxArray_creal_T *b_fv;
  int nt_re_tmp;
  n1 = x->size[0];
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    ihi = y->size[0] * y->size[1];
    y->size[0] = x->size[0];
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, ihi);
  } else {
    emxInit_real_T(&costab1q, 2);
    useRadix2 = ((x->size[0] & (x->size[0] - 1)) == 0);
    get_algo_sizes(x->size[0], useRadix2, &N2blue, &nd2);
    twid_re = 6.2831853071795862 / (double)nd2;
    idx = nd2 / 2 / 2;
    ihi = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = idx + 1;
    emxEnsureCapacity_real_T(costab1q, ihi);
    costab1q->data[0] = 1.0;
    nd2 = idx / 2 - 1;
    for (k = 0; k <= nd2; k++) {
      costab1q->data[k + 1] = cos(twid_re * ((double)k + 1.0));
    }

    ihi = nd2 + 2;
    nd2 = idx - 1;
    for (k = ihi; k <= nd2; k++) {
      costab1q->data[k] = sin(twid_re * (double)(idx - k));
    }

    costab1q->data[idx] = 0.0;
    emxInit_real_T(&costab, 2);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    if (!useRadix2) {
      idx = costab1q->size[1] - 1;
      nd2 = (costab1q->size[1] - 1) << 1;
      ihi = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = nd2 + 1;
      emxEnsureCapacity_real_T(costab, ihi);
      ihi = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = nd2 + 1;
      emxEnsureCapacity_real_T(sintab, ihi);
      costab->data[0] = 1.0;
      sintab->data[0] = 0.0;
      ihi = sintabinv->size[0] * sintabinv->size[1];
      sintabinv->size[0] = 1;
      sintabinv->size[1] = nd2 + 1;
      emxEnsureCapacity_real_T(sintabinv, ihi);
      for (k = 0; k < idx; k++) {
        sintabinv->data[k + 1] = costab1q->data[(idx - k) - 1];
      }

      ihi = costab1q->size[1];
      for (k = ihi; k <= nd2; k++) {
        sintabinv->data[k] = costab1q->data[k - idx];
      }

      for (k = 0; k < idx; k++) {
        costab->data[k + 1] = costab1q->data[k + 1];
        sintab->data[k + 1] = -costab1q->data[(idx - k) - 1];
      }

      ihi = costab1q->size[1];
      for (k = ihi; k <= nd2; k++) {
        costab->data[k] = -costab1q->data[nd2 - k];
        sintab->data[k] = -costab1q->data[k - idx];
      }
    } else {
      idx = costab1q->size[1] - 1;
      nd2 = (costab1q->size[1] - 1) << 1;
      ihi = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = nd2 + 1;
      emxEnsureCapacity_real_T(costab, ihi);
      ihi = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = nd2 + 1;
      emxEnsureCapacity_real_T(sintab, ihi);
      costab->data[0] = 1.0;
      sintab->data[0] = 0.0;
      for (k = 0; k < idx; k++) {
        costab->data[k + 1] = costab1q->data[k + 1];
        sintab->data[k + 1] = costab1q->data[(idx - k) - 1];
      }

      ihi = costab1q->size[1];
      for (k = ihi; k <= nd2; k++) {
        costab->data[k] = -costab1q->data[nd2 - k];
        sintab->data[k] = costab1q->data[k - idx];
      }

      sintabinv->size[0] = 1;
      sintabinv->size[1] = 0;
    }

    emxFree_real_T(&costab1q);
    emxInit_creal_T(&rwork, 1);
    if (useRadix2) {
      sx_idx_1 = (unsigned int)x->size[1];
      nChan = (int)sx_idx_1;
      ihi = y->size[0] * y->size[1];
      y->size[0] = x->size[0];
      y->size[1] = x->size[1];
      emxEnsureCapacity_creal_T(y, ihi);
      if (0 <= (int)sx_idx_1 - 1) {
        nd2 = x->size[0];
        nRowsM1 = x->size[0];
        if (nd2 < nRowsM1) {
          nRowsM1 = nd2;
        }

        nRowsM2 = x->size[0] - 2;
        minNrowsNx = x->size[0] / 2;
        nRowsD4 = minNrowsNx / 2;
        sz_idx_0 = x->size[0];
      }

      for (k = 0; k < nChan; k++) {
        nInt2 = k * x->size[0];
        ihi = rwork->size[0];
        rwork->size[0] = sz_idx_0;
        emxEnsureCapacity_creal_T(rwork, ihi);
        if (n1 > x->size[0]) {
          ihi = rwork->size[0];
          rwork->size[0] = sz_idx_0;
          emxEnsureCapacity_creal_T(rwork, ihi);
          for (ihi = 0; ihi < sz_idx_0; ihi++) {
            rwork->data[ihi].re = 0.0;
            rwork->data[ihi].im = 0.0;
          }
        }

        rt = 0;
        nd2 = 0;
        for (i = 0; i <= nRowsM1 - 2; i++) {
          rwork->data[nd2] = x->data[nInt2];
          idx = n1;
          useRadix2 = true;
          while (useRadix2) {
            idx >>= 1;
            rt ^= idx;
            useRadix2 = ((rt & idx) == 0);
          }

          nd2 = rt;
          nInt2++;
        }

        rwork->data[nd2] = x->data[nInt2];
        if (n1 > 1) {
          for (i = 0; i <= nRowsM2; i += 2) {
            nt_re = rwork->data[i + 1].re;
            nt_im = rwork->data[i + 1].im;
            twid_im = rwork->data[i].re;
            twid_re = rwork->data[i].im;
            rwork->data[i + 1].re = rwork->data[i].re - rwork->data[i + 1].re;
            rwork->data[i + 1].im = rwork->data[i].im - rwork->data[i + 1].im;
            twid_im += nt_re;
            twid_re += nt_im;
            rwork->data[i].re = twid_im;
            rwork->data[i].im = twid_re;
          }
        }

        nd2 = 2;
        rt = 4;
        b_k = nRowsD4;
        nInt2 = ((nRowsD4 - 1) << 2) + 1;
        while (b_k > 0) {
          for (i = 0; i < nInt2; i += rt) {
            nt_re_tmp = i + nd2;
            nt_re = rwork->data[nt_re_tmp].re;
            nt_im = rwork->data[nt_re_tmp].im;
            rwork->data[nt_re_tmp].re = rwork->data[i].re - rwork->
              data[nt_re_tmp].re;
            rwork->data[nt_re_tmp].im = rwork->data[i].im - rwork->
              data[nt_re_tmp].im;
            rwork->data[i].re += nt_re;
            rwork->data[i].im += nt_im;
          }

          istart = 1;
          for (idx = b_k; idx < minNrowsNx; idx += b_k) {
            twid_re = costab->data[idx];
            twid_im = sintab->data[idx];
            i = istart;
            ihi = istart + nInt2;
            while (i < ihi) {
              nt_re_tmp = i + nd2;
              nt_re = twid_re * rwork->data[nt_re_tmp].re - twid_im *
                rwork->data[nt_re_tmp].im;
              nt_im = twid_re * rwork->data[nt_re_tmp].im + twid_im *
                rwork->data[nt_re_tmp].re;
              rwork->data[nt_re_tmp].re = rwork->data[i].re - nt_re;
              rwork->data[nt_re_tmp].im = rwork->data[i].im - nt_im;
              rwork->data[i].re += nt_re;
              rwork->data[i].im += nt_im;
              i += rt;
            }

            istart++;
          }

          b_k /= 2;
          nd2 = rt;
          rt += rt;
          nInt2 -= nd2;
        }

        for (nd2 = 0; nd2 < n1; nd2++) {
          y->data[nd2 + y->size[0] * k] = rwork->data[nd2];
        }
      }

      if (y->size[0] > 1) {
        twid_re = 1.0 / (double)y->size[0];
        nd2 = y->size[0] * y->size[1];
        for (ihi = 0; ihi < nd2; ihi++) {
          y->data[ihi].re *= twid_re;
          y->data[ihi].im *= twid_re;
        }
      }
    } else {
      emxInit_creal_T(&wwc, 1);
      n1 = x->size[0];
      sx_idx_1 = (unsigned int)x->size[1];
      nChan = (int)sx_idx_1;
      nd2 = (x->size[0] + x->size[0]) - 1;
      ihi = wwc->size[0];
      wwc->size[0] = nd2;
      emxEnsureCapacity_creal_T(wwc, ihi);
      idx = x->size[0];
      rt = 0;
      wwc->data[x->size[0] - 1].re = 1.0;
      wwc->data[x->size[0] - 1].im = 0.0;
      nInt2 = x->size[0] << 1;
      ihi = x->size[0];
      for (k = 0; k <= ihi - 2; k++) {
        istart = ((k + 1) << 1) - 1;
        if (nInt2 - rt <= istart) {
          rt += istart - nInt2;
        } else {
          rt += istart;
        }

        nt_im = 3.1415926535897931 * (double)rt / (double)n1;
        if (nt_im == 0.0) {
          nt_re = 1.0;
          nt_im = 0.0;
        } else {
          nt_re = cos(nt_im);
          nt_im = sin(nt_im);
        }

        wwc->data[idx - 2].re = nt_re;
        wwc->data[idx - 2].im = -nt_im;
        idx--;
      }

      idx = 0;
      ihi = nd2 - 1;
      for (k = ihi; k >= n1; k--) {
        wwc->data[k] = wwc->data[idx];
        idx++;
      }

      ihi = y->size[0] * y->size[1];
      y->size[0] = x->size[0];
      y->size[1] = x->size[1];
      emxEnsureCapacity_creal_T(y, ihi);
      if (0 <= (int)sx_idx_1 - 1) {
        nd2 = x->size[0];
        minNrowsNx = x->size[0];
        if (nd2 < minNrowsNx) {
          minNrowsNx = nd2;
        }

        sz_idx_0 = x->size[0];
        i = minNrowsNx + 1;
        nRowsM2 = wwc->size[0];
      }

      emxInit_creal_T(&fv, 1);
      emxInit_creal_T(&b_fv, 1);
      for (k = 0; k < nChan; k++) {
        ihi = rwork->size[0];
        rwork->size[0] = sz_idx_0;
        emxEnsureCapacity_creal_T(rwork, ihi);
        if (n1 > x->size[0]) {
          ihi = rwork->size[0];
          rwork->size[0] = sz_idx_0;
          emxEnsureCapacity_creal_T(rwork, ihi);
          for (ihi = 0; ihi < sz_idx_0; ihi++) {
            rwork->data[ihi].re = 0.0;
            rwork->data[ihi].im = 0.0;
          }
        }

        nd2 = k * x->size[0];
        for (b_k = 0; b_k < minNrowsNx; b_k++) {
          nt_re_tmp = (n1 + b_k) - 1;
          rwork->data[b_k].re = wwc->data[nt_re_tmp].re * x->data[nd2].re +
            wwc->data[nt_re_tmp].im * x->data[nd2].im;
          rwork->data[b_k].im = wwc->data[nt_re_tmp].re * x->data[nd2].im -
            wwc->data[nt_re_tmp].im * x->data[nd2].re;
          nd2++;
        }

        for (b_k = i; b_k <= n1; b_k++) {
          rwork->data[b_k - 1].re = 0.0;
          rwork->data[b_k - 1].im = 0.0;
        }

        r2br_r2dit_trig_impl(rwork, N2blue, costab, sintab, fv);
        r2br_r2dit_trig_impl(wwc, N2blue, costab, sintab, b_fv);
        ihi = b_fv->size[0];
        b_fv->size[0] = fv->size[0];
        emxEnsureCapacity_creal_T(b_fv, ihi);
        nd2 = fv->size[0];
        for (ihi = 0; ihi < nd2; ihi++) {
          twid_re = fv->data[ihi].re * b_fv->data[ihi].im + fv->data[ihi].im *
            b_fv->data[ihi].re;
          b_fv->data[ihi].re = fv->data[ihi].re * b_fv->data[ihi].re - fv->
            data[ihi].im * b_fv->data[ihi].im;
          b_fv->data[ihi].im = twid_re;
        }

        r2br_r2dit_trig_impl(b_fv, N2blue, costab, sintabinv, fv);
        if (fv->size[0] > 1) {
          twid_re = 1.0 / (double)fv->size[0];
          nd2 = fv->size[0];
          for (ihi = 0; ihi < nd2; ihi++) {
            fv->data[ihi].re *= twid_re;
            fv->data[ihi].im *= twid_re;
          }
        }

        idx = 0;
        for (b_k = n1; b_k <= nRowsM2; b_k++) {
          twid_re = wwc->data[b_k - 1].re * fv->data[b_k - 1].re + wwc->data[b_k
            - 1].im * fv->data[b_k - 1].im;
          twid_im = wwc->data[b_k - 1].re * fv->data[b_k - 1].im - wwc->data[b_k
            - 1].im * fv->data[b_k - 1].re;
          rwork->data[idx].re = twid_re;
          rwork->data[idx].im = twid_im;
          rwork->data[idx].re = twid_re;
          rwork->data[idx].im = twid_im;
          if (rwork->data[idx].im == 0.0) {
            twid_im = rwork->data[idx].re / (double)n1;
            twid_re = 0.0;
          } else if (rwork->data[idx].re == 0.0) {
            twid_im = 0.0;
            twid_re = rwork->data[idx].im / (double)n1;
          } else {
            twid_im = rwork->data[idx].re / (double)n1;
            twid_re = rwork->data[idx].im / (double)n1;
          }

          rwork->data[idx].re = twid_im;
          rwork->data[idx].im = twid_re;
          idx++;
        }

        for (nd2 = 0; nd2 < n1; nd2++) {
          y->data[nd2 + y->size[0] * k] = rwork->data[nd2];
        }
      }

      emxFree_creal_T(&b_fv);
      emxFree_creal_T(&fv);
      emxFree_creal_T(&wwc);
    }

    emxFree_creal_T(&rwork);
    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
  }
}

/*
 * File trailer for ifft.c
 *
 * [EOF]
 */
