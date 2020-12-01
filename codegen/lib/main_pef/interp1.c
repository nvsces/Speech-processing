/*
 * File: interp1.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "interp1.h"
#include "main_pef.h"
#include "main_pef_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *varargin_1
 *                const emxArray_real_T *varargin_2
 *                const emxArray_real_T *varargin_3
 *                emxArray_real_T *Vq
 * Return Type  : void
 */
void interp1(const emxArray_real_T *varargin_1, const emxArray_real_T
             *varargin_2, const emxArray_real_T *varargin_3, emxArray_real_T *Vq)
{
  emxArray_real_T *y;
  int i;
  int nd2;
  emxArray_real_T *x;
  int nyrows;
  int nycols;
  int nx;
  int k;
  int exitg1;
  int nxi;
  double xtmp;
  int offset;
  int j;
  int low_i;
  double b_y1;
  emxInit_real_T(&y, 2);
  i = y->size[0] * y->size[1];
  y->size[0] = varargin_2->size[0];
  y->size[1] = varargin_2->size[1];
  emxEnsureCapacity_real_T(y, i);
  nd2 = varargin_2->size[0] * varargin_2->size[1];
  for (i = 0; i < nd2; i++) {
    y->data[i] = varargin_2->data[i];
  }

  emxInit_real_T(&x, 1);
  i = x->size[0];
  x->size[0] = varargin_1->size[0];
  emxEnsureCapacity_real_T(x, i);
  nd2 = varargin_1->size[0];
  for (i = 0; i < nd2; i++) {
    x->data[i] = varargin_1->data[i];
  }

  nyrows = varargin_2->size[0];
  nycols = varargin_2->size[1] - 1;
  nx = varargin_1->size[0] - 1;
  i = Vq->size[0] * Vq->size[1];
  Vq->size[0] = varargin_3->size[0];
  Vq->size[1] = varargin_2->size[1];
  emxEnsureCapacity_real_T(Vq, i);
  nd2 = varargin_3->size[0] * varargin_2->size[1];
  for (i = 0; i < nd2; i++) {
    Vq->data[i] = rtNaN;
  }

  if (varargin_3->size[0] != 0) {
    k = 0;
    do {
      exitg1 = 0;
      if (k <= nx) {
        if (rtIsNaN(varargin_1->data[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (varargin_1->data[1] < varargin_1->data[0]) {
          i = (nx + 1) >> 1;
          for (nd2 = 0; nd2 < i; nd2++) {
            xtmp = x->data[nd2];
            offset = nx - nd2;
            x->data[nd2] = x->data[offset];
            x->data[offset] = xtmp;
          }

          if ((varargin_2->size[1] != 0) && (varargin_2->size[0] > 1)) {
            nx = varargin_2->size[0] - 1;
            nd2 = varargin_2->size[0] >> 1;
            i = varargin_2->size[1] - 1;
            for (j = 0; j <= i; j++) {
              offset = j * varargin_2->size[0];
              for (k = 0; k < nd2; k++) {
                nxi = offset + k;
                xtmp = y->data[nxi];
                low_i = (offset + nx) - k;
                y->data[nxi] = y->data[low_i];
                y->data[low_i] = xtmp;
              }
            }
          }
        }

        nxi = varargin_3->size[0];
        for (k = 0; k < nxi; k++) {
          if (rtIsNaN(varargin_3->data[k])) {
            for (j = 0; j <= nycols; j++) {
              Vq->data[k + j * nxi] = rtNaN;
            }
          } else {
            if ((!(varargin_3->data[k] > x->data[x->size[0] - 1])) &&
                (!(varargin_3->data[k] < x->data[0]))) {
              nd2 = x->size[0];
              low_i = 1;
              offset = 2;
              while (nd2 > offset) {
                nx = (low_i >> 1) + (nd2 >> 1);
                if (((low_i & 1) == 1) && ((nd2 & 1) == 1)) {
                  nx++;
                }

                if (varargin_3->data[k] >= x->data[nx - 1]) {
                  low_i = nx;
                  offset = nx + 1;
                } else {
                  nd2 = nx;
                }
              }

              xtmp = x->data[low_i - 1];
              xtmp = (varargin_3->data[k] - xtmp) / (x->data[low_i] - xtmp);
              if (xtmp == 0.0) {
                for (j = 0; j <= nycols; j++) {
                  Vq->data[k + j * nxi] = y->data[(low_i + j * nyrows) - 1];
                }
              } else if (xtmp == 1.0) {
                for (j = 0; j <= nycols; j++) {
                  Vq->data[k + j * nxi] = y->data[low_i + j * nyrows];
                }
              } else {
                for (j = 0; j <= nycols; j++) {
                  nd2 = low_i + j * nyrows;
                  b_y1 = y->data[nd2 - 1];
                  if (b_y1 == y->data[nd2]) {
                    Vq->data[k + j * nxi] = b_y1;
                  } else {
                    Vq->data[k + j * nxi] = (1.0 - xtmp) * b_y1 + xtmp * y->
                      data[nd2];
                  }
                }
              }
            }
          }
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  emxFree_real_T(&x);
  emxFree_real_T(&y);
}

/*
 * File trailer for interp1.c
 *
 * [EOF]
 */
