/*
 * File: main_pef_initialize.c
 *
 * MATLAB Coder version            : 4.3
 * C/C++ source code generated on  : 01-Dec-2020 15:13:13
 */

/* Include Files */
#include "main_pef_initialize.h"
#include "main_pef.h"
#include "main_pef_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_pef_initialize(void)
{
  rt_InitInfAndNaN();
  isInitialized_main_pef = true;
}

/*
 * File trailer for main_pef_initialize.c
 *
 * [EOF]
 */
