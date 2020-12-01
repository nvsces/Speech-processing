/*
 * File: main_pef.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "main_pef.h"
#include "colon.h"
#include "diff.h"
#include "fft.h"
#include "find.h"
#include "hamming.h"
#include "ifft.h"
#include "interp1.h"
#include "linspace.h"
#include "logspace.h"
#include "main_pef_data.h"
#include "main_pef_emxutil.h"
#include "main_pef_initialize.h"
#include "main_pef_rtwutil.h"
#include "nextpow2.h"
#include "repmat.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include <math.h>

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                double fs
 *                emxArray_real_T *f0
 *                emxArray_real_T *conf
 * Return Type  : void
 */
void main_pef(const emxArray_real_T *x, double fs, emxArray_real_T *f0,
              emxArray_real_T *conf)
{
  emxArray_real_T *y;
  double WindowLength;
  double hopLength;
  double NFFT;
  int i;
  int i1;
  int sizes_idx_0;
  int loop_ub;
  int n;
  emxArray_real_T *logSpacedFrequency;
  double d;
  emxArray_real_T *q;
  double u0;
  double u1;
  int vlen;
  emxArray_real_T *linSpacedFrequency;
  emxArray_real_T *bwTemp;
  emxArray_real_T *aFilt;
  int idx;
  boolean_T exitg1;
  int wBandEdges_idx_0;
  emxArray_real_T *h;
  emxArray_real_T *b_q;
  emxArray_real_T *delta;
  emxArray_real_T *b_x;
  emxArray_boolean_T *c_q;
  emxArray_real_T *domain;
  emxArray_real_T *b_y;
  emxArray_real_T *r;
  int numToPad_data[1];
  int numToPad_size[2];
  emxArray_creal_T *Y;
  int b_loop_ub;
  emxArray_real_T *Ylog;
  boolean_T empty_non_axis_sizes;
  emxArray_creal_T *r1;
  emxArray_creal_T *r2;
  emxArray_creal_T *b_Y;
  emxArray_real_T *varargin_1;
  boolean_T guard1 = false;
  cell_wrap_5 reshapes[2];
  int i2;
  emxArray_int32_T *r3;
  int i3;
  int b_n;
  if (isInitialized_main_pef == false) {
    main_pef_initialize();
  }

  emxInit_real_T(&y, 2);
  WindowLength = rt_roundd_snf(fs * 0.052);
  hopLength = WindowLength - rt_roundd_snf(fs * 0.041999999999999996);
  NFFT = ceil(((double)x->size[0] - WindowLength) / hopLength);
  i = (int)WindowLength;
  i1 = y->size[0] * y->size[1];
  y->size[0] = i;
  sizes_idx_0 = (int)(NFFT + 1.0);
  y->size[1] = sizes_idx_0;
  emxEnsureCapacity_real_T(y, i1);
  loop_ub = i * sizes_idx_0;
  for (i = 0; i < loop_ub; i++) {
    y->data[i] = 0.0;
  }

  for (n = 0; n < sizes_idx_0; n++) {
    d = hopLength * (((double)n + 1.0) - 1.0);
    u0 = WindowLength + d;
    u1 = x->size[0];
    if (u0 < u1) {
      u1 = u0;
    }

    if (d + 1.0 > u1) {
      i = 1;
      i1 = 0;
    } else {
      i = (int)(d + 1.0);
      i1 = (int)u1;
    }

    vlen = (int)(((double)n + 1.0) + 0.0 * (NFFT + 1.0)) - 1;
    loop_ub = (i1 - i) + 1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      y->data[i1 + y->size[0] * vlen] = x->data[(i + i1) - 1];
    }
  }

  emxInit_real_T(&logSpacedFrequency, 1);
  emxInit_real_T(&q, 2);
  WindowLength = nextpow2(2.0 * WindowLength - 1.0);
  NFFT = rt_powd_snf(2.0, WindowLength);
  u0 = fs / 2.0 - 1.0;
  if (!(u0 < 4000.0)) {
    u0 = 4000.0;
  }

  logspace(log10(u0), NFFT, q);
  i = logSpacedFrequency->size[0];
  logSpacedFrequency->size[0] = q->size[1];
  emxEnsureCapacity_real_T(logSpacedFrequency, i);
  loop_ub = q->size[1];
  for (i = 0; i < loop_ub; i++) {
    logSpacedFrequency->data[i] = q->data[i];
  }

  emxInit_real_T(&linSpacedFrequency, 1);
  linspace(fs / 2.0, rt_roundd_snf(NFFT / 2.0) + 1.0, q);
  i = linSpacedFrequency->size[0];
  linSpacedFrequency->size[0] = q->size[1];
  emxEnsureCapacity_real_T(linSpacedFrequency, i);
  loop_ub = q->size[1];
  for (i = 0; i < loop_ub; i++) {
    linSpacedFrequency->data[i] = q->data[i];
  }

  emxInit_real_T(&bwTemp, 1);
  emxInit_real_T(&aFilt, 1);
  loop_ub = logSpacedFrequency->size[0];
  i = aFilt->size[0];
  aFilt->size[0] = logSpacedFrequency->size[0];
  emxEnsureCapacity_real_T(aFilt, i);
  for (i = 0; i < loop_ub; i++) {
    aFilt->data[i] = logSpacedFrequency->data[i] - 50.0;
  }

  i = aFilt->size[0];
  i1 = bwTemp->size[0];
  bwTemp->size[0] = aFilt->size[0];
  emxEnsureCapacity_real_T(bwTemp, i1);
  for (sizes_idx_0 = 0; sizes_idx_0 < i; sizes_idx_0++) {
    bwTemp->data[sizes_idx_0] = fabs(aFilt->data[sizes_idx_0]);
  }

  n = bwTemp->size[0];
  if (bwTemp->size[0] <= 2) {
    if (bwTemp->size[0] == 1) {
      idx = 1;
    } else if ((bwTemp->data[0] > bwTemp->data[1]) || (rtIsNaN(bwTemp->data[0]) &&
                (!rtIsNaN(bwTemp->data[1])))) {
      idx = 2;
    } else {
      idx = 1;
    }
  } else {
    if (!rtIsNaN(bwTemp->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      sizes_idx_0 = 2;
      exitg1 = false;
      while ((!exitg1) && (sizes_idx_0 <= bwTemp->size[0])) {
        if (!rtIsNaN(bwTemp->data[sizes_idx_0 - 1])) {
          idx = sizes_idx_0;
          exitg1 = true;
        } else {
          sizes_idx_0++;
        }
      }
    }

    if (idx == 0) {
      idx = 1;
    } else {
      WindowLength = bwTemp->data[idx - 1];
      i = idx + 1;
      for (sizes_idx_0 = i; sizes_idx_0 <= n; sizes_idx_0++) {
        d = bwTemp->data[sizes_idx_0 - 1];
        if (WindowLength > d) {
          WindowLength = d;
          idx = sizes_idx_0;
        }
      }
    }
  }

  wBandEdges_idx_0 = idx;
  i = aFilt->size[0];
  aFilt->size[0] = logSpacedFrequency->size[0];
  emxEnsureCapacity_real_T(aFilt, i);
  for (i = 0; i < loop_ub; i++) {
    aFilt->data[i] = logSpacedFrequency->data[i] - 400.0;
  }

  i = aFilt->size[0];
  i1 = bwTemp->size[0];
  bwTemp->size[0] = aFilt->size[0];
  emxEnsureCapacity_real_T(bwTemp, i1);
  for (sizes_idx_0 = 0; sizes_idx_0 < i; sizes_idx_0++) {
    bwTemp->data[sizes_idx_0] = fabs(aFilt->data[sizes_idx_0]);
  }

  n = bwTemp->size[0];
  if (bwTemp->size[0] <= 2) {
    if (bwTemp->size[0] == 1) {
      idx = 1;
    } else if ((bwTemp->data[0] > bwTemp->data[1]) || (rtIsNaN(bwTemp->data[0]) &&
                (!rtIsNaN(bwTemp->data[1])))) {
      idx = 2;
    } else {
      idx = 1;
    }
  } else {
    if (!rtIsNaN(bwTemp->data[0])) {
      idx = 1;
    } else {
      idx = 0;
      sizes_idx_0 = 2;
      exitg1 = false;
      while ((!exitg1) && (sizes_idx_0 <= bwTemp->size[0])) {
        if (!rtIsNaN(bwTemp->data[sizes_idx_0 - 1])) {
          idx = sizes_idx_0;
          exitg1 = true;
        } else {
          sizes_idx_0++;
        }
      }
    }

    if (idx == 0) {
      idx = 1;
    } else {
      WindowLength = bwTemp->data[idx - 1];
      i = idx + 1;
      for (sizes_idx_0 = i; sizes_idx_0 <= n; sizes_idx_0++) {
        d = bwTemp->data[sizes_idx_0 - 1];
        if (WindowLength > d) {
          WindowLength = d;
          idx = sizes_idx_0;
        }
      }
    }
  }

  if (3 > logSpacedFrequency->size[0]) {
    i = 0;
    i1 = 0;
  } else {
    i = 2;
    i1 = logSpacedFrequency->size[0];
  }

  loop_ub = i1 - i;
  i1 = bwTemp->size[0];
  bwTemp->size[0] = loop_ub;
  emxEnsureCapacity_real_T(bwTemp, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    bwTemp->data[i1] = (logSpacedFrequency->data[i + i1] -
                        logSpacedFrequency->data[i1]) / 2.0;
  }

  emxInit_real_T(&h, 2);
  b_logspace(rt_roundd_snf((double)(unsigned int)logSpacedFrequency->size[0] /
              2.0), q);
  i = h->size[0] * h->size[1];
  h->size[0] = 1;
  h->size[1] = q->size[1];
  emxEnsureCapacity_real_T(h, i);
  loop_ub = q->size[0] * q->size[1];
  for (i = 0; i < loop_ub; i++) {
    h->data[i] = 6.2831853071795862 * q->data[i];
  }

  n = h->size[1];
  for (sizes_idx_0 = 0; sizes_idx_0 < n; sizes_idx_0++) {
    h->data[sizes_idx_0] = cos(h->data[sizes_idx_0]);
  }

  i = h->size[0] * h->size[1];
  i1 = h->size[0] * h->size[1];
  h->size[0] = 1;
  emxEnsureCapacity_real_T(h, i1);
  loop_ub = i - 1;
  for (i = 0; i <= loop_ub; i++) {
    h->data[i] = 1.0 / (1.8 - h->data[i]);
  }

  if (1 > q->size[1] - 1) {
    loop_ub = 1;
  } else {
    loop_ub = q->size[1];
  }

  i = (2 <= q->size[1]);
  emxInit_real_T(&b_q, 2);
  i1 = b_q->size[0] * b_q->size[1];
  b_q->size[0] = 1;
  b_q->size[1] = loop_ub + 1;
  emxEnsureCapacity_real_T(b_q, i1);
  b_q->data[0] = q->data[0];
  for (i1 = 0; i1 <= loop_ub - 2; i1++) {
    b_q->data[i1 + 1] = (q->data[i1] + q->data[i + i1]) / 2.0;
  }

  emxInit_real_T(&delta, 2);
  emxInit_real_T(&b_x, 2);
  b_q->data[loop_ub] = q->data[q->size[1] - 1];
  diff(b_q, delta);
  i = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 1;
  b_x->size[1] = h->size[1];
  emxEnsureCapacity_real_T(b_x, i);
  loop_ub = h->size[0] * h->size[1];
  emxFree_real_T(&b_q);
  for (i = 0; i < loop_ub; i++) {
    b_x->data[i] = h->data[i] * delta->data[i];
  }

  vlen = b_x->size[1];
  if (b_x->size[1] == 0) {
    WindowLength = 0.0;
  } else {
    WindowLength = b_x->data[0];
    for (sizes_idx_0 = 2; sizes_idx_0 <= vlen; sizes_idx_0++) {
      WindowLength += b_x->data[sizes_idx_0 - 1];
    }
  }

  emxFree_real_T(&b_x);
  vlen = delta->size[1];
  if (delta->size[1] == 0) {
    hopLength = 0.0;
  } else {
    hopLength = delta->data[0];
    for (sizes_idx_0 = 2; sizes_idx_0 <= vlen; sizes_idx_0++) {
      hopLength += delta->data[sizes_idx_0 - 1];
    }
  }

  emxFree_real_T(&delta);
  WindowLength /= hopLength;
  i = aFilt->size[0];
  aFilt->size[0] = h->size[1];
  emxEnsureCapacity_real_T(aFilt, i);
  loop_ub = h->size[1];
  for (i = 0; i < loop_ub; i++) {
    aFilt->data[i] = h->data[i] - WindowLength;
  }

  emxFree_real_T(&h);
  emxInit_boolean_T(&c_q, 2);
  i = c_q->size[0] * c_q->size[1];
  c_q->size[0] = 1;
  c_q->size[1] = q->size[1];
  emxEnsureCapacity_boolean_T(c_q, i);
  loop_ub = q->size[0] * q->size[1];
  for (i = 0; i < loop_ub; i++) {
    c_q->data[i] = (q->data[i] < 1.0);
  }

  emxInit_real_T(&domain, 2);
  emxInit_real_T(&b_y, 2);
  emxInit_real_T(&r, 1);
  eml_find(c_q, numToPad_data, numToPad_size);
  hamming(y->size[0], r);
  repmat(r, y->size[1], domain);
  i = b_y->size[0] * b_y->size[1];
  b_y->size[0] = y->size[0];
  b_y->size[1] = y->size[1];
  emxEnsureCapacity_real_T(b_y, i);
  loop_ub = y->size[0] * y->size[1];
  emxFree_real_T(&r);
  emxFree_boolean_T(&c_q);
  for (i = 0; i < loop_ub; i++) {
    b_y->data[i] = y->data[i] * domain->data[i];
  }

  emxInit_creal_T(&Y, 2);
  fft(b_y, NFFT, Y);
  loop_ub = (int)(NFFT / 2.0 + 1.0);
  if (1 > y->size[1]) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = y->size[1];
  }

  i = b_y->size[0] * b_y->size[1];
  b_y->size[0] = loop_ub;
  b_y->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_y, i);
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_y->data[i1 + b_y->size[0] * i] = Y->data[i1 + Y->size[0] * i].re *
        Y->data[i1 + Y->size[0] * i].re - Y->data[i1 + Y->size[0] * i].im *
        -Y->data[i1 + Y->size[0] * i].im;
    }
  }

  emxInit_real_T(&Ylog, 2);
  interp1(linSpacedFrequency, b_y, logSpacedFrequency, Ylog);
  i = linSpacedFrequency->size[0];
  linSpacedFrequency->size[0] = bwTemp->size[0] + 2;
  emxEnsureCapacity_real_T(linSpacedFrequency, i);
  linSpacedFrequency->data[0] = bwTemp->data[0] / NFFT;
  loop_ub = bwTemp->size[0];
  for (i = 0; i < loop_ub; i++) {
    linSpacedFrequency->data[i + 1] = bwTemp->data[i] / NFFT;
  }

  linSpacedFrequency->data[bwTemp->size[0] + 1] = bwTemp->data[bwTemp->size[0] -
    1] / NFFT;
  repmat(linSpacedFrequency, y->size[1], domain);
  loop_ub = Ylog->size[0] * Ylog->size[1];
  emxFree_real_T(&bwTemp);
  for (i = 0; i < loop_ub; i++) {
    Ylog->data[i] *= domain->data[i];
  }

  if ((numToPad_data[0] != 0) && (Ylog->size[1] != 0)) {
    vlen = Ylog->size[1];
  } else if ((Ylog->size[0] != 0) && (Ylog->size[1] != 0)) {
    vlen = Ylog->size[1];
  } else {
    vlen = Ylog->size[1];
    if (vlen <= 0) {
      vlen = 0;
    }

    if (Ylog->size[1] > vlen) {
      vlen = Ylog->size[1];
    }
  }

  empty_non_axis_sizes = (vlen == 0);
  if (empty_non_axis_sizes || ((numToPad_data[0] != 0) && (Ylog->size[1] != 0)))
  {
    n = numToPad_data[0];
  } else {
    n = 0;
  }

  if (empty_non_axis_sizes || ((Ylog->size[0] != 0) && (Ylog->size[1] != 0))) {
    sizes_idx_0 = Ylog->size[0];
  } else {
    sizes_idx_0 = 0;
  }

  i = y->size[0] * y->size[1];
  y->size[0] = n + sizes_idx_0;
  y->size[1] = vlen;
  emxEnsureCapacity_real_T(y, i);
  for (i = 0; i < vlen; i++) {
    for (i1 = 0; i1 < n; i1++) {
      y->data[i1 + y->size[0] * i] = 0.0;
    }
  }

  for (i = 0; i < vlen; i++) {
    for (i1 = 0; i1 < sizes_idx_0; i1++) {
      y->data[(i1 + n) + y->size[0] * i] = Ylog->data[i1 + sizes_idx_0 * i];
    }
  }

  emxFree_real_T(&Ylog);
  emxInit_creal_T(&r1, 1);
  vlen = y->size[0];
  n = aFilt->size[0];
  if (vlen > n) {
    n = vlen;
  }

  vlen = n - 1;
  if (idx < vlen) {
    vlen = idx;
  }

  WindowLength = nextpow2(2.0 * (double)n - 1.0);
  u0 = rt_powd_snf(2.0, WindowLength);
  u1 = NFFT * 4.0;
  if ((u0 < u1) || rtIsNaN(u1)) {
    WindowLength = u0;
  } else {
    WindowLength = u1;
  }

  fft(y, WindowLength, Y);
  b_fft(aFilt, WindowLength, r1);
  loop_ub = r1->size[0];
  for (i = 0; i < loop_ub; i++) {
    r1->data[i].im = -r1->data[i].im;
  }

  emxInit_creal_T(&r2, 2);
  emxInit_creal_T(&b_Y, 2);
  b_repmat(r1, Y->size[1], r2);
  i = b_Y->size[0] * b_Y->size[1];
  b_Y->size[0] = Y->size[0];
  b_Y->size[1] = Y->size[1];
  emxEnsureCapacity_creal_T(b_Y, i);
  loop_ub = Y->size[0] * Y->size[1];
  emxFree_creal_T(&r1);
  for (i = 0; i < loop_ub; i++) {
    b_Y->data[i].re = Y->data[i].re * r2->data[i].re - Y->data[i].im * r2->
      data[i].im;
    b_Y->data[i].im = Y->data[i].re * r2->data[i].im + Y->data[i].im * r2->
      data[i].re;
  }

  emxFree_creal_T(&Y);
  ifft(b_Y, r2);
  i = y->size[0] * y->size[1];
  y->size[0] = r2->size[0];
  y->size[1] = r2->size[1];
  emxEnsureCapacity_real_T(y, i);
  loop_ub = r2->size[0] * r2->size[1];
  emxFree_creal_T(&b_Y);
  for (i = 0; i < loop_ub; i++) {
    y->data[i] = r2->data[i].re;
  }

  emxFree_creal_T(&r2);
  if (1.0 > (double)vlen + 1.0) {
    loop_ub = 0;
  } else {
    loop_ub = vlen + 1;
  }

  if (vlen < 1) {
    q->size[0] = 1;
    q->size[1] = 0;
  } else {
    i = q->size[0] * q->size[1];
    q->size[0] = 1;
    b_loop_ub = vlen - 1;
    q->size[1] = b_loop_ub + 1;
    emxEnsureCapacity_real_T(q, i);
    for (i = 0; i <= b_loop_ub; i++) {
      q->data[i] = (double)i + 1.0;
    }
  }

  emxInit_real_T(&varargin_1, 2);
  WindowLength -= (double)vlen;
  b_loop_ub = y->size[1];
  i = varargin_1->size[0] * varargin_1->size[1];
  varargin_1->size[0] = q->size[1];
  varargin_1->size[1] = y->size[1];
  emxEnsureCapacity_real_T(varargin_1, i);
  for (i = 0; i < b_loop_ub; i++) {
    vlen = q->size[1];
    for (i1 = 0; i1 < vlen; i1++) {
      varargin_1->data[i1 + varargin_1->size[0] * i] = y->data[((int)
        (WindowLength + q->data[i1]) + y->size[0] * i) - 1];
    }
  }

  i = linSpacedFrequency->size[0];
  linSpacedFrequency->size[0] = q->size[1];
  emxEnsureCapacity_real_T(linSpacedFrequency, i);
  b_loop_ub = q->size[1];
  for (i = 0; i < b_loop_ub; i++) {
    linSpacedFrequency->data[i] = q->data[i];
  }

  if ((linSpacedFrequency->size[0] != 0) && (y->size[1] != 0)) {
    vlen = y->size[1];
  } else if ((loop_ub != 0) && (y->size[1] != 0)) {
    vlen = y->size[1];
  } else {
    if (y->size[1] > 0) {
      vlen = y->size[1];
    } else {
      vlen = 0;
    }

    if (y->size[1] > vlen) {
      vlen = y->size[1];
    }
  }

  empty_non_axis_sizes = (vlen == 0);
  guard1 = false;
  if (empty_non_axis_sizes) {
    guard1 = true;
  } else {
    i = linSpacedFrequency->size[0];
    linSpacedFrequency->size[0] = q->size[1];
    emxEnsureCapacity_real_T(linSpacedFrequency, i);
    b_loop_ub = q->size[1];
    for (i = 0; i < b_loop_ub; i++) {
      linSpacedFrequency->data[i] = q->data[i];
    }

    if ((linSpacedFrequency->size[0] != 0) && (y->size[1] != 0)) {
      guard1 = true;
    } else {
      n = 0;
    }
  }

  if (guard1) {
    i = linSpacedFrequency->size[0];
    linSpacedFrequency->size[0] = q->size[1];
    emxEnsureCapacity_real_T(linSpacedFrequency, i);
    b_loop_ub = q->size[1];
    for (i = 0; i < b_loop_ub; i++) {
      linSpacedFrequency->data[i] = q->data[i];
    }

    n = linSpacedFrequency->size[0];
  }

  emxFree_real_T(&linSpacedFrequency);
  if (empty_non_axis_sizes || ((loop_ub != 0) && (y->size[1] != 0))) {
    sizes_idx_0 = loop_ub;
  } else {
    sizes_idx_0 = 0;
  }

  b_loop_ub = y->size[1] - 1;
  i = b_y->size[0] * b_y->size[1];
  b_y->size[0] = loop_ub;
  b_y->size[1] = y->size[1];
  emxEnsureCapacity_real_T(b_y, i);
  for (i = 0; i <= b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_y->data[i1 + b_y->size[0] * i] = y->data[i1 + y->size[0] * i];
    }
  }

  i = y->size[0] * y->size[1];
  y->size[0] = b_y->size[0];
  y->size[1] = b_y->size[1];
  emxEnsureCapacity_real_T(y, i);
  loop_ub = b_y->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_y->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      y->data[i1 + y->size[0] * i] = b_y->data[i1 + b_y->size[0] * i];
    }
  }

  emxFree_real_T(&b_y);
  emxInitMatrix_cell_wrap_5(reshapes);
  i = reshapes[1].f1->size[0] * reshapes[1].f1->size[1];
  reshapes[1].f1->size[0] = sizes_idx_0;
  reshapes[1].f1->size[1] = vlen;
  emxEnsureCapacity_real_T(reshapes[1].f1, i);
  loop_ub = sizes_idx_0 * vlen;
  for (i = 0; i < loop_ub; i++) {
    reshapes[1].f1->data[i] = y->data[i];
  }

  i = y->size[0] * y->size[1];
  y->size[0] = n + reshapes[1].f1->size[0];
  y->size[1] = vlen;
  emxEnsureCapacity_real_T(y, i);
  for (i = 0; i < vlen; i++) {
    for (i1 = 0; i1 < n; i1++) {
      y->data[i1 + y->size[0] * i] = varargin_1->data[i1 + n * i];
    }
  }

  emxFree_real_T(&varargin_1);
  loop_ub = reshapes[1].f1->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = reshapes[1].f1->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      y->data[(i1 + n) + y->size[0] * i] = reshapes[1].f1->data[i1 + reshapes[1]
        .f1->size[0] * i];
    }
  }

  emxFreeMatrix_cell_wrap_5(reshapes);
  if ((double)idx + 1.0 > y->size[0]) {
    i = 0;
    i1 = 0;
  } else {
    i = idx;
    i1 = y->size[0];
  }

  loop_ub = y->size[1];
  b_loop_ub = i1 - i;
  i1 = domain->size[0] * domain->size[1];
  domain->size[0] = b_loop_ub;
  domain->size[1] = y->size[1];
  emxEnsureCapacity_real_T(domain, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    for (sizes_idx_0 = 0; sizes_idx_0 < b_loop_ub; sizes_idx_0++) {
      domain->data[sizes_idx_0 + domain->size[0] * i1] = y->data[(i +
        sizes_idx_0) + y->size[0] * i1];
    }
  }

  loop_ub = y->size[1];
  i = aFilt->size[0];
  aFilt->size[0] = y->size[1];
  emxEnsureCapacity_real_T(aFilt, i);
  for (i = 0; i < loop_ub; i++) {
    aFilt->data[i] = 0.0;
  }

  loop_ub = y->size[1];
  i = conf->size[0];
  conf->size[0] = y->size[1];
  emxEnsureCapacity_real_T(conf, i);
  for (i = 0; i < loop_ub; i++) {
    conf->data[i] = 0.0;
  }

  i = y->size[1] - 1;
  if (0 <= y->size[1] - 1) {
    if (wBandEdges_idx_0 > idx) {
      i2 = -1;
      i3 = -1;
    } else {
      i2 = wBandEdges_idx_0 - 2;
      i3 = idx - 1;
    }

    b_n = i3 - i2;
  }

  emxFree_real_T(&y);
  emxInit_int32_T(&r3, 1);
  for (vlen = 0; vlen <= i; vlen++) {
    if (i3 - i2 <= 2) {
      if (i3 - i2 == 1) {
        conf->data[vlen] = domain->data[(i2 + domain->size[0] * vlen) + 1];
        n = 1;
      } else {
        d = domain->data[(i2 + domain->size[0] * vlen) + 2];
        WindowLength = domain->data[(i2 + domain->size[0] * vlen) + 1];
        if ((WindowLength < d) || (rtIsNaN(domain->data[(i2 + domain->size[0] *
               vlen) + 1]) && (!rtIsNaN(d)))) {
          conf->data[vlen] = d;
          n = 2;
        } else {
          conf->data[vlen] = WindowLength;
          n = 1;
        }
      }
    } else {
      d = domain->data[(i2 + domain->size[0] * vlen) + 1];
      if (!rtIsNaN(d)) {
        n = 1;
      } else {
        n = 0;
        sizes_idx_0 = 2;
        exitg1 = false;
        while ((!exitg1) && (sizes_idx_0 <= i3 - i2)) {
          if (!rtIsNaN(domain->data[(i2 + sizes_idx_0) + domain->size[0] * vlen]))
          {
            n = sizes_idx_0;
            exitg1 = true;
          } else {
            sizes_idx_0++;
          }
        }
      }

      if (n == 0) {
        conf->data[vlen] = d;
        n = 1;
      } else {
        WindowLength = domain->data[(i2 + n) + domain->size[0] * vlen];
        i1 = n + 1;
        for (sizes_idx_0 = i1; sizes_idx_0 <= b_n; sizes_idx_0++) {
          d = domain->data[(i2 + sizes_idx_0) + domain->size[0] * vlen];
          if (WindowLength < d) {
            WindowLength = d;
            n = sizes_idx_0;
          }
        }

        conf->data[vlen] = WindowLength;
      }
    }

    u0 = ((double)n - 1.0) + (double)wBandEdges_idx_0;
    u1 = wBandEdges_idx_0;
    if (u0 > u1) {
      u1 = u0;
    }

    u0 = ((double)n + 1.0) + (double)wBandEdges_idx_0;
    WindowLength = idx;
    if (u0 < WindowLength) {
      WindowLength = u0;
    }

    if (WindowLength < u1) {
      q->size[0] = 1;
      q->size[1] = 0;
    } else if (u1 == u1) {
      i1 = q->size[0] * q->size[1];
      q->size[0] = 1;
      loop_ub = (int)(WindowLength - u1);
      q->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(q, i1);
      for (i1 = 0; i1 <= loop_ub; i1++) {
        q->data[i1] = u1 + (double)i1;
      }
    } else {
      eml_float_colon(u1, WindowLength, q);
    }

    i1 = r3->size[0];
    r3->size[0] = q->size[1];
    emxEnsureCapacity_int32_T(r3, i1);
    loop_ub = q->size[1];
    for (i1 = 0; i1 < loop_ub; i1++) {
      r3->data[i1] = (int)q->data[i1];
    }

    loop_ub = r3->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      domain->data[(r3->data[i1] + domain->size[0] * vlen) - 1] = rtNaN;
    }

    aFilt->data[vlen] = ((double)wBandEdges_idx_0 + (double)n) - 1.0;
  }

  emxFree_int32_T(&r3);
  emxFree_real_T(&domain);
  emxFree_real_T(&q);
  i = f0->size[0];
  f0->size[0] = aFilt->size[0];
  emxEnsureCapacity_real_T(f0, i);
  loop_ub = aFilt->size[0];
  for (i = 0; i < loop_ub; i++) {
    f0->data[i] = logSpacedFrequency->data[(int)aFilt->data[i] - 1];
  }

  emxFree_real_T(&logSpacedFrequency);
  n = conf->size[0];
  for (vlen = 0; vlen < n; vlen++) {
    if (conf->data[vlen] < 0.0) {
      conf->data[vlen] = 0.0;
    }
  }

  sum(conf, aFilt);
  loop_ub = conf->size[0];
  for (i = 0; i < loop_ub; i++) {
    conf->data[i] /= aFilt->data[i];
  }

  emxFree_real_T(&aFilt);
}

/*
 * File trailer for main_pef.c
 *
 * [EOF]
 */
