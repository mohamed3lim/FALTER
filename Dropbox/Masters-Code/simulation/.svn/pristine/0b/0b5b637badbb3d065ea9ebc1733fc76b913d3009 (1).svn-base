/* Include files */

#include <stddef.h>
#include "blas.h"
#include "falter_library_sfun.h"
#include "c3_falter_library.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "falter_library_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c3_debug_family_names[9] = { "l", "At", "i", "nargin",
  "nargout", "Plane", "Position", "Directions", "Dt" };

/* Function Declarations */
static void initialize_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance);
static void initialize_params_c3_falter_library
  (SFc3_falter_libraryInstanceStruct *chartInstance);
static void enable_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance);
static void disable_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance);
static void c3_update_debugger_state_c3_falter_library
  (SFc3_falter_libraryInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_falter_library
  (SFc3_falter_libraryInstanceStruct *chartInstance);
static void set_sim_state_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance);
static void sf_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance);
static void initSimStructsc3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance);
static void registerMessagesc3_falter_library(SFc3_falter_libraryInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct *chartInstance,
  const mxArray *c3_Dt, const char_T *c3_identifier, real_T c3_y[17]);
static void c3_b_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[17]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_c_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_d_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[9]);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[90]);
static void c3_b_info_helper(c3_ResolvedFunctionInfo c3_info[90]);
static void c3_realmin(SFc3_falter_libraryInstanceStruct *chartInstance);
static void c3_eps(SFc3_falter_libraryInstanceStruct *chartInstance);
static void c3_eml_matlab_zgetrf(SFc3_falter_libraryInstanceStruct
  *chartInstance, real_T c3_A[9], real_T c3_b_A[9], int32_T c3_ipiv[3], int32_T *
  c3_info);
static void c3_check_forloop_overflow_error(SFc3_falter_libraryInstanceStruct
  *chartInstance, boolean_T c3_overflow);
static void c3_eml_xger(SFc3_falter_libraryInstanceStruct *chartInstance,
  int32_T c3_m, int32_T c3_n, real_T c3_alpha1, int32_T c3_ix0, int32_T c3_iy0,
  real_T c3_A[9], int32_T c3_ia0, real_T c3_b_A[9]);
static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_e_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_f_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_falter_library, const char_T *
  c3_identifier);
static uint8_T c3_g_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_eml_matlab_zgetrf(SFc3_falter_libraryInstanceStruct
  *chartInstance, real_T c3_A[9], int32_T c3_ipiv[3], int32_T *c3_info);
static void c3_b_eml_xger(SFc3_falter_libraryInstanceStruct *chartInstance,
  int32_T c3_m, int32_T c3_n, real_T c3_alpha1, int32_T c3_ix0, int32_T c3_iy0,
  real_T c3_A[9], int32_T c3_ia0);
static void init_dsm_address_info(SFc3_falter_libraryInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_is_active_c3_falter_library = 0U;
}

static void initialize_params_c3_falter_library
  (SFc3_falter_libraryInstanceStruct *chartInstance)
{
}

static void enable_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_falter_library
  (SFc3_falter_libraryInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c3_falter_library
  (SFc3_falter_libraryInstanceStruct *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  int32_T c3_i0;
  real_T c3_u[17];
  const mxArray *c3_b_y = NULL;
  uint8_T c3_hoistedGlobal;
  uint8_T c3_b_u;
  const mxArray *c3_c_y = NULL;
  real_T (*c3_Dt)[17];
  c3_Dt = (real_T (*)[17])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(2), FALSE);
  for (c3_i0 = 0; c3_i0 < 17; c3_i0++) {
    c3_u[c3_i0] = (*c3_Dt)[c3_i0];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 17), FALSE);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_hoistedGlobal = chartInstance->c3_is_active_c3_falter_library;
  c3_b_u = c3_hoistedGlobal;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  sf_mex_assign(&c3_st, c3_y, FALSE);
  return c3_st;
}

static void set_sim_state_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T c3_dv0[17];
  int32_T c3_i1;
  real_T (*c3_Dt)[17];
  c3_Dt = (real_T (*)[17])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)), "Dt",
                      c3_dv0);
  for (c3_i1 = 0; c3_i1 < 17; c3_i1++) {
    (*c3_Dt)[c3_i1] = c3_dv0[c3_i1];
  }

  chartInstance->c3_is_active_c3_falter_library = c3_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
     "is_active_c3_falter_library");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_falter_library(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance)
{
}

static void sf_c3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance)
{
  int32_T c3_i2;
  int32_T c3_i3;
  int32_T c3_i4;
  int32_T c3_i5;
  int32_T c3_i6;
  real_T c3_Plane[6];
  int32_T c3_i7;
  real_T c3_Position[3];
  int32_T c3_i8;
  real_T c3_Directions[51];
  uint32_T c3_debug_family_var_map[9];
  real_T c3_l;
  real_T c3_At[9];
  real_T c3_i;
  real_T c3_nargin = 3.0;
  real_T c3_nargout = 1.0;
  real_T c3_Dt[17];
  int32_T c3_i9;
  int32_T c3_i10;
  int32_T c3_i11;
  int32_T c3_i12;
  int32_T c3_i13;
  int32_T c3_b_i;
  int32_T c3_i14;
  real_T c3_x[9];
  int32_T c3_info;
  int32_T c3_ipiv[3];
  real_T c3_y;
  int32_T c3_k;
  real_T c3_b_k;
  real_T c3_a;
  real_T c3_b;
  boolean_T c3_isodd;
  int32_T c3_c_k;
  int32_T c3_b_a;
  real_T c3_b_b;
  int32_T c3_c_a;
  real_T c3_c_b;
  int32_T c3_idx;
  real_T c3_flt;
  boolean_T c3_p;
  int32_T c3_i15;
  real_T (*c3_b_Dt)[17];
  real_T (*c3_b_Directions)[51];
  real_T (*c3_b_Position)[3];
  real_T (*c3_b_Plane)[6];
  c3_b_Directions = (real_T (*)[51])ssGetInputPortSignal(chartInstance->S, 2);
  c3_b_Position = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c3_b_Dt = (real_T (*)[17])ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_Plane = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i2 = 0; c3_i2 < 6; c3_i2++) {
    _SFD_DATA_RANGE_CHECK((*c3_b_Plane)[c3_i2], 0U);
  }

  for (c3_i3 = 0; c3_i3 < 17; c3_i3++) {
    _SFD_DATA_RANGE_CHECK((*c3_b_Dt)[c3_i3], 1U);
  }

  for (c3_i4 = 0; c3_i4 < 3; c3_i4++) {
    _SFD_DATA_RANGE_CHECK((*c3_b_Position)[c3_i4], 2U);
  }

  for (c3_i5 = 0; c3_i5 < 51; c3_i5++) {
    _SFD_DATA_RANGE_CHECK((*c3_b_Directions)[c3_i5], 3U);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i6 = 0; c3_i6 < 6; c3_i6++) {
    c3_Plane[c3_i6] = (*c3_b_Plane)[c3_i6];
  }

  for (c3_i7 = 0; c3_i7 < 3; c3_i7++) {
    c3_Position[c3_i7] = (*c3_b_Position)[c3_i7];
  }

  for (c3_i8 = 0; c3_i8 < 51; c3_i8++) {
    c3_Directions[c3_i8] = (*c3_b_Directions)[c3_i8];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_l, 0U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_At, 1U, c3_f_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_i, 2U, c3_e_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 3U, c3_e_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 4U, c3_e_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_Plane, 5U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_Position, 6U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_Directions, 7U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_Dt, 8U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 4);
  c3_l = 17.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 5);
  for (c3_i9 = 0; c3_i9 < 17; c3_i9++) {
    c3_Dt[c3_i9] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 6);
  c3_i10 = 0;
  for (c3_i11 = 0; c3_i11 < 2; c3_i11++) {
    for (c3_i12 = 0; c3_i12 < 3; c3_i12++) {
      c3_At[c3_i12 + c3_i10] = c3_Plane[c3_i12 + c3_i10];
    }

    c3_i10 += 3;
  }

  for (c3_i13 = 0; c3_i13 < 3; c3_i13++) {
    c3_At[c3_i13 + 6] = c3_Position[c3_i13];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 8);
  c3_i = 1.0;
  c3_b_i = 0;
  while (c3_b_i < 17) {
    c3_i = 1.0 + (real_T)c3_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 9);
    for (c3_i14 = 0; c3_i14 < 9; c3_i14++) {
      c3_x[c3_i14] = c3_At[c3_i14];
    }

    c3_b_eml_matlab_zgetrf(chartInstance, c3_x, c3_ipiv, &c3_info);
    c3_y = c3_x[0];
    for (c3_k = 0; c3_k < 2; c3_k++) {
      c3_b_k = 2.0 + (real_T)c3_k;
      c3_a = c3_y;
      c3_b = c3_x[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c3_b_k), 1, 3, 1, 0) + 3 * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c3_b_k),
        1, 3, 2, 0) - 1)) - 1];
      c3_y = c3_a * c3_b;
    }

    c3_isodd = FALSE;
    for (c3_c_k = 0; c3_c_k < 2; c3_c_k++) {
      c3_b_k = 1.0 + (real_T)c3_c_k;
      c3_b_a = c3_ipiv[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c3_b_k), 1, 3, 1, 0) - 1];
      c3_b_b = c3_b_k;
      c3_c_a = c3_b_a;
      c3_c_b = c3_b_b;
      c3_idx = c3_c_a;
      c3_flt = c3_c_b;
      c3_p = ((real_T)c3_idx > c3_flt);
      if (c3_p) {
        c3_isodd = !c3_isodd;
      }
    }

    if (c3_isodd) {
      c3_y = -c3_y;
    }

    c3_Dt[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("Dt", (int32_T)
      _SFD_INTEGER_CHECK("i", c3_i), 1, 17, 1, 0) - 1] = c3_y;
    c3_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -9);
  _SFD_SYMBOL_SCOPE_POP();
  for (c3_i15 = 0; c3_i15 < 17; c3_i15++) {
    (*c3_b_Dt)[c3_i15] = c3_Dt[c3_i15];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_falter_libraryMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc3_falter_library(SFc3_falter_libraryInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc3_falter_library(SFc3_falter_libraryInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i16;
  real_T c3_b_inData[17];
  int32_T c3_i17;
  real_T c3_u[17];
  const mxArray *c3_y = NULL;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i16 = 0; c3_i16 < 17; c3_i16++) {
    c3_b_inData[c3_i16] = (*(real_T (*)[17])c3_inData)[c3_i16];
  }

  for (c3_i17 = 0; c3_i17 < 17; c3_i17++) {
    c3_u[c3_i17] = c3_b_inData[c3_i17];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 17), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct *chartInstance,
  const mxArray *c3_Dt, const char_T *c3_identifier, real_T c3_y[17])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_Dt), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_Dt);
}

static void c3_b_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[17])
{
  real_T c3_dv1[17];
  int32_T c3_i18;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv1, 1, 0, 0U, 1, 0U, 1, 17);
  for (c3_i18 = 0; c3_i18 < 17; c3_i18++) {
    c3_y[c3_i18] = c3_dv1[c3_i18];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_Dt;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[17];
  int32_T c3_i19;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_Dt = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_Dt), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_Dt);
  for (c3_i19 = 0; c3_i19 < 17; c3_i19++) {
    (*(real_T (*)[17])c3_outData)[c3_i19] = c3_y[c3_i19];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i20;
  int32_T c3_i21;
  int32_T c3_i22;
  real_T c3_b_inData[51];
  int32_T c3_i23;
  int32_T c3_i24;
  int32_T c3_i25;
  real_T c3_u[51];
  const mxArray *c3_y = NULL;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i20 = 0;
  for (c3_i21 = 0; c3_i21 < 17; c3_i21++) {
    for (c3_i22 = 0; c3_i22 < 3; c3_i22++) {
      c3_b_inData[c3_i22 + c3_i20] = (*(real_T (*)[51])c3_inData)[c3_i22 +
        c3_i20];
    }

    c3_i20 += 3;
  }

  c3_i23 = 0;
  for (c3_i24 = 0; c3_i24 < 17; c3_i24++) {
    for (c3_i25 = 0; c3_i25 < 3; c3_i25++) {
      c3_u[c3_i25 + c3_i23] = c3_b_inData[c3_i25 + c3_i23];
    }

    c3_i23 += 3;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 3, 17), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i26;
  real_T c3_b_inData[3];
  int32_T c3_i27;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i26 = 0; c3_i26 < 3; c3_i26++) {
    c3_b_inData[c3_i26] = (*(real_T (*)[3])c3_inData)[c3_i26];
  }

  for (c3_i27 = 0; c3_i27 < 3; c3_i27++) {
    c3_u[c3_i27] = c3_b_inData[c3_i27];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i28;
  int32_T c3_i29;
  int32_T c3_i30;
  real_T c3_b_inData[6];
  int32_T c3_i31;
  int32_T c3_i32;
  int32_T c3_i33;
  real_T c3_u[6];
  const mxArray *c3_y = NULL;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i28 = 0;
  for (c3_i29 = 0; c3_i29 < 2; c3_i29++) {
    for (c3_i30 = 0; c3_i30 < 3; c3_i30++) {
      c3_b_inData[c3_i30 + c3_i28] = (*(real_T (*)[6])c3_inData)[c3_i30 + c3_i28];
    }

    c3_i28 += 3;
  }

  c3_i31 = 0;
  for (c3_i32 = 0; c3_i32 < 2; c3_i32++) {
    for (c3_i33 = 0; c3_i33 < 3; c3_i33++) {
      c3_u[c3_i33 + c3_i31] = c3_b_inData[c3_i33 + c3_i31];
    }

    c3_i31 += 3;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 3, 2), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static real_T c3_c_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i34;
  int32_T c3_i35;
  int32_T c3_i36;
  real_T c3_b_inData[9];
  int32_T c3_i37;
  int32_T c3_i38;
  int32_T c3_i39;
  real_T c3_u[9];
  const mxArray *c3_y = NULL;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i34 = 0;
  for (c3_i35 = 0; c3_i35 < 3; c3_i35++) {
    for (c3_i36 = 0; c3_i36 < 3; c3_i36++) {
      c3_b_inData[c3_i36 + c3_i34] = (*(real_T (*)[9])c3_inData)[c3_i36 + c3_i34];
    }

    c3_i34 += 3;
  }

  c3_i37 = 0;
  for (c3_i38 = 0; c3_i38 < 3; c3_i38++) {
    for (c3_i39 = 0; c3_i39 < 3; c3_i39++) {
      c3_u[c3_i39 + c3_i37] = c3_b_inData[c3_i39 + c3_i37];
    }

    c3_i37 += 3;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static void c3_d_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[9])
{
  real_T c3_dv2[9];
  int32_T c3_i40;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv2, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c3_i40 = 0; c3_i40 < 9; c3_i40++) {
    c3_y[c3_i40] = c3_dv2[c3_i40];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_At;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[9];
  int32_T c3_i41;
  int32_T c3_i42;
  int32_T c3_i43;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_At = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_At), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_At);
  c3_i41 = 0;
  for (c3_i42 = 0; c3_i42 < 3; c3_i42++) {
    for (c3_i43 = 0; c3_i43 < 3; c3_i43++) {
      (*(real_T (*)[9])c3_outData)[c3_i43 + c3_i41] = c3_y[c3_i43 + c3_i41];
    }

    c3_i41 += 3;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_falter_library_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo;
  c3_ResolvedFunctionInfo c3_info[90];
  const mxArray *c3_m0 = NULL;
  int32_T c3_i44;
  c3_ResolvedFunctionInfo *c3_r0;
  c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  c3_info_helper(c3_info);
  c3_b_info_helper(c3_info);
  sf_mex_assign(&c3_m0, sf_mex_createstruct("nameCaptureInfo", 1, 90), FALSE);
  for (c3_i44 = 0; c3_i44 < 90; c3_i44++) {
    c3_r0 = &c3_info[c3_i44];
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->context)), "context", "nameCaptureInfo",
                    c3_i44);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c3_r0->name)), "name", "nameCaptureInfo", c3_i44);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c3_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c3_i44);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->resolved)), "resolved", "nameCaptureInfo",
                    c3_i44);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c3_i44);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c3_i44);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c3_i44);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c3_i44);
  }

  sf_mex_assign(&c3_nameCaptureInfo, c3_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c3_nameCaptureInfo);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[90])
{
  c3_info[0].context = "";
  c3_info[0].name = "det";
  c3_info[0].dominantType = "double";
  c3_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c3_info[0].fileTimeLo = 1286818822U;
  c3_info[0].fileTimeHi = 0U;
  c3_info[0].mFileTimeLo = 0U;
  c3_info[0].mFileTimeHi = 0U;
  c3_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c3_info[1].name = "eml_index_class";
  c3_info[1].dominantType = "";
  c3_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[1].fileTimeLo = 1323170578U;
  c3_info[1].fileTimeHi = 0U;
  c3_info[1].mFileTimeLo = 0U;
  c3_info[1].mFileTimeHi = 0U;
  c3_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c3_info[2].name = "eml_xgetrf";
  c3_info[2].dominantType = "double";
  c3_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c3_info[2].fileTimeLo = 1286818806U;
  c3_info[2].fileTimeHi = 0U;
  c3_info[2].mFileTimeLo = 0U;
  c3_info[2].mFileTimeHi = 0U;
  c3_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c3_info[3].name = "eml_lapack_xgetrf";
  c3_info[3].dominantType = "double";
  c3_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c3_info[3].fileTimeLo = 1286818810U;
  c3_info[3].fileTimeHi = 0U;
  c3_info[3].mFileTimeLo = 0U;
  c3_info[3].mFileTimeHi = 0U;
  c3_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c3_info[4].name = "eml_matlab_zgetrf";
  c3_info[4].dominantType = "double";
  c3_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[4].fileTimeLo = 1302688994U;
  c3_info[4].fileTimeHi = 0U;
  c3_info[4].mFileTimeLo = 0U;
  c3_info[4].mFileTimeHi = 0U;
  c3_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[5].name = "realmin";
  c3_info[5].dominantType = "char";
  c3_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c3_info[5].fileTimeLo = 1307651242U;
  c3_info[5].fileTimeHi = 0U;
  c3_info[5].mFileTimeLo = 0U;
  c3_info[5].mFileTimeHi = 0U;
  c3_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c3_info[6].name = "eml_realmin";
  c3_info[6].dominantType = "char";
  c3_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c3_info[6].fileTimeLo = 1307651244U;
  c3_info[6].fileTimeHi = 0U;
  c3_info[6].mFileTimeLo = 0U;
  c3_info[6].mFileTimeHi = 0U;
  c3_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c3_info[7].name = "eml_float_model";
  c3_info[7].dominantType = "char";
  c3_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c3_info[7].fileTimeLo = 1326727996U;
  c3_info[7].fileTimeHi = 0U;
  c3_info[7].mFileTimeLo = 0U;
  c3_info[7].mFileTimeHi = 0U;
  c3_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[8].name = "eps";
  c3_info[8].dominantType = "char";
  c3_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c3_info[8].fileTimeLo = 1326727996U;
  c3_info[8].fileTimeHi = 0U;
  c3_info[8].mFileTimeLo = 0U;
  c3_info[8].mFileTimeHi = 0U;
  c3_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c3_info[9].name = "eml_is_float_class";
  c3_info[9].dominantType = "char";
  c3_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c3_info[9].fileTimeLo = 1286818782U;
  c3_info[9].fileTimeHi = 0U;
  c3_info[9].mFileTimeLo = 0U;
  c3_info[9].mFileTimeHi = 0U;
  c3_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c3_info[10].name = "eml_eps";
  c3_info[10].dominantType = "char";
  c3_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c3_info[10].fileTimeLo = 1326727996U;
  c3_info[10].fileTimeHi = 0U;
  c3_info[10].mFileTimeLo = 0U;
  c3_info[10].mFileTimeHi = 0U;
  c3_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c3_info[11].name = "eml_float_model";
  c3_info[11].dominantType = "char";
  c3_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c3_info[11].fileTimeLo = 1326727996U;
  c3_info[11].fileTimeHi = 0U;
  c3_info[11].mFileTimeLo = 0U;
  c3_info[11].mFileTimeHi = 0U;
  c3_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[12].name = "min";
  c3_info[12].dominantType = "coder.internal.indexInt";
  c3_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c3_info[12].fileTimeLo = 1311255318U;
  c3_info[12].fileTimeHi = 0U;
  c3_info[12].mFileTimeLo = 0U;
  c3_info[12].mFileTimeHi = 0U;
  c3_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c3_info[13].name = "eml_min_or_max";
  c3_info[13].dominantType = "char";
  c3_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c3_info[13].fileTimeLo = 1334071490U;
  c3_info[13].fileTimeHi = 0U;
  c3_info[13].mFileTimeLo = 0U;
  c3_info[13].mFileTimeHi = 0U;
  c3_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[14].name = "eml_scalar_eg";
  c3_info[14].dominantType = "coder.internal.indexInt";
  c3_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[14].fileTimeLo = 1286818796U;
  c3_info[14].fileTimeHi = 0U;
  c3_info[14].mFileTimeLo = 0U;
  c3_info[14].mFileTimeHi = 0U;
  c3_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[15].name = "eml_scalexp_alloc";
  c3_info[15].dominantType = "coder.internal.indexInt";
  c3_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c3_info[15].fileTimeLo = 1352424860U;
  c3_info[15].fileTimeHi = 0U;
  c3_info[15].mFileTimeLo = 0U;
  c3_info[15].mFileTimeHi = 0U;
  c3_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[16].name = "eml_index_class";
  c3_info[16].dominantType = "";
  c3_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[16].fileTimeLo = 1323170578U;
  c3_info[16].fileTimeHi = 0U;
  c3_info[16].mFileTimeLo = 0U;
  c3_info[16].mFileTimeHi = 0U;
  c3_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c3_info[17].name = "eml_scalar_eg";
  c3_info[17].dominantType = "coder.internal.indexInt";
  c3_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[17].fileTimeLo = 1286818796U;
  c3_info[17].fileTimeHi = 0U;
  c3_info[17].mFileTimeLo = 0U;
  c3_info[17].mFileTimeHi = 0U;
  c3_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[18].name = "colon";
  c3_info[18].dominantType = "double";
  c3_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c3_info[18].fileTimeLo = 1348191928U;
  c3_info[18].fileTimeHi = 0U;
  c3_info[18].mFileTimeLo = 0U;
  c3_info[18].mFileTimeHi = 0U;
  c3_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c3_info[19].name = "colon";
  c3_info[19].dominantType = "double";
  c3_info[19].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c3_info[19].fileTimeLo = 1348191928U;
  c3_info[19].fileTimeHi = 0U;
  c3_info[19].mFileTimeLo = 0U;
  c3_info[19].mFileTimeHi = 0U;
  c3_info[20].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c3_info[20].name = "floor";
  c3_info[20].dominantType = "double";
  c3_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c3_info[20].fileTimeLo = 1343830380U;
  c3_info[20].fileTimeHi = 0U;
  c3_info[20].mFileTimeLo = 0U;
  c3_info[20].mFileTimeHi = 0U;
  c3_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c3_info[21].name = "eml_scalar_floor";
  c3_info[21].dominantType = "double";
  c3_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c3_info[21].fileTimeLo = 1286818726U;
  c3_info[21].fileTimeHi = 0U;
  c3_info[21].mFileTimeLo = 0U;
  c3_info[21].mFileTimeHi = 0U;
  c3_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c3_info[22].name = "intmin";
  c3_info[22].dominantType = "char";
  c3_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c3_info[22].fileTimeLo = 1311255318U;
  c3_info[22].fileTimeHi = 0U;
  c3_info[22].mFileTimeLo = 0U;
  c3_info[22].mFileTimeHi = 0U;
  c3_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c3_info[23].name = "intmax";
  c3_info[23].dominantType = "char";
  c3_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[23].fileTimeLo = 1311255316U;
  c3_info[23].fileTimeHi = 0U;
  c3_info[23].mFileTimeLo = 0U;
  c3_info[23].mFileTimeHi = 0U;
  c3_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c3_info[24].name = "intmin";
  c3_info[24].dominantType = "char";
  c3_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c3_info[24].fileTimeLo = 1311255318U;
  c3_info[24].fileTimeHi = 0U;
  c3_info[24].mFileTimeLo = 0U;
  c3_info[24].mFileTimeHi = 0U;
  c3_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c3_info[25].name = "intmax";
  c3_info[25].dominantType = "char";
  c3_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[25].fileTimeLo = 1311255316U;
  c3_info[25].fileTimeHi = 0U;
  c3_info[25].mFileTimeLo = 0U;
  c3_info[25].mFileTimeHi = 0U;
  c3_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c3_info[26].name = "eml_isa_uint";
  c3_info[26].dominantType = "coder.internal.indexInt";
  c3_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c3_info[26].fileTimeLo = 1286818784U;
  c3_info[26].fileTimeHi = 0U;
  c3_info[26].mFileTimeLo = 0U;
  c3_info[26].mFileTimeHi = 0U;
  c3_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c3_info[27].name = "eml_unsigned_class";
  c3_info[27].dominantType = "char";
  c3_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c3_info[27].fileTimeLo = 1323170580U;
  c3_info[27].fileTimeHi = 0U;
  c3_info[27].mFileTimeLo = 0U;
  c3_info[27].mFileTimeHi = 0U;
  c3_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c3_info[28].name = "eml_index_class";
  c3_info[28].dominantType = "";
  c3_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[28].fileTimeLo = 1323170578U;
  c3_info[28].fileTimeHi = 0U;
  c3_info[28].mFileTimeLo = 0U;
  c3_info[28].mFileTimeHi = 0U;
  c3_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c3_info[29].name = "eml_index_class";
  c3_info[29].dominantType = "";
  c3_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[29].fileTimeLo = 1323170578U;
  c3_info[29].fileTimeHi = 0U;
  c3_info[29].mFileTimeLo = 0U;
  c3_info[29].mFileTimeHi = 0U;
  c3_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c3_info[30].name = "intmax";
  c3_info[30].dominantType = "char";
  c3_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[30].fileTimeLo = 1311255316U;
  c3_info[30].fileTimeHi = 0U;
  c3_info[30].mFileTimeLo = 0U;
  c3_info[30].mFileTimeHi = 0U;
  c3_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c3_info[31].name = "eml_isa_uint";
  c3_info[31].dominantType = "coder.internal.indexInt";
  c3_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c3_info[31].fileTimeLo = 1286818784U;
  c3_info[31].fileTimeHi = 0U;
  c3_info[31].mFileTimeLo = 0U;
  c3_info[31].mFileTimeHi = 0U;
  c3_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c3_info[32].name = "eml_index_plus";
  c3_info[32].dominantType = "double";
  c3_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[32].fileTimeLo = 1286818778U;
  c3_info[32].fileTimeHi = 0U;
  c3_info[32].mFileTimeLo = 0U;
  c3_info[32].mFileTimeHi = 0U;
  c3_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[33].name = "eml_index_class";
  c3_info[33].dominantType = "";
  c3_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[33].fileTimeLo = 1323170578U;
  c3_info[33].fileTimeHi = 0U;
  c3_info[33].mFileTimeLo = 0U;
  c3_info[33].mFileTimeHi = 0U;
  c3_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_signed_integer_colon";
  c3_info[34].name = "eml_int_forloop_overflow_check";
  c3_info[34].dominantType = "";
  c3_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c3_info[34].fileTimeLo = 1346510340U;
  c3_info[34].fileTimeHi = 0U;
  c3_info[34].mFileTimeLo = 0U;
  c3_info[34].mFileTimeHi = 0U;
  c3_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c3_info[35].name = "intmax";
  c3_info[35].dominantType = "char";
  c3_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[35].fileTimeLo = 1311255316U;
  c3_info[35].fileTimeHi = 0U;
  c3_info[35].mFileTimeLo = 0U;
  c3_info[35].mFileTimeHi = 0U;
  c3_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[36].name = "eml_index_class";
  c3_info[36].dominantType = "";
  c3_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[36].fileTimeLo = 1323170578U;
  c3_info[36].fileTimeHi = 0U;
  c3_info[36].mFileTimeLo = 0U;
  c3_info[36].mFileTimeHi = 0U;
  c3_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[37].name = "eml_index_plus";
  c3_info[37].dominantType = "double";
  c3_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[37].fileTimeLo = 1286818778U;
  c3_info[37].fileTimeHi = 0U;
  c3_info[37].mFileTimeLo = 0U;
  c3_info[37].mFileTimeHi = 0U;
  c3_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[38].name = "eml_int_forloop_overflow_check";
  c3_info[38].dominantType = "";
  c3_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c3_info[38].fileTimeLo = 1346510340U;
  c3_info[38].fileTimeHi = 0U;
  c3_info[38].mFileTimeLo = 0U;
  c3_info[38].mFileTimeHi = 0U;
  c3_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[39].name = "eml_index_minus";
  c3_info[39].dominantType = "double";
  c3_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c3_info[39].fileTimeLo = 1286818778U;
  c3_info[39].fileTimeHi = 0U;
  c3_info[39].mFileTimeLo = 0U;
  c3_info[39].mFileTimeHi = 0U;
  c3_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c3_info[40].name = "eml_index_class";
  c3_info[40].dominantType = "";
  c3_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[40].fileTimeLo = 1323170578U;
  c3_info[40].fileTimeHi = 0U;
  c3_info[40].mFileTimeLo = 0U;
  c3_info[40].mFileTimeHi = 0U;
  c3_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[41].name = "eml_index_minus";
  c3_info[41].dominantType = "coder.internal.indexInt";
  c3_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c3_info[41].fileTimeLo = 1286818778U;
  c3_info[41].fileTimeHi = 0U;
  c3_info[41].mFileTimeLo = 0U;
  c3_info[41].mFileTimeHi = 0U;
  c3_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[42].name = "eml_index_times";
  c3_info[42].dominantType = "coder.internal.indexInt";
  c3_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c3_info[42].fileTimeLo = 1286818780U;
  c3_info[42].fileTimeHi = 0U;
  c3_info[42].mFileTimeLo = 0U;
  c3_info[42].mFileTimeHi = 0U;
  c3_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c3_info[43].name = "eml_index_class";
  c3_info[43].dominantType = "";
  c3_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[43].fileTimeLo = 1323170578U;
  c3_info[43].fileTimeHi = 0U;
  c3_info[43].mFileTimeLo = 0U;
  c3_info[43].mFileTimeHi = 0U;
  c3_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[44].name = "eml_index_plus";
  c3_info[44].dominantType = "coder.internal.indexInt";
  c3_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[44].fileTimeLo = 1286818778U;
  c3_info[44].fileTimeHi = 0U;
  c3_info[44].mFileTimeLo = 0U;
  c3_info[44].mFileTimeHi = 0U;
  c3_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[45].name = "eml_ixamax";
  c3_info[45].dominantType = "double";
  c3_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c3_info[45].fileTimeLo = 1299076770U;
  c3_info[45].fileTimeHi = 0U;
  c3_info[45].mFileTimeLo = 0U;
  c3_info[45].mFileTimeHi = 0U;
  c3_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c3_info[46].name = "eml_blas_inline";
  c3_info[46].dominantType = "";
  c3_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c3_info[46].fileTimeLo = 1299076768U;
  c3_info[46].fileTimeHi = 0U;
  c3_info[46].mFileTimeLo = 0U;
  c3_info[46].mFileTimeHi = 0U;
  c3_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m!below_threshold";
  c3_info[47].name = "length";
  c3_info[47].dominantType = "double";
  c3_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c3_info[47].fileTimeLo = 1303146206U;
  c3_info[47].fileTimeHi = 0U;
  c3_info[47].mFileTimeLo = 0U;
  c3_info[47].mFileTimeHi = 0U;
  c3_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength";
  c3_info[48].name = "eml_index_class";
  c3_info[48].dominantType = "";
  c3_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[48].fileTimeLo = 1323170578U;
  c3_info[48].fileTimeHi = 0U;
  c3_info[48].mFileTimeLo = 0U;
  c3_info[48].mFileTimeHi = 0U;
  c3_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c3_info[49].name = "eml_index_class";
  c3_info[49].dominantType = "";
  c3_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[49].fileTimeLo = 1323170578U;
  c3_info[49].fileTimeHi = 0U;
  c3_info[49].mFileTimeLo = 0U;
  c3_info[49].mFileTimeHi = 0U;
  c3_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c3_info[50].name = "eml_refblas_ixamax";
  c3_info[50].dominantType = "double";
  c3_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c3_info[50].fileTimeLo = 1299076770U;
  c3_info[50].fileTimeHi = 0U;
  c3_info[50].mFileTimeLo = 0U;
  c3_info[50].mFileTimeHi = 0U;
  c3_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c3_info[51].name = "eml_index_class";
  c3_info[51].dominantType = "";
  c3_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[51].fileTimeLo = 1323170578U;
  c3_info[51].fileTimeHi = 0U;
  c3_info[51].mFileTimeLo = 0U;
  c3_info[51].mFileTimeHi = 0U;
  c3_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c3_info[52].name = "eml_xcabs1";
  c3_info[52].dominantType = "double";
  c3_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c3_info[52].fileTimeLo = 1286818706U;
  c3_info[52].fileTimeHi = 0U;
  c3_info[52].mFileTimeLo = 0U;
  c3_info[52].mFileTimeHi = 0U;
  c3_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c3_info[53].name = "abs";
  c3_info[53].dominantType = "double";
  c3_info[53].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[53].fileTimeLo = 1343830366U;
  c3_info[53].fileTimeHi = 0U;
  c3_info[53].mFileTimeLo = 0U;
  c3_info[53].mFileTimeHi = 0U;
  c3_info[54].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[54].name = "eml_scalar_abs";
  c3_info[54].dominantType = "double";
  c3_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c3_info[54].fileTimeLo = 1286818712U;
  c3_info[54].fileTimeHi = 0U;
  c3_info[54].mFileTimeLo = 0U;
  c3_info[54].mFileTimeHi = 0U;
  c3_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c3_info[55].name = "eml_int_forloop_overflow_check";
  c3_info[55].dominantType = "";
  c3_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c3_info[55].fileTimeLo = 1346510340U;
  c3_info[55].fileTimeHi = 0U;
  c3_info[55].mFileTimeLo = 0U;
  c3_info[55].mFileTimeHi = 0U;
  c3_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c3_info[56].name = "eml_index_plus";
  c3_info[56].dominantType = "coder.internal.indexInt";
  c3_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[56].fileTimeLo = 1286818778U;
  c3_info[56].fileTimeHi = 0U;
  c3_info[56].mFileTimeLo = 0U;
  c3_info[56].mFileTimeHi = 0U;
  c3_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[57].name = "eml_xswap";
  c3_info[57].dominantType = "double";
  c3_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c3_info[57].fileTimeLo = 1299076778U;
  c3_info[57].fileTimeHi = 0U;
  c3_info[57].mFileTimeLo = 0U;
  c3_info[57].mFileTimeHi = 0U;
  c3_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c3_info[58].name = "eml_blas_inline";
  c3_info[58].dominantType = "";
  c3_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c3_info[58].fileTimeLo = 1299076768U;
  c3_info[58].fileTimeHi = 0U;
  c3_info[58].mFileTimeLo = 0U;
  c3_info[58].mFileTimeHi = 0U;
  c3_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c3_info[59].name = "eml_index_class";
  c3_info[59].dominantType = "";
  c3_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[59].fileTimeLo = 1323170578U;
  c3_info[59].fileTimeHi = 0U;
  c3_info[59].mFileTimeLo = 0U;
  c3_info[59].mFileTimeHi = 0U;
  c3_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c3_info[60].name = "eml_refblas_xswap";
  c3_info[60].dominantType = "double";
  c3_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c3_info[60].fileTimeLo = 1299076786U;
  c3_info[60].fileTimeHi = 0U;
  c3_info[60].mFileTimeLo = 0U;
  c3_info[60].mFileTimeHi = 0U;
  c3_info[61].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c3_info[61].name = "eml_index_class";
  c3_info[61].dominantType = "";
  c3_info[61].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[61].fileTimeLo = 1323170578U;
  c3_info[61].fileTimeHi = 0U;
  c3_info[61].mFileTimeLo = 0U;
  c3_info[61].mFileTimeHi = 0U;
  c3_info[62].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c3_info[62].name = "abs";
  c3_info[62].dominantType = "coder.internal.indexInt";
  c3_info[62].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[62].fileTimeLo = 1343830366U;
  c3_info[62].fileTimeHi = 0U;
  c3_info[62].mFileTimeLo = 0U;
  c3_info[62].mFileTimeHi = 0U;
  c3_info[63].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[63].name = "eml_scalar_abs";
  c3_info[63].dominantType = "coder.internal.indexInt";
  c3_info[63].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c3_info[63].fileTimeLo = 1286818712U;
  c3_info[63].fileTimeHi = 0U;
  c3_info[63].mFileTimeLo = 0U;
  c3_info[63].mFileTimeHi = 0U;
}

static void c3_b_info_helper(c3_ResolvedFunctionInfo c3_info[90])
{
  c3_info[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c3_info[64].name = "eml_int_forloop_overflow_check";
  c3_info[64].dominantType = "";
  c3_info[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c3_info[64].fileTimeLo = 1346510340U;
  c3_info[64].fileTimeHi = 0U;
  c3_info[64].mFileTimeLo = 0U;
  c3_info[64].mFileTimeHi = 0U;
  c3_info[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c3_info[65].name = "eml_index_plus";
  c3_info[65].dominantType = "coder.internal.indexInt";
  c3_info[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[65].fileTimeLo = 1286818778U;
  c3_info[65].fileTimeHi = 0U;
  c3_info[65].mFileTimeLo = 0U;
  c3_info[65].mFileTimeHi = 0U;
  c3_info[66].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[66].name = "eml_div";
  c3_info[66].dominantType = "double";
  c3_info[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c3_info[66].fileTimeLo = 1313347810U;
  c3_info[66].fileTimeHi = 0U;
  c3_info[66].mFileTimeLo = 0U;
  c3_info[66].mFileTimeHi = 0U;
  c3_info[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c3_info[67].name = "eml_xgeru";
  c3_info[67].dominantType = "double";
  c3_info[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c3_info[67].fileTimeLo = 1299076774U;
  c3_info[67].fileTimeHi = 0U;
  c3_info[67].mFileTimeLo = 0U;
  c3_info[67].mFileTimeHi = 0U;
  c3_info[68].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c3_info[68].name = "eml_blas_inline";
  c3_info[68].dominantType = "";
  c3_info[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c3_info[68].fileTimeLo = 1299076768U;
  c3_info[68].fileTimeHi = 0U;
  c3_info[68].mFileTimeLo = 0U;
  c3_info[68].mFileTimeHi = 0U;
  c3_info[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c3_info[69].name = "eml_xger";
  c3_info[69].dominantType = "double";
  c3_info[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c3_info[69].fileTimeLo = 1299076774U;
  c3_info[69].fileTimeHi = 0U;
  c3_info[69].mFileTimeLo = 0U;
  c3_info[69].mFileTimeHi = 0U;
  c3_info[70].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c3_info[70].name = "eml_blas_inline";
  c3_info[70].dominantType = "";
  c3_info[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c3_info[70].fileTimeLo = 1299076768U;
  c3_info[70].fileTimeHi = 0U;
  c3_info[70].mFileTimeLo = 0U;
  c3_info[70].mFileTimeHi = 0U;
  c3_info[71].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m!below_threshold";
  c3_info[71].name = "intmax";
  c3_info[71].dominantType = "char";
  c3_info[71].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c3_info[71].fileTimeLo = 1311255316U;
  c3_info[71].fileTimeHi = 0U;
  c3_info[71].mFileTimeLo = 0U;
  c3_info[71].mFileTimeHi = 0U;
  c3_info[72].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m!below_threshold";
  c3_info[72].name = "min";
  c3_info[72].dominantType = "double";
  c3_info[72].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c3_info[72].fileTimeLo = 1311255318U;
  c3_info[72].fileTimeHi = 0U;
  c3_info[72].mFileTimeLo = 0U;
  c3_info[72].mFileTimeHi = 0U;
  c3_info[73].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[73].name = "eml_scalar_eg";
  c3_info[73].dominantType = "double";
  c3_info[73].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[73].fileTimeLo = 1286818796U;
  c3_info[73].fileTimeHi = 0U;
  c3_info[73].mFileTimeLo = 0U;
  c3_info[73].mFileTimeHi = 0U;
  c3_info[74].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c3_info[74].name = "eml_scalexp_alloc";
  c3_info[74].dominantType = "double";
  c3_info[74].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c3_info[74].fileTimeLo = 1352424860U;
  c3_info[74].fileTimeHi = 0U;
  c3_info[74].mFileTimeLo = 0U;
  c3_info[74].mFileTimeHi = 0U;
  c3_info[75].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c3_info[75].name = "eml_scalar_eg";
  c3_info[75].dominantType = "double";
  c3_info[75].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[75].fileTimeLo = 1286818796U;
  c3_info[75].fileTimeHi = 0U;
  c3_info[75].mFileTimeLo = 0U;
  c3_info[75].mFileTimeHi = 0U;
  c3_info[76].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m!below_threshold";
  c3_info[76].name = "mtimes";
  c3_info[76].dominantType = "double";
  c3_info[76].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[76].fileTimeLo = 1289519692U;
  c3_info[76].fileTimeHi = 0U;
  c3_info[76].mFileTimeLo = 0U;
  c3_info[76].mFileTimeHi = 0U;
  c3_info[77].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c3_info[77].name = "eml_index_class";
  c3_info[77].dominantType = "";
  c3_info[77].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[77].fileTimeLo = 1323170578U;
  c3_info[77].fileTimeHi = 0U;
  c3_info[77].mFileTimeLo = 0U;
  c3_info[77].mFileTimeHi = 0U;
  c3_info[78].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c3_info[78].name = "eml_refblas_xger";
  c3_info[78].dominantType = "double";
  c3_info[78].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c3_info[78].fileTimeLo = 1299076776U;
  c3_info[78].fileTimeHi = 0U;
  c3_info[78].mFileTimeLo = 0U;
  c3_info[78].mFileTimeHi = 0U;
  c3_info[79].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c3_info[79].name = "eml_refblas_xgerx";
  c3_info[79].dominantType = "char";
  c3_info[79].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c3_info[79].fileTimeLo = 1299076778U;
  c3_info[79].fileTimeHi = 0U;
  c3_info[79].mFileTimeLo = 0U;
  c3_info[79].mFileTimeHi = 0U;
  c3_info[80].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c3_info[80].name = "eml_index_class";
  c3_info[80].dominantType = "";
  c3_info[80].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c3_info[80].fileTimeLo = 1323170578U;
  c3_info[80].fileTimeHi = 0U;
  c3_info[80].mFileTimeLo = 0U;
  c3_info[80].mFileTimeHi = 0U;
  c3_info[81].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c3_info[81].name = "abs";
  c3_info[81].dominantType = "coder.internal.indexInt";
  c3_info[81].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c3_info[81].fileTimeLo = 1343830366U;
  c3_info[81].fileTimeHi = 0U;
  c3_info[81].mFileTimeLo = 0U;
  c3_info[81].mFileTimeHi = 0U;
  c3_info[82].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c3_info[82].name = "eml_index_minus";
  c3_info[82].dominantType = "double";
  c3_info[82].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c3_info[82].fileTimeLo = 1286818778U;
  c3_info[82].fileTimeHi = 0U;
  c3_info[82].mFileTimeLo = 0U;
  c3_info[82].mFileTimeHi = 0U;
  c3_info[83].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c3_info[83].name = "eml_int_forloop_overflow_check";
  c3_info[83].dominantType = "";
  c3_info[83].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c3_info[83].fileTimeLo = 1346510340U;
  c3_info[83].fileTimeHi = 0U;
  c3_info[83].mFileTimeLo = 0U;
  c3_info[83].mFileTimeHi = 0U;
  c3_info[84].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c3_info[84].name = "eml_index_plus";
  c3_info[84].dominantType = "double";
  c3_info[84].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[84].fileTimeLo = 1286818778U;
  c3_info[84].fileTimeHi = 0U;
  c3_info[84].mFileTimeLo = 0U;
  c3_info[84].mFileTimeHi = 0U;
  c3_info[85].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c3_info[85].name = "eml_index_plus";
  c3_info[85].dominantType = "coder.internal.indexInt";
  c3_info[85].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c3_info[85].fileTimeLo = 1286818778U;
  c3_info[85].fileTimeHi = 0U;
  c3_info[85].mFileTimeLo = 0U;
  c3_info[85].mFileTimeHi = 0U;
  c3_info[86].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c3_info[86].name = "mtimes";
  c3_info[86].dominantType = "double";
  c3_info[86].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[86].fileTimeLo = 1289519692U;
  c3_info[86].fileTimeHi = 0U;
  c3_info[86].mFileTimeLo = 0U;
  c3_info[86].mFileTimeHi = 0U;
  c3_info[87].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c3_info[87].name = "coder.internal.indexIntRelop";
  c3_info[87].dominantType = "";
  c3_info[87].resolved =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m";
  c3_info[87].fileTimeLo = 1326728322U;
  c3_info[87].fileTimeHi = 0U;
  c3_info[87].mFileTimeLo = 0U;
  c3_info[87].mFileTimeHi = 0U;
  c3_info[88].context =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!float_class_contains_indexIntClass";
  c3_info[88].name = "eml_float_model";
  c3_info[88].dominantType = "char";
  c3_info[88].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c3_info[88].fileTimeLo = 1326727996U;
  c3_info[88].fileTimeHi = 0U;
  c3_info[88].mFileTimeLo = 0U;
  c3_info[88].mFileTimeHi = 0U;
  c3_info[89].context =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!is_signed_indexIntClass";
  c3_info[89].name = "intmin";
  c3_info[89].dominantType = "char";
  c3_info[89].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c3_info[89].fileTimeLo = 1311255318U;
  c3_info[89].fileTimeHi = 0U;
  c3_info[89].mFileTimeLo = 0U;
  c3_info[89].mFileTimeHi = 0U;
}

static void c3_realmin(SFc3_falter_libraryInstanceStruct *chartInstance)
{
}

static void c3_eps(SFc3_falter_libraryInstanceStruct *chartInstance)
{
}

static void c3_eml_matlab_zgetrf(SFc3_falter_libraryInstanceStruct
  *chartInstance, real_T c3_A[9], real_T c3_b_A[9], int32_T c3_ipiv[3], int32_T *
  c3_info)
{
  int32_T c3_i45;
  for (c3_i45 = 0; c3_i45 < 9; c3_i45++) {
    c3_b_A[c3_i45] = c3_A[c3_i45];
  }

  c3_b_eml_matlab_zgetrf(chartInstance, c3_b_A, c3_ipiv, c3_info);
}

static void c3_check_forloop_overflow_error(SFc3_falter_libraryInstanceStruct
  *chartInstance, boolean_T c3_overflow)
{
  int32_T c3_i46;
  static char_T c3_cv0[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c3_u[34];
  const mxArray *c3_y = NULL;
  int32_T c3_i47;
  static char_T c3_cv1[23] = { 'c', 'o', 'd', 'e', 'r', '.', 'i', 'n', 't', 'e',
    'r', 'n', 'a', 'l', '.', 'i', 'n', 'd', 'e', 'x', 'I', 'n', 't' };

  char_T c3_b_u[23];
  const mxArray *c3_b_y = NULL;
  if (!c3_overflow) {
  } else {
    for (c3_i46 = 0; c3_i46 < 34; c3_i46++) {
      c3_u[c3_i46] = c3_cv0[c3_i46];
    }

    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  FALSE);
    for (c3_i47 = 0; c3_i47 < 23; c3_i47++) {
      c3_b_u[c3_i47] = c3_cv1[c3_i47];
    }

    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 23),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
      14, c3_y, 14, c3_b_y));
  }
}

static void c3_eml_xger(SFc3_falter_libraryInstanceStruct *chartInstance,
  int32_T c3_m, int32_T c3_n, real_T c3_alpha1, int32_T c3_ix0, int32_T c3_iy0,
  real_T c3_A[9], int32_T c3_ia0, real_T c3_b_A[9])
{
  int32_T c3_i48;
  for (c3_i48 = 0; c3_i48 < 9; c3_i48++) {
    c3_b_A[c3_i48] = c3_A[c3_i48];
  }

  c3_b_eml_xger(chartInstance, c3_m, c3_n, c3_alpha1, c3_ix0, c3_iy0, c3_b_A,
                c3_ia0);
}

static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, FALSE);
  return c3_mxArrayOutData;
}

static int32_T c3_e_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i49;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i49, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i49;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_f_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_falter_library, const char_T *
  c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_falter_library), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_falter_library);
  return c3_y;
}

static uint8_T c3_g_emlrt_marshallIn(SFc3_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_eml_matlab_zgetrf(SFc3_falter_libraryInstanceStruct
  *chartInstance, real_T c3_A[9], int32_T c3_ipiv[3], int32_T *c3_info)
{
  int32_T c3_i50;
  int32_T c3_j;
  int32_T c3_b_j;
  int32_T c3_a;
  int32_T c3_jm1;
  int32_T c3_b;
  int32_T c3_mmj;
  int32_T c3_b_a;
  int32_T c3_c;
  int32_T c3_b_b;
  int32_T c3_jj;
  int32_T c3_c_a;
  int32_T c3_jp1j;
  int32_T c3_d_a;
  int32_T c3_b_c;
  int32_T c3_n;
  int32_T c3_ix0;
  int32_T c3_b_n;
  int32_T c3_b_ix0;
  int32_T c3_c_n;
  int32_T c3_c_ix0;
  int32_T c3_idxmax;
  int32_T c3_ix;
  real_T c3_x;
  real_T c3_b_x;
  real_T c3_c_x;
  real_T c3_y;
  real_T c3_d_x;
  real_T c3_e_x;
  real_T c3_b_y;
  real_T c3_smax;
  int32_T c3_d_n;
  int32_T c3_c_b;
  int32_T c3_d_b;
  boolean_T c3_overflow;
  int32_T c3_k;
  int32_T c3_b_k;
  int32_T c3_e_a;
  real_T c3_f_x;
  real_T c3_g_x;
  real_T c3_h_x;
  real_T c3_c_y;
  real_T c3_i_x;
  real_T c3_j_x;
  real_T c3_d_y;
  real_T c3_s;
  int32_T c3_f_a;
  int32_T c3_jpiv_offset;
  int32_T c3_g_a;
  int32_T c3_e_b;
  int32_T c3_jpiv;
  int32_T c3_h_a;
  int32_T c3_f_b;
  int32_T c3_c_c;
  int32_T c3_g_b;
  int32_T c3_jrow;
  int32_T c3_i_a;
  int32_T c3_h_b;
  int32_T c3_jprow;
  int32_T c3_d_ix0;
  int32_T c3_iy0;
  int32_T c3_e_ix0;
  int32_T c3_b_iy0;
  int32_T c3_f_ix0;
  int32_T c3_c_iy0;
  int32_T c3_b_ix;
  int32_T c3_iy;
  int32_T c3_c_k;
  real_T c3_temp;
  int32_T c3_j_a;
  int32_T c3_k_a;
  int32_T c3_b_jp1j;
  int32_T c3_l_a;
  int32_T c3_d_c;
  int32_T c3_m_a;
  int32_T c3_i_b;
  int32_T c3_i51;
  int32_T c3_n_a;
  int32_T c3_j_b;
  int32_T c3_o_a;
  int32_T c3_k_b;
  boolean_T c3_b_overflow;
  int32_T c3_i;
  int32_T c3_b_i;
  real_T c3_k_x;
  real_T c3_e_y;
  real_T c3_z;
  int32_T c3_l_b;
  int32_T c3_e_c;
  int32_T c3_p_a;
  int32_T c3_f_c;
  int32_T c3_q_a;
  int32_T c3_g_c;
  int32_T c3_m;
  int32_T c3_e_n;
  int32_T c3_g_ix0;
  int32_T c3_d_iy0;
  int32_T c3_ia0;
  real_T c3_d1;
  c3_realmin(chartInstance);
  c3_eps(chartInstance);
  for (c3_i50 = 0; c3_i50 < 3; c3_i50++) {
    c3_ipiv[c3_i50] = 1 + c3_i50;
  }

  *c3_info = 0;
  for (c3_j = 1; c3_j < 3; c3_j++) {
    c3_b_j = c3_j;
    c3_a = c3_b_j - 1;
    c3_jm1 = c3_a;
    c3_b = c3_b_j;
    c3_mmj = 3 - c3_b;
    c3_b_a = c3_jm1;
    c3_c = c3_b_a << 2;
    c3_b_b = c3_c + 1;
    c3_jj = c3_b_b;
    c3_c_a = c3_jj + 1;
    c3_jp1j = c3_c_a;
    c3_d_a = c3_mmj;
    c3_b_c = c3_d_a;
    c3_n = c3_b_c + 1;
    c3_ix0 = c3_jj;
    c3_b_n = c3_n;
    c3_b_ix0 = c3_ix0;
    c3_c_n = c3_b_n;
    c3_c_ix0 = c3_b_ix0;
    if (c3_c_n < 1) {
      c3_idxmax = 0;
    } else {
      c3_idxmax = 1;
      if (c3_c_n > 1) {
        c3_ix = c3_c_ix0;
        c3_x = c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c3_ix), 1, 9, 1, 0) - 1];
        c3_b_x = c3_x;
        c3_c_x = c3_b_x;
        c3_y = muDoubleScalarAbs(c3_c_x);
        c3_d_x = 0.0;
        c3_e_x = c3_d_x;
        c3_b_y = muDoubleScalarAbs(c3_e_x);
        c3_smax = c3_y + c3_b_y;
        c3_d_n = c3_c_n;
        c3_c_b = c3_d_n;
        c3_d_b = c3_c_b;
        if (2 > c3_d_b) {
          c3_overflow = FALSE;
        } else {
          c3_overflow = (c3_d_b > 2147483646);
        }

        if (c3_overflow) {
          c3_check_forloop_overflow_error(chartInstance, c3_overflow);
        }

        for (c3_k = 2; c3_k <= c3_d_n; c3_k++) {
          c3_b_k = c3_k;
          c3_e_a = c3_ix + 1;
          c3_ix = c3_e_a;
          c3_f_x = c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c3_ix), 1, 9, 1, 0) - 1];
          c3_g_x = c3_f_x;
          c3_h_x = c3_g_x;
          c3_c_y = muDoubleScalarAbs(c3_h_x);
          c3_i_x = 0.0;
          c3_j_x = c3_i_x;
          c3_d_y = muDoubleScalarAbs(c3_j_x);
          c3_s = c3_c_y + c3_d_y;
          if (c3_s > c3_smax) {
            c3_idxmax = c3_b_k;
            c3_smax = c3_s;
          }
        }
      }
    }

    c3_f_a = c3_idxmax - 1;
    c3_jpiv_offset = c3_f_a;
    c3_g_a = c3_jj;
    c3_e_b = c3_jpiv_offset;
    c3_jpiv = c3_g_a + c3_e_b;
    if (c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_jpiv), 1, 9, 1, 0) - 1] != 0.0) {
      if (c3_jpiv_offset != 0) {
        c3_h_a = c3_b_j;
        c3_f_b = c3_jpiv_offset;
        c3_c_c = c3_h_a + c3_f_b;
        c3_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_b_j), 1, 3, 1, 0) - 1] = c3_c_c;
        c3_g_b = c3_jm1 + 1;
        c3_jrow = c3_g_b;
        c3_i_a = c3_jrow;
        c3_h_b = c3_jpiv_offset;
        c3_jprow = c3_i_a + c3_h_b;
        c3_d_ix0 = c3_jrow;
        c3_iy0 = c3_jprow;
        c3_e_ix0 = c3_d_ix0;
        c3_b_iy0 = c3_iy0;
        c3_f_ix0 = c3_e_ix0;
        c3_c_iy0 = c3_b_iy0;
        c3_b_ix = c3_f_ix0;
        c3_iy = c3_c_iy0;
        for (c3_c_k = 1; c3_c_k < 4; c3_c_k++) {
          c3_temp = c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c3_b_ix), 1, 9, 1, 0) - 1];
          c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_b_ix), 1, 9, 1, 0) - 1] =
            c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_iy), 1, 9, 1, 0) - 1];
          c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_iy), 1, 9, 1, 0) - 1] = c3_temp;
          c3_j_a = c3_b_ix + 3;
          c3_b_ix = c3_j_a;
          c3_k_a = c3_iy + 3;
          c3_iy = c3_k_a;
        }
      }

      c3_b_jp1j = c3_jp1j;
      c3_l_a = c3_mmj;
      c3_d_c = c3_l_a;
      c3_m_a = c3_jp1j;
      c3_i_b = c3_d_c - 1;
      c3_i51 = c3_m_a + c3_i_b;
      c3_n_a = c3_b_jp1j;
      c3_j_b = c3_i51;
      c3_o_a = c3_n_a;
      c3_k_b = c3_j_b;
      if (c3_o_a > c3_k_b) {
        c3_b_overflow = FALSE;
      } else {
        c3_b_overflow = (c3_k_b > 2147483646);
      }

      if (c3_b_overflow) {
        c3_check_forloop_overflow_error(chartInstance, c3_b_overflow);
      }

      for (c3_i = c3_b_jp1j; c3_i <= c3_i51; c3_i++) {
        c3_b_i = c3_i;
        c3_k_x = c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c3_b_i), 1, 9, 1, 0) - 1];
        c3_e_y = c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c3_jj), 1, 9, 1, 0) - 1];
        c3_z = c3_k_x / c3_e_y;
        c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c3_b_i), 1, 9, 1, 0) - 1] = c3_z;
      }
    } else {
      *c3_info = c3_b_j;
    }

    c3_l_b = c3_b_j;
    c3_e_c = 3 - c3_l_b;
    c3_p_a = c3_jj;
    c3_f_c = c3_p_a;
    c3_q_a = c3_jj;
    c3_g_c = c3_q_a;
    c3_m = c3_mmj;
    c3_e_n = c3_e_c;
    c3_g_ix0 = c3_jp1j;
    c3_d_iy0 = c3_f_c + 3;
    c3_ia0 = c3_g_c + 4;
    c3_d1 = -1.0;
    c3_b_eml_xger(chartInstance, c3_m, c3_e_n, c3_d1, c3_g_ix0, c3_d_iy0, c3_A,
                  c3_ia0);
  }

  if (*c3_info == 0) {
    if (!(c3_A[8] != 0.0)) {
      *c3_info = 3;
    }
  }
}

static void c3_b_eml_xger(SFc3_falter_libraryInstanceStruct *chartInstance,
  int32_T c3_m, int32_T c3_n, real_T c3_alpha1, int32_T c3_ix0, int32_T c3_iy0,
  real_T c3_A[9], int32_T c3_ia0)
{
  int32_T c3_b_m;
  int32_T c3_b_n;
  real_T c3_b_alpha1;
  int32_T c3_b_ix0;
  int32_T c3_b_iy0;
  int32_T c3_b_ia0;
  int32_T c3_c_m;
  int32_T c3_c_n;
  real_T c3_c_alpha1;
  int32_T c3_c_ix0;
  int32_T c3_c_iy0;
  int32_T c3_c_ia0;
  int32_T c3_d_m;
  int32_T c3_d_n;
  real_T c3_d_alpha1;
  int32_T c3_d_ix0;
  int32_T c3_d_iy0;
  int32_T c3_d_ia0;
  int32_T c3_ixstart;
  int32_T c3_a;
  int32_T c3_jA;
  int32_T c3_jy;
  int32_T c3_e_n;
  int32_T c3_b;
  int32_T c3_b_b;
  boolean_T c3_overflow;
  int32_T c3_j;
  real_T c3_yjy;
  real_T c3_temp;
  int32_T c3_ix;
  int32_T c3_c_b;
  int32_T c3_i52;
  int32_T c3_b_a;
  int32_T c3_d_b;
  int32_T c3_i53;
  int32_T c3_c_a;
  int32_T c3_e_b;
  int32_T c3_d_a;
  int32_T c3_f_b;
  boolean_T c3_b_overflow;
  int32_T c3_ijA;
  int32_T c3_b_ijA;
  int32_T c3_e_a;
  int32_T c3_f_a;
  int32_T c3_g_a;
  c3_b_m = c3_m;
  c3_b_n = c3_n;
  c3_b_alpha1 = c3_alpha1;
  c3_b_ix0 = c3_ix0;
  c3_b_iy0 = c3_iy0;
  c3_b_ia0 = c3_ia0;
  c3_c_m = c3_b_m;
  c3_c_n = c3_b_n;
  c3_c_alpha1 = c3_b_alpha1;
  c3_c_ix0 = c3_b_ix0;
  c3_c_iy0 = c3_b_iy0;
  c3_c_ia0 = c3_b_ia0;
  c3_d_m = c3_c_m;
  c3_d_n = c3_c_n;
  c3_d_alpha1 = c3_c_alpha1;
  c3_d_ix0 = c3_c_ix0;
  c3_d_iy0 = c3_c_iy0;
  c3_d_ia0 = c3_c_ia0;
  if (c3_d_alpha1 == 0.0) {
  } else {
    c3_ixstart = c3_d_ix0;
    c3_a = c3_d_ia0 - 1;
    c3_jA = c3_a;
    c3_jy = c3_d_iy0;
    c3_e_n = c3_d_n;
    c3_b = c3_e_n;
    c3_b_b = c3_b;
    if (1 > c3_b_b) {
      c3_overflow = FALSE;
    } else {
      c3_overflow = (c3_b_b > 2147483646);
    }

    if (c3_overflow) {
      c3_check_forloop_overflow_error(chartInstance, c3_overflow);
    }

    for (c3_j = 1; c3_j <= c3_e_n; c3_j++) {
      c3_yjy = c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c3_jy), 1, 9, 1, 0) - 1];
      if (c3_yjy != 0.0) {
        c3_temp = c3_yjy * c3_d_alpha1;
        c3_ix = c3_ixstart;
        c3_c_b = c3_jA + 1;
        c3_i52 = c3_c_b;
        c3_b_a = c3_d_m;
        c3_d_b = c3_jA;
        c3_i53 = c3_b_a + c3_d_b;
        c3_c_a = c3_i52;
        c3_e_b = c3_i53;
        c3_d_a = c3_c_a;
        c3_f_b = c3_e_b;
        if (c3_d_a > c3_f_b) {
          c3_b_overflow = FALSE;
        } else {
          c3_b_overflow = (c3_f_b > 2147483646);
        }

        if (c3_b_overflow) {
          c3_check_forloop_overflow_error(chartInstance, c3_b_overflow);
        }

        for (c3_ijA = c3_i52; c3_ijA <= c3_i53; c3_ijA++) {
          c3_b_ijA = c3_ijA;
          c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_b_ijA), 1, 9, 1, 0) - 1] =
            c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_b_ijA), 1, 9, 1, 0) - 1] +
            c3_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c3_ix), 1, 9, 1, 0) - 1] * c3_temp;
          c3_e_a = c3_ix + 1;
          c3_ix = c3_e_a;
        }
      }

      c3_f_a = c3_jy + 3;
      c3_jy = c3_f_a;
      c3_g_a = c3_jA + 3;
      c3_jA = c3_g_a;
    }
  }
}

static void init_dsm_address_info(SFc3_falter_libraryInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c3_falter_library_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4121721254U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(723361643U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4236821929U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1859758171U);
}

mxArray *sf_c3_falter_library_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("KFZMNve6NBl2w0CMV1g4XH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(2);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(17);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(17);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_falter_library_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c3_falter_library(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"Dt\",},{M[8],M[0],T\"is_active_c3_falter_library\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_falter_library_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_falter_libraryInstanceStruct *chartInstance;
    chartInstance = (SFc3_falter_libraryInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _falter_libraryMachineNumber_,
           3,
           1,
           1,
           4,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_falter_libraryMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_falter_libraryMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _falter_libraryMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Plane");
          _SFD_SET_DATA_PROPS(1,2,0,1,"Dt");
          _SFD_SET_DATA_PROPS(2,1,1,0,"Position");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Directions");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,1,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,159);
        _SFD_CV_INIT_EML_FOR(0,1,0,126,136,159);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 17;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)
            c3_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 17;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c3_Plane)[6];
          real_T (*c3_Dt)[17];
          real_T (*c3_Position)[3];
          real_T (*c3_Directions)[51];
          c3_Directions = (real_T (*)[51])ssGetInputPortSignal(chartInstance->S,
            2);
          c3_Position = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c3_Dt = (real_T (*)[17])ssGetOutputPortSignal(chartInstance->S, 1);
          c3_Plane = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_Plane);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_Dt);
          _SFD_SET_DATA_VALUE_PTR(2U, *c3_Position);
          _SFD_SET_DATA_VALUE_PTR(3U, *c3_Directions);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _falter_libraryMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "hqXdoJZKE0BVvk22a5bLpC";
}

static void sf_opaque_initialize_c3_falter_library(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_falter_libraryInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_falter_library((SFc3_falter_libraryInstanceStruct*)
    chartInstanceVar);
  initialize_c3_falter_library((SFc3_falter_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c3_falter_library(void *chartInstanceVar)
{
  enable_c3_falter_library((SFc3_falter_libraryInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_falter_library(void *chartInstanceVar)
{
  disable_c3_falter_library((SFc3_falter_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c3_falter_library(void *chartInstanceVar)
{
  sf_c3_falter_library((SFc3_falter_libraryInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_falter_library(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_falter_library
    ((SFc3_falter_libraryInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_falter_library();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c3_falter_library(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_falter_library();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_falter_library((SFc3_falter_libraryInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_falter_library(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_falter_library(S);
}

static void sf_opaque_set_sim_state_c3_falter_library(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c3_falter_library(S, st);
}

static void sf_opaque_terminate_c3_falter_library(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_falter_libraryInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_falter_library_optimization_info();
    }

    finalize_c3_falter_library((SFc3_falter_libraryInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_falter_library((SFc3_falter_libraryInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_falter_library(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_falter_library((SFc3_falter_libraryInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_falter_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_falter_library_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,3,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3350266401U));
  ssSetChecksum1(S,(4194783968U));
  ssSetChecksum2(S,(671691016U));
  ssSetChecksum3(S,(3254154264U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_falter_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_falter_library(SimStruct *S)
{
  SFc3_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc3_falter_libraryInstanceStruct *)utMalloc(sizeof
    (SFc3_falter_libraryInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_falter_libraryInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c3_falter_library;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_falter_library;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c3_falter_library;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_falter_library;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_falter_library;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c3_falter_library;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c3_falter_library;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_falter_library;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_falter_library;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_falter_library;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_falter_library;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c3_falter_library_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_falter_library(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_falter_library(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_falter_library(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_falter_library_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
