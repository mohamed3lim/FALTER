/* Include files */

#include <stddef.h>
#include "blas.h"
#include "falter_library_sfun.h"
#include "c4_falter_library.h"
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
static const char * c4_debug_family_names[9] = { "l", "At", "i", "nargin",
  "nargout", "Plane", "Position", "Directions", "Dt" };

/* Function Declarations */
static void initialize_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance);
static void initialize_params_c4_falter_library
  (SFc4_falter_libraryInstanceStruct *chartInstance);
static void enable_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance);
static void disable_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance);
static void c4_update_debugger_state_c4_falter_library
  (SFc4_falter_libraryInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c4_falter_library
  (SFc4_falter_libraryInstanceStruct *chartInstance);
static void set_sim_state_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_st);
static void finalize_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance);
static void sf_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance);
static void initSimStructsc4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance);
static void registerMessagesc4_falter_library(SFc4_falter_libraryInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static void c4_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct *chartInstance,
  const mxArray *c4_Dt, const char_T *c4_identifier, real_T c4_y[768]);
static void c4_b_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real_T c4_y[768]);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_c_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_d_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real_T c4_y[9]);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[90]);
static void c4_b_info_helper(c4_ResolvedFunctionInfo c4_info[90]);
static void c4_realmin(SFc4_falter_libraryInstanceStruct *chartInstance);
static void c4_eps(SFc4_falter_libraryInstanceStruct *chartInstance);
static void c4_eml_matlab_zgetrf(SFc4_falter_libraryInstanceStruct
  *chartInstance, real_T c4_A[9], real_T c4_b_A[9], int32_T c4_ipiv[3], int32_T *
  c4_info);
static void c4_check_forloop_overflow_error(SFc4_falter_libraryInstanceStruct
  *chartInstance, boolean_T c4_overflow);
static void c4_eml_xger(SFc4_falter_libraryInstanceStruct *chartInstance,
  int32_T c4_m, int32_T c4_n, real_T c4_alpha1, int32_T c4_ix0, int32_T c4_iy0,
  real_T c4_A[9], int32_T c4_ia0, real_T c4_b_A[9]);
static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_e_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_f_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_falter_library, const char_T *
  c4_identifier);
static uint8_T c4_g_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_eml_matlab_zgetrf(SFc4_falter_libraryInstanceStruct
  *chartInstance, real_T c4_A[9], int32_T c4_ipiv[3], int32_T *c4_info);
static void c4_b_eml_xger(SFc4_falter_libraryInstanceStruct *chartInstance,
  int32_T c4_m, int32_T c4_n, real_T c4_alpha1, int32_T c4_ix0, int32_T c4_iy0,
  real_T c4_A[9], int32_T c4_ia0);
static void init_dsm_address_info(SFc4_falter_libraryInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c4_is_active_c4_falter_library = 0U;
}

static void initialize_params_c4_falter_library
  (SFc4_falter_libraryInstanceStruct *chartInstance)
{
}

static void enable_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c4_update_debugger_state_c4_falter_library
  (SFc4_falter_libraryInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c4_falter_library
  (SFc4_falter_libraryInstanceStruct *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  int32_T c4_i0;
  real_T c4_u[768];
  const mxArray *c4_b_y = NULL;
  uint8_T c4_hoistedGlobal;
  uint8_T c4_b_u;
  const mxArray *c4_c_y = NULL;
  real_T (*c4_Dt)[768];
  c4_Dt = (real_T (*)[768])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellarray(2), FALSE);
  for (c4_i0 = 0; c4_i0 < 768; c4_i0++) {
    c4_u[c4_i0] = (*c4_Dt)[c4_i0];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 768), FALSE);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_hoistedGlobal = chartInstance->c4_is_active_c4_falter_library;
  c4_b_u = c4_hoistedGlobal;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  sf_mex_assign(&c4_st, c4_y, FALSE);
  return c4_st;
}

static void set_sim_state_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_u;
  real_T c4_dv0[768];
  int32_T c4_i1;
  real_T (*c4_Dt)[768];
  c4_Dt = (real_T (*)[768])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c4_doneDoubleBufferReInit = TRUE;
  c4_u = sf_mex_dup(c4_st);
  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)), "Dt",
                      c4_dv0);
  for (c4_i1 = 0; c4_i1 < 768; c4_i1++) {
    (*c4_Dt)[c4_i1] = c4_dv0[c4_i1];
  }

  chartInstance->c4_is_active_c4_falter_library = c4_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)),
     "is_active_c4_falter_library");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_falter_library(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance)
{
}

static void sf_c4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance)
{
  int32_T c4_i2;
  int32_T c4_i3;
  int32_T c4_i4;
  int32_T c4_i5;
  int32_T c4_i6;
  real_T c4_Plane[6];
  int32_T c4_i7;
  real_T c4_Position[3];
  int32_T c4_i8;
  real_T c4_Directions[2304];
  uint32_T c4_debug_family_var_map[9];
  real_T c4_l;
  real_T c4_At[9];
  real_T c4_i;
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 1.0;
  real_T c4_Dt[768];
  int32_T c4_i9;
  int32_T c4_i10;
  int32_T c4_i11;
  int32_T c4_i12;
  int32_T c4_i13;
  int32_T c4_b_i;
  int32_T c4_i14;
  real_T c4_x[9];
  int32_T c4_info;
  int32_T c4_ipiv[3];
  real_T c4_y;
  int32_T c4_k;
  real_T c4_b_k;
  real_T c4_a;
  real_T c4_b;
  boolean_T c4_isodd;
  int32_T c4_c_k;
  int32_T c4_b_a;
  real_T c4_b_b;
  int32_T c4_c_a;
  real_T c4_c_b;
  int32_T c4_idx;
  real_T c4_flt;
  boolean_T c4_p;
  int32_T c4_i15;
  real_T (*c4_b_Dt)[768];
  real_T (*c4_b_Directions)[2304];
  real_T (*c4_b_Position)[3];
  real_T (*c4_b_Plane)[6];
  c4_b_Directions = (real_T (*)[2304])ssGetInputPortSignal(chartInstance->S, 2);
  c4_b_Position = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
  c4_b_Dt = (real_T (*)[768])ssGetOutputPortSignal(chartInstance->S, 1);
  c4_b_Plane = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  for (c4_i2 = 0; c4_i2 < 6; c4_i2++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_Plane)[c4_i2], 0U);
  }

  for (c4_i3 = 0; c4_i3 < 768; c4_i3++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_Dt)[c4_i3], 1U);
  }

  for (c4_i4 = 0; c4_i4 < 3; c4_i4++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_Position)[c4_i4], 2U);
  }

  for (c4_i5 = 0; c4_i5 < 2304; c4_i5++) {
    _SFD_DATA_RANGE_CHECK((*c4_b_Directions)[c4_i5], 3U);
  }

  chartInstance->c4_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  for (c4_i6 = 0; c4_i6 < 6; c4_i6++) {
    c4_Plane[c4_i6] = (*c4_b_Plane)[c4_i6];
  }

  for (c4_i7 = 0; c4_i7 < 3; c4_i7++) {
    c4_Position[c4_i7] = (*c4_b_Position)[c4_i7];
  }

  for (c4_i8 = 0; c4_i8 < 2304; c4_i8++) {
    c4_Directions[c4_i8] = (*c4_b_Directions)[c4_i8];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_l, 0U, c4_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_At, 1U, c4_f_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_i, 2U, c4_e_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 3U, c4_e_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 4U, c4_e_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_Plane, 5U, c4_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_Position, 6U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_Directions, 7U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_Dt, 8U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 4);
  c4_l = 768.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 5);
  for (c4_i9 = 0; c4_i9 < 768; c4_i9++) {
    c4_Dt[c4_i9] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 6);
  c4_i10 = 0;
  for (c4_i11 = 0; c4_i11 < 2; c4_i11++) {
    for (c4_i12 = 0; c4_i12 < 3; c4_i12++) {
      c4_At[c4_i12 + c4_i10] = c4_Plane[c4_i12 + c4_i10];
    }

    c4_i10 += 3;
  }

  for (c4_i13 = 0; c4_i13 < 3; c4_i13++) {
    c4_At[c4_i13 + 6] = c4_Position[c4_i13];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 8);
  c4_i = 1.0;
  c4_b_i = 0;
  while (c4_b_i < 768) {
    c4_i = 1.0 + (real_T)c4_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 9);
    for (c4_i14 = 0; c4_i14 < 9; c4_i14++) {
      c4_x[c4_i14] = c4_At[c4_i14];
    }

    c4_b_eml_matlab_zgetrf(chartInstance, c4_x, c4_ipiv, &c4_info);
    c4_y = c4_x[0];
    for (c4_k = 0; c4_k < 2; c4_k++) {
      c4_b_k = 2.0 + (real_T)c4_k;
      c4_a = c4_y;
      c4_b = c4_x[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c4_b_k), 1, 3, 1, 0) + 3 * ((int32_T)(real_T)
        _SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("", c4_b_k),
        1, 3, 2, 0) - 1)) - 1];
      c4_y = c4_a * c4_b;
    }

    c4_isodd = FALSE;
    for (c4_c_k = 0; c4_c_k < 2; c4_c_k++) {
      c4_b_k = 1.0 + (real_T)c4_c_k;
      c4_b_a = c4_ipiv[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
        _SFD_INTEGER_CHECK("", c4_b_k), 1, 3, 1, 0) - 1];
      c4_b_b = c4_b_k;
      c4_c_a = c4_b_a;
      c4_c_b = c4_b_b;
      c4_idx = c4_c_a;
      c4_flt = c4_c_b;
      c4_p = ((real_T)c4_idx > c4_flt);
      if (c4_p) {
        c4_isodd = !c4_isodd;
      }
    }

    if (c4_isodd) {
      c4_y = -c4_y;
    }

    c4_Dt[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("Dt", (int32_T)
      _SFD_INTEGER_CHECK("i", c4_i), 1, 768, 1, 0) - 1] = c4_y;
    c4_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -9);
  _SFD_SYMBOL_SCOPE_POP();
  for (c4_i15 = 0; c4_i15 < 768; c4_i15++) {
    (*c4_b_Dt)[c4_i15] = c4_Dt[c4_i15];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_falter_libraryMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc4_falter_library(SFc4_falter_libraryInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc4_falter_library(SFc4_falter_libraryInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber)
{
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i16;
  real_T c4_b_inData[768];
  int32_T c4_i17;
  real_T c4_u[768];
  const mxArray *c4_y = NULL;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i16 = 0; c4_i16 < 768; c4_i16++) {
    c4_b_inData[c4_i16] = (*(real_T (*)[768])c4_inData)[c4_i16];
  }

  for (c4_i17 = 0; c4_i17 < 768; c4_i17++) {
    c4_u[c4_i17] = c4_b_inData[c4_i17];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 768), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static void c4_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct *chartInstance,
  const mxArray *c4_Dt, const char_T *c4_identifier, real_T c4_y[768])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_Dt), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_Dt);
}

static void c4_b_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real_T c4_y[768])
{
  real_T c4_dv1[768];
  int32_T c4_i18;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv1, 1, 0, 0U, 1, 0U, 1, 768);
  for (c4_i18 = 0; c4_i18 < 768; c4_i18++) {
    c4_y[c4_i18] = c4_dv1[c4_i18];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_Dt;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[768];
  int32_T c4_i19;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_Dt = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_Dt), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_Dt);
  for (c4_i19 = 0; c4_i19 < 768; c4_i19++) {
    (*(real_T (*)[768])c4_outData)[c4_i19] = c4_y[c4_i19];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i20;
  int32_T c4_i21;
  int32_T c4_i22;
  real_T c4_b_inData[2304];
  int32_T c4_i23;
  int32_T c4_i24;
  int32_T c4_i25;
  real_T c4_u[2304];
  const mxArray *c4_y = NULL;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i20 = 0;
  for (c4_i21 = 0; c4_i21 < 768; c4_i21++) {
    for (c4_i22 = 0; c4_i22 < 3; c4_i22++) {
      c4_b_inData[c4_i22 + c4_i20] = (*(real_T (*)[2304])c4_inData)[c4_i22 +
        c4_i20];
    }

    c4_i20 += 3;
  }

  c4_i23 = 0;
  for (c4_i24 = 0; c4_i24 < 768; c4_i24++) {
    for (c4_i25 = 0; c4_i25 < 3; c4_i25++) {
      c4_u[c4_i25 + c4_i23] = c4_b_inData[c4_i25 + c4_i23];
    }

    c4_i23 += 3;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 3, 768), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i26;
  real_T c4_b_inData[3];
  int32_T c4_i27;
  real_T c4_u[3];
  const mxArray *c4_y = NULL;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i26 = 0; c4_i26 < 3; c4_i26++) {
    c4_b_inData[c4_i26] = (*(real_T (*)[3])c4_inData)[c4_i26];
  }

  for (c4_i27 = 0; c4_i27 < 3; c4_i27++) {
    c4_u[c4_i27] = c4_b_inData[c4_i27];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i28;
  int32_T c4_i29;
  int32_T c4_i30;
  real_T c4_b_inData[6];
  int32_T c4_i31;
  int32_T c4_i32;
  int32_T c4_i33;
  real_T c4_u[6];
  const mxArray *c4_y = NULL;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i28 = 0;
  for (c4_i29 = 0; c4_i29 < 2; c4_i29++) {
    for (c4_i30 = 0; c4_i30 < 3; c4_i30++) {
      c4_b_inData[c4_i30 + c4_i28] = (*(real_T (*)[6])c4_inData)[c4_i30 + c4_i28];
    }

    c4_i28 += 3;
  }

  c4_i31 = 0;
  for (c4_i32 = 0; c4_i32 < 2; c4_i32++) {
    for (c4_i33 = 0; c4_i33 < 3; c4_i33++) {
      c4_u[c4_i33 + c4_i31] = c4_b_inData[c4_i33 + c4_i31];
    }

    c4_i31 += 3;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 3, 2), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static real_T c4_c_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_nargout;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_nargout = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_nargout), &c4_thisId);
  sf_mex_destroy(&c4_nargout);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i34;
  int32_T c4_i35;
  int32_T c4_i36;
  real_T c4_b_inData[9];
  int32_T c4_i37;
  int32_T c4_i38;
  int32_T c4_i39;
  real_T c4_u[9];
  const mxArray *c4_y = NULL;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i34 = 0;
  for (c4_i35 = 0; c4_i35 < 3; c4_i35++) {
    for (c4_i36 = 0; c4_i36 < 3; c4_i36++) {
      c4_b_inData[c4_i36 + c4_i34] = (*(real_T (*)[9])c4_inData)[c4_i36 + c4_i34];
    }

    c4_i34 += 3;
  }

  c4_i37 = 0;
  for (c4_i38 = 0; c4_i38 < 3; c4_i38++) {
    for (c4_i39 = 0; c4_i39 < 3; c4_i39++) {
      c4_u[c4_i39 + c4_i37] = c4_b_inData[c4_i39 + c4_i37];
    }

    c4_i37 += 3;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static void c4_d_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
  real_T c4_y[9])
{
  real_T c4_dv2[9];
  int32_T c4_i40;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv2, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c4_i40 = 0; c4_i40 < 9; c4_i40++) {
    c4_y[c4_i40] = c4_dv2[c4_i40];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_At;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[9];
  int32_T c4_i41;
  int32_T c4_i42;
  int32_T c4_i43;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_At = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_At), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_At);
  c4_i41 = 0;
  for (c4_i42 = 0; c4_i42 < 3; c4_i42++) {
    for (c4_i43 = 0; c4_i43 < 3; c4_i43++) {
      (*(real_T (*)[9])c4_outData)[c4_i43 + c4_i41] = c4_y[c4_i43 + c4_i41];
    }

    c4_i41 += 3;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_falter_library_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo;
  c4_ResolvedFunctionInfo c4_info[90];
  const mxArray *c4_m0 = NULL;
  int32_T c4_i44;
  c4_ResolvedFunctionInfo *c4_r0;
  c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  c4_info_helper(c4_info);
  c4_b_info_helper(c4_info);
  sf_mex_assign(&c4_m0, sf_mex_createstruct("nameCaptureInfo", 1, 90), FALSE);
  for (c4_i44 = 0; c4_i44 < 90; c4_i44++) {
    c4_r0 = &c4_info[c4_i44];
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->context)), "context", "nameCaptureInfo",
                    c4_i44);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c4_r0->name)), "name", "nameCaptureInfo", c4_i44);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c4_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c4_i44);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", c4_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->resolved)), "resolved", "nameCaptureInfo",
                    c4_i44);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c4_i44);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c4_i44);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c4_i44);
    sf_mex_addfield(c4_m0, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c4_i44);
  }

  sf_mex_assign(&c4_nameCaptureInfo, c4_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[90])
{
  c4_info[0].context = "";
  c4_info[0].name = "det";
  c4_info[0].dominantType = "double";
  c4_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c4_info[0].fileTimeLo = 1286818822U;
  c4_info[0].fileTimeHi = 0U;
  c4_info[0].mFileTimeLo = 0U;
  c4_info[0].mFileTimeHi = 0U;
  c4_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c4_info[1].name = "eml_index_class";
  c4_info[1].dominantType = "";
  c4_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[1].fileTimeLo = 1323170578U;
  c4_info[1].fileTimeHi = 0U;
  c4_info[1].mFileTimeLo = 0U;
  c4_info[1].mFileTimeHi = 0U;
  c4_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c4_info[2].name = "eml_xgetrf";
  c4_info[2].dominantType = "double";
  c4_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c4_info[2].fileTimeLo = 1286818806U;
  c4_info[2].fileTimeHi = 0U;
  c4_info[2].mFileTimeLo = 0U;
  c4_info[2].mFileTimeHi = 0U;
  c4_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/eml_xgetrf.m";
  c4_info[3].name = "eml_lapack_xgetrf";
  c4_info[3].dominantType = "double";
  c4_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c4_info[3].fileTimeLo = 1286818810U;
  c4_info[3].fileTimeHi = 0U;
  c4_info[3].mFileTimeLo = 0U;
  c4_info[3].mFileTimeHi = 0U;
  c4_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/internal/eml_lapack_xgetrf.m";
  c4_info[4].name = "eml_matlab_zgetrf";
  c4_info[4].dominantType = "double";
  c4_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[4].fileTimeLo = 1302688994U;
  c4_info[4].fileTimeHi = 0U;
  c4_info[4].mFileTimeLo = 0U;
  c4_info[4].mFileTimeHi = 0U;
  c4_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[5].name = "realmin";
  c4_info[5].dominantType = "char";
  c4_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c4_info[5].fileTimeLo = 1307651242U;
  c4_info[5].fileTimeHi = 0U;
  c4_info[5].mFileTimeLo = 0U;
  c4_info[5].mFileTimeHi = 0U;
  c4_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c4_info[6].name = "eml_realmin";
  c4_info[6].dominantType = "char";
  c4_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c4_info[6].fileTimeLo = 1307651244U;
  c4_info[6].fileTimeHi = 0U;
  c4_info[6].mFileTimeLo = 0U;
  c4_info[6].mFileTimeHi = 0U;
  c4_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c4_info[7].name = "eml_float_model";
  c4_info[7].dominantType = "char";
  c4_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c4_info[7].fileTimeLo = 1326727996U;
  c4_info[7].fileTimeHi = 0U;
  c4_info[7].mFileTimeLo = 0U;
  c4_info[7].mFileTimeHi = 0U;
  c4_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[8].name = "eps";
  c4_info[8].dominantType = "char";
  c4_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c4_info[8].fileTimeLo = 1326727996U;
  c4_info[8].fileTimeHi = 0U;
  c4_info[8].mFileTimeLo = 0U;
  c4_info[8].mFileTimeHi = 0U;
  c4_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c4_info[9].name = "eml_is_float_class";
  c4_info[9].dominantType = "char";
  c4_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c4_info[9].fileTimeLo = 1286818782U;
  c4_info[9].fileTimeHi = 0U;
  c4_info[9].mFileTimeLo = 0U;
  c4_info[9].mFileTimeHi = 0U;
  c4_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c4_info[10].name = "eml_eps";
  c4_info[10].dominantType = "char";
  c4_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c4_info[10].fileTimeLo = 1326727996U;
  c4_info[10].fileTimeHi = 0U;
  c4_info[10].mFileTimeLo = 0U;
  c4_info[10].mFileTimeHi = 0U;
  c4_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m";
  c4_info[11].name = "eml_float_model";
  c4_info[11].dominantType = "char";
  c4_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c4_info[11].fileTimeLo = 1326727996U;
  c4_info[11].fileTimeHi = 0U;
  c4_info[11].mFileTimeLo = 0U;
  c4_info[11].mFileTimeHi = 0U;
  c4_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[12].name = "min";
  c4_info[12].dominantType = "coder.internal.indexInt";
  c4_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c4_info[12].fileTimeLo = 1311255318U;
  c4_info[12].fileTimeHi = 0U;
  c4_info[12].mFileTimeLo = 0U;
  c4_info[12].mFileTimeHi = 0U;
  c4_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c4_info[13].name = "eml_min_or_max";
  c4_info[13].dominantType = "char";
  c4_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c4_info[13].fileTimeLo = 1334071490U;
  c4_info[13].fileTimeHi = 0U;
  c4_info[13].mFileTimeLo = 0U;
  c4_info[13].mFileTimeHi = 0U;
  c4_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c4_info[14].name = "eml_scalar_eg";
  c4_info[14].dominantType = "coder.internal.indexInt";
  c4_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[14].fileTimeLo = 1286818796U;
  c4_info[14].fileTimeHi = 0U;
  c4_info[14].mFileTimeLo = 0U;
  c4_info[14].mFileTimeHi = 0U;
  c4_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c4_info[15].name = "eml_scalexp_alloc";
  c4_info[15].dominantType = "coder.internal.indexInt";
  c4_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c4_info[15].fileTimeLo = 1352424860U;
  c4_info[15].fileTimeHi = 0U;
  c4_info[15].mFileTimeLo = 0U;
  c4_info[15].mFileTimeHi = 0U;
  c4_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c4_info[16].name = "eml_index_class";
  c4_info[16].dominantType = "";
  c4_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[16].fileTimeLo = 1323170578U;
  c4_info[16].fileTimeHi = 0U;
  c4_info[16].mFileTimeLo = 0U;
  c4_info[16].mFileTimeHi = 0U;
  c4_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c4_info[17].name = "eml_scalar_eg";
  c4_info[17].dominantType = "coder.internal.indexInt";
  c4_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[17].fileTimeLo = 1286818796U;
  c4_info[17].fileTimeHi = 0U;
  c4_info[17].mFileTimeLo = 0U;
  c4_info[17].mFileTimeHi = 0U;
  c4_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[18].name = "colon";
  c4_info[18].dominantType = "double";
  c4_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c4_info[18].fileTimeLo = 1348191928U;
  c4_info[18].fileTimeHi = 0U;
  c4_info[18].mFileTimeLo = 0U;
  c4_info[18].mFileTimeHi = 0U;
  c4_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c4_info[19].name = "colon";
  c4_info[19].dominantType = "double";
  c4_info[19].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c4_info[19].fileTimeLo = 1348191928U;
  c4_info[19].fileTimeHi = 0U;
  c4_info[19].mFileTimeLo = 0U;
  c4_info[19].mFileTimeHi = 0U;
  c4_info[20].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c4_info[20].name = "floor";
  c4_info[20].dominantType = "double";
  c4_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c4_info[20].fileTimeLo = 1343830380U;
  c4_info[20].fileTimeHi = 0U;
  c4_info[20].mFileTimeLo = 0U;
  c4_info[20].mFileTimeHi = 0U;
  c4_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c4_info[21].name = "eml_scalar_floor";
  c4_info[21].dominantType = "double";
  c4_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c4_info[21].fileTimeLo = 1286818726U;
  c4_info[21].fileTimeHi = 0U;
  c4_info[21].mFileTimeLo = 0U;
  c4_info[21].mFileTimeHi = 0U;
  c4_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c4_info[22].name = "intmin";
  c4_info[22].dominantType = "char";
  c4_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c4_info[22].fileTimeLo = 1311255318U;
  c4_info[22].fileTimeHi = 0U;
  c4_info[22].mFileTimeLo = 0U;
  c4_info[22].mFileTimeHi = 0U;
  c4_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c4_info[23].name = "intmax";
  c4_info[23].dominantType = "char";
  c4_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c4_info[23].fileTimeLo = 1311255316U;
  c4_info[23].fileTimeHi = 0U;
  c4_info[23].mFileTimeLo = 0U;
  c4_info[23].mFileTimeHi = 0U;
  c4_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c4_info[24].name = "intmin";
  c4_info[24].dominantType = "char";
  c4_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c4_info[24].fileTimeLo = 1311255318U;
  c4_info[24].fileTimeHi = 0U;
  c4_info[24].mFileTimeLo = 0U;
  c4_info[24].mFileTimeHi = 0U;
  c4_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c4_info[25].name = "intmax";
  c4_info[25].dominantType = "char";
  c4_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c4_info[25].fileTimeLo = 1311255316U;
  c4_info[25].fileTimeHi = 0U;
  c4_info[25].mFileTimeLo = 0U;
  c4_info[25].mFileTimeHi = 0U;
  c4_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher";
  c4_info[26].name = "eml_isa_uint";
  c4_info[26].dominantType = "coder.internal.indexInt";
  c4_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c4_info[26].fileTimeLo = 1286818784U;
  c4_info[26].fileTimeHi = 0U;
  c4_info[26].mFileTimeLo = 0U;
  c4_info[26].mFileTimeHi = 0U;
  c4_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c4_info[27].name = "eml_unsigned_class";
  c4_info[27].dominantType = "char";
  c4_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c4_info[27].fileTimeLo = 1323170580U;
  c4_info[27].fileTimeHi = 0U;
  c4_info[27].mFileTimeLo = 0U;
  c4_info[27].mFileTimeHi = 0U;
  c4_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m";
  c4_info[28].name = "eml_index_class";
  c4_info[28].dominantType = "";
  c4_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[28].fileTimeLo = 1323170578U;
  c4_info[28].fileTimeHi = 0U;
  c4_info[28].mFileTimeLo = 0U;
  c4_info[28].mFileTimeHi = 0U;
  c4_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c4_info[29].name = "eml_index_class";
  c4_info[29].dominantType = "";
  c4_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[29].fileTimeLo = 1323170578U;
  c4_info[29].fileTimeHi = 0U;
  c4_info[29].mFileTimeLo = 0U;
  c4_info[29].mFileTimeHi = 0U;
  c4_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c4_info[30].name = "intmax";
  c4_info[30].dominantType = "char";
  c4_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c4_info[30].fileTimeLo = 1311255316U;
  c4_info[30].fileTimeHi = 0U;
  c4_info[30].mFileTimeLo = 0U;
  c4_info[30].mFileTimeHi = 0U;
  c4_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c4_info[31].name = "eml_isa_uint";
  c4_info[31].dominantType = "coder.internal.indexInt";
  c4_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c4_info[31].fileTimeLo = 1286818784U;
  c4_info[31].fileTimeHi = 0U;
  c4_info[31].mFileTimeLo = 0U;
  c4_info[31].mFileTimeHi = 0U;
  c4_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd";
  c4_info[32].name = "eml_index_plus";
  c4_info[32].dominantType = "double";
  c4_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c4_info[32].fileTimeLo = 1286818778U;
  c4_info[32].fileTimeHi = 0U;
  c4_info[32].mFileTimeLo = 0U;
  c4_info[32].mFileTimeHi = 0U;
  c4_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c4_info[33].name = "eml_index_class";
  c4_info[33].dominantType = "";
  c4_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[33].fileTimeLo = 1323170578U;
  c4_info[33].fileTimeHi = 0U;
  c4_info[33].mFileTimeLo = 0U;
  c4_info[33].mFileTimeHi = 0U;
  c4_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_signed_integer_colon";
  c4_info[34].name = "eml_int_forloop_overflow_check";
  c4_info[34].dominantType = "";
  c4_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c4_info[34].fileTimeLo = 1346510340U;
  c4_info[34].fileTimeHi = 0U;
  c4_info[34].mFileTimeLo = 0U;
  c4_info[34].mFileTimeHi = 0U;
  c4_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c4_info[35].name = "intmax";
  c4_info[35].dominantType = "char";
  c4_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c4_info[35].fileTimeLo = 1311255316U;
  c4_info[35].fileTimeHi = 0U;
  c4_info[35].mFileTimeLo = 0U;
  c4_info[35].mFileTimeHi = 0U;
  c4_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[36].name = "eml_index_class";
  c4_info[36].dominantType = "";
  c4_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[36].fileTimeLo = 1323170578U;
  c4_info[36].fileTimeHi = 0U;
  c4_info[36].mFileTimeLo = 0U;
  c4_info[36].mFileTimeHi = 0U;
  c4_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[37].name = "eml_index_plus";
  c4_info[37].dominantType = "double";
  c4_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c4_info[37].fileTimeLo = 1286818778U;
  c4_info[37].fileTimeHi = 0U;
  c4_info[37].mFileTimeLo = 0U;
  c4_info[37].mFileTimeHi = 0U;
  c4_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[38].name = "eml_int_forloop_overflow_check";
  c4_info[38].dominantType = "";
  c4_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c4_info[38].fileTimeLo = 1346510340U;
  c4_info[38].fileTimeHi = 0U;
  c4_info[38].mFileTimeLo = 0U;
  c4_info[38].mFileTimeHi = 0U;
  c4_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[39].name = "eml_index_minus";
  c4_info[39].dominantType = "double";
  c4_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c4_info[39].fileTimeLo = 1286818778U;
  c4_info[39].fileTimeHi = 0U;
  c4_info[39].mFileTimeLo = 0U;
  c4_info[39].mFileTimeHi = 0U;
  c4_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c4_info[40].name = "eml_index_class";
  c4_info[40].dominantType = "";
  c4_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[40].fileTimeLo = 1323170578U;
  c4_info[40].fileTimeHi = 0U;
  c4_info[40].mFileTimeLo = 0U;
  c4_info[40].mFileTimeHi = 0U;
  c4_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[41].name = "eml_index_minus";
  c4_info[41].dominantType = "coder.internal.indexInt";
  c4_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c4_info[41].fileTimeLo = 1286818778U;
  c4_info[41].fileTimeHi = 0U;
  c4_info[41].mFileTimeLo = 0U;
  c4_info[41].mFileTimeHi = 0U;
  c4_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[42].name = "eml_index_times";
  c4_info[42].dominantType = "coder.internal.indexInt";
  c4_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c4_info[42].fileTimeLo = 1286818780U;
  c4_info[42].fileTimeHi = 0U;
  c4_info[42].mFileTimeLo = 0U;
  c4_info[42].mFileTimeHi = 0U;
  c4_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c4_info[43].name = "eml_index_class";
  c4_info[43].dominantType = "";
  c4_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[43].fileTimeLo = 1323170578U;
  c4_info[43].fileTimeHi = 0U;
  c4_info[43].mFileTimeLo = 0U;
  c4_info[43].mFileTimeHi = 0U;
  c4_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[44].name = "eml_index_plus";
  c4_info[44].dominantType = "coder.internal.indexInt";
  c4_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c4_info[44].fileTimeLo = 1286818778U;
  c4_info[44].fileTimeHi = 0U;
  c4_info[44].mFileTimeLo = 0U;
  c4_info[44].mFileTimeHi = 0U;
  c4_info[45].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[45].name = "eml_ixamax";
  c4_info[45].dominantType = "double";
  c4_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c4_info[45].fileTimeLo = 1299076770U;
  c4_info[45].fileTimeHi = 0U;
  c4_info[45].mFileTimeLo = 0U;
  c4_info[45].mFileTimeHi = 0U;
  c4_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_ixamax.m";
  c4_info[46].name = "eml_blas_inline";
  c4_info[46].dominantType = "";
  c4_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c4_info[46].fileTimeLo = 1299076768U;
  c4_info[46].fileTimeHi = 0U;
  c4_info[46].mFileTimeLo = 0U;
  c4_info[46].mFileTimeHi = 0U;
  c4_info[47].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m!below_threshold";
  c4_info[47].name = "length";
  c4_info[47].dominantType = "double";
  c4_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c4_info[47].fileTimeLo = 1303146206U;
  c4_info[47].fileTimeHi = 0U;
  c4_info[47].mFileTimeLo = 0U;
  c4_info[47].mFileTimeHi = 0U;
  c4_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength";
  c4_info[48].name = "eml_index_class";
  c4_info[48].dominantType = "";
  c4_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[48].fileTimeLo = 1323170578U;
  c4_info[48].fileTimeHi = 0U;
  c4_info[48].mFileTimeLo = 0U;
  c4_info[48].mFileTimeHi = 0U;
  c4_info[49].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c4_info[49].name = "eml_index_class";
  c4_info[49].dominantType = "";
  c4_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[49].fileTimeLo = 1323170578U;
  c4_info[49].fileTimeHi = 0U;
  c4_info[49].mFileTimeLo = 0U;
  c4_info[49].mFileTimeHi = 0U;
  c4_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_ixamax.m";
  c4_info[50].name = "eml_refblas_ixamax";
  c4_info[50].dominantType = "double";
  c4_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c4_info[50].fileTimeLo = 1299076770U;
  c4_info[50].fileTimeHi = 0U;
  c4_info[50].mFileTimeLo = 0U;
  c4_info[50].mFileTimeHi = 0U;
  c4_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c4_info[51].name = "eml_index_class";
  c4_info[51].dominantType = "";
  c4_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[51].fileTimeLo = 1323170578U;
  c4_info[51].fileTimeHi = 0U;
  c4_info[51].mFileTimeLo = 0U;
  c4_info[51].mFileTimeHi = 0U;
  c4_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c4_info[52].name = "eml_xcabs1";
  c4_info[52].dominantType = "double";
  c4_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c4_info[52].fileTimeLo = 1286818706U;
  c4_info[52].fileTimeHi = 0U;
  c4_info[52].mFileTimeLo = 0U;
  c4_info[52].mFileTimeHi = 0U;
  c4_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c4_info[53].name = "abs";
  c4_info[53].dominantType = "double";
  c4_info[53].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c4_info[53].fileTimeLo = 1343830366U;
  c4_info[53].fileTimeHi = 0U;
  c4_info[53].mFileTimeLo = 0U;
  c4_info[53].mFileTimeHi = 0U;
  c4_info[54].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c4_info[54].name = "eml_scalar_abs";
  c4_info[54].dominantType = "double";
  c4_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c4_info[54].fileTimeLo = 1286818712U;
  c4_info[54].fileTimeHi = 0U;
  c4_info[54].mFileTimeLo = 0U;
  c4_info[54].mFileTimeHi = 0U;
  c4_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c4_info[55].name = "eml_int_forloop_overflow_check";
  c4_info[55].dominantType = "";
  c4_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c4_info[55].fileTimeLo = 1346510340U;
  c4_info[55].fileTimeHi = 0U;
  c4_info[55].mFileTimeLo = 0U;
  c4_info[55].mFileTimeHi = 0U;
  c4_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_ixamax.m";
  c4_info[56].name = "eml_index_plus";
  c4_info[56].dominantType = "coder.internal.indexInt";
  c4_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c4_info[56].fileTimeLo = 1286818778U;
  c4_info[56].fileTimeHi = 0U;
  c4_info[56].mFileTimeLo = 0U;
  c4_info[56].mFileTimeHi = 0U;
  c4_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[57].name = "eml_xswap";
  c4_info[57].dominantType = "double";
  c4_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c4_info[57].fileTimeLo = 1299076778U;
  c4_info[57].fileTimeHi = 0U;
  c4_info[57].mFileTimeLo = 0U;
  c4_info[57].mFileTimeHi = 0U;
  c4_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xswap.m";
  c4_info[58].name = "eml_blas_inline";
  c4_info[58].dominantType = "";
  c4_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c4_info[58].fileTimeLo = 1299076768U;
  c4_info[58].fileTimeHi = 0U;
  c4_info[58].mFileTimeLo = 0U;
  c4_info[58].mFileTimeHi = 0U;
  c4_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c4_info[59].name = "eml_index_class";
  c4_info[59].dominantType = "";
  c4_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[59].fileTimeLo = 1323170578U;
  c4_info[59].fileTimeHi = 0U;
  c4_info[59].mFileTimeLo = 0U;
  c4_info[59].mFileTimeHi = 0U;
  c4_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xswap.m";
  c4_info[60].name = "eml_refblas_xswap";
  c4_info[60].dominantType = "double";
  c4_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c4_info[60].fileTimeLo = 1299076786U;
  c4_info[60].fileTimeHi = 0U;
  c4_info[60].mFileTimeLo = 0U;
  c4_info[60].mFileTimeHi = 0U;
  c4_info[61].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c4_info[61].name = "eml_index_class";
  c4_info[61].dominantType = "";
  c4_info[61].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[61].fileTimeLo = 1323170578U;
  c4_info[61].fileTimeHi = 0U;
  c4_info[61].mFileTimeLo = 0U;
  c4_info[61].mFileTimeHi = 0U;
  c4_info[62].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c4_info[62].name = "abs";
  c4_info[62].dominantType = "coder.internal.indexInt";
  c4_info[62].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c4_info[62].fileTimeLo = 1343830366U;
  c4_info[62].fileTimeHi = 0U;
  c4_info[62].mFileTimeLo = 0U;
  c4_info[62].mFileTimeHi = 0U;
  c4_info[63].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c4_info[63].name = "eml_scalar_abs";
  c4_info[63].dominantType = "coder.internal.indexInt";
  c4_info[63].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c4_info[63].fileTimeLo = 1286818712U;
  c4_info[63].fileTimeHi = 0U;
  c4_info[63].mFileTimeLo = 0U;
  c4_info[63].mFileTimeHi = 0U;
}

static void c4_b_info_helper(c4_ResolvedFunctionInfo c4_info[90])
{
  c4_info[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c4_info[64].name = "eml_int_forloop_overflow_check";
  c4_info[64].dominantType = "";
  c4_info[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c4_info[64].fileTimeLo = 1346510340U;
  c4_info[64].fileTimeHi = 0U;
  c4_info[64].mFileTimeLo = 0U;
  c4_info[64].mFileTimeHi = 0U;
  c4_info[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xswap.m";
  c4_info[65].name = "eml_index_plus";
  c4_info[65].dominantType = "coder.internal.indexInt";
  c4_info[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c4_info[65].fileTimeLo = 1286818778U;
  c4_info[65].fileTimeHi = 0U;
  c4_info[65].mFileTimeLo = 0U;
  c4_info[65].mFileTimeHi = 0U;
  c4_info[66].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[66].name = "eml_div";
  c4_info[66].dominantType = "double";
  c4_info[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c4_info[66].fileTimeLo = 1313347810U;
  c4_info[66].fileTimeHi = 0U;
  c4_info[66].mFileTimeLo = 0U;
  c4_info[66].mFileTimeHi = 0U;
  c4_info[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/lapack/matlab/eml_matlab_zgetrf.m";
  c4_info[67].name = "eml_xgeru";
  c4_info[67].dominantType = "double";
  c4_info[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c4_info[67].fileTimeLo = 1299076774U;
  c4_info[67].fileTimeHi = 0U;
  c4_info[67].mFileTimeLo = 0U;
  c4_info[67].mFileTimeHi = 0U;
  c4_info[68].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c4_info[68].name = "eml_blas_inline";
  c4_info[68].dominantType = "";
  c4_info[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c4_info[68].fileTimeLo = 1299076768U;
  c4_info[68].fileTimeHi = 0U;
  c4_info[68].mFileTimeLo = 0U;
  c4_info[68].mFileTimeHi = 0U;
  c4_info[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgeru.m";
  c4_info[69].name = "eml_xger";
  c4_info[69].dominantType = "double";
  c4_info[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c4_info[69].fileTimeLo = 1299076774U;
  c4_info[69].fileTimeHi = 0U;
  c4_info[69].mFileTimeLo = 0U;
  c4_info[69].mFileTimeHi = 0U;
  c4_info[70].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xger.m";
  c4_info[70].name = "eml_blas_inline";
  c4_info[70].dominantType = "";
  c4_info[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c4_info[70].fileTimeLo = 1299076768U;
  c4_info[70].fileTimeHi = 0U;
  c4_info[70].mFileTimeLo = 0U;
  c4_info[70].mFileTimeHi = 0U;
  c4_info[71].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m!below_threshold";
  c4_info[71].name = "intmax";
  c4_info[71].dominantType = "char";
  c4_info[71].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c4_info[71].fileTimeLo = 1311255316U;
  c4_info[71].fileTimeHi = 0U;
  c4_info[71].mFileTimeLo = 0U;
  c4_info[71].mFileTimeHi = 0U;
  c4_info[72].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m!below_threshold";
  c4_info[72].name = "min";
  c4_info[72].dominantType = "double";
  c4_info[72].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m";
  c4_info[72].fileTimeLo = 1311255318U;
  c4_info[72].fileTimeHi = 0U;
  c4_info[72].mFileTimeLo = 0U;
  c4_info[72].mFileTimeHi = 0U;
  c4_info[73].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c4_info[73].name = "eml_scalar_eg";
  c4_info[73].dominantType = "double";
  c4_info[73].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[73].fileTimeLo = 1286818796U;
  c4_info[73].fileTimeHi = 0U;
  c4_info[73].mFileTimeLo = 0U;
  c4_info[73].mFileTimeHi = 0U;
  c4_info[74].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c4_info[74].name = "eml_scalexp_alloc";
  c4_info[74].dominantType = "double";
  c4_info[74].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c4_info[74].fileTimeLo = 1352424860U;
  c4_info[74].fileTimeHi = 0U;
  c4_info[74].mFileTimeLo = 0U;
  c4_info[74].mFileTimeHi = 0U;
  c4_info[75].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c4_info[75].name = "eml_scalar_eg";
  c4_info[75].dominantType = "double";
  c4_info[75].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c4_info[75].fileTimeLo = 1286818796U;
  c4_info[75].fileTimeHi = 0U;
  c4_info[75].mFileTimeLo = 0U;
  c4_info[75].mFileTimeHi = 0U;
  c4_info[76].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m!below_threshold";
  c4_info[76].name = "mtimes";
  c4_info[76].dominantType = "double";
  c4_info[76].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[76].fileTimeLo = 1289519692U;
  c4_info[76].fileTimeHi = 0U;
  c4_info[76].mFileTimeLo = 0U;
  c4_info[76].mFileTimeHi = 0U;
  c4_info[77].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c4_info[77].name = "eml_index_class";
  c4_info[77].dominantType = "";
  c4_info[77].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[77].fileTimeLo = 1323170578U;
  c4_info[77].fileTimeHi = 0U;
  c4_info[77].mFileTimeLo = 0U;
  c4_info[77].mFileTimeHi = 0U;
  c4_info[78].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xger.m";
  c4_info[78].name = "eml_refblas_xger";
  c4_info[78].dominantType = "double";
  c4_info[78].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c4_info[78].fileTimeLo = 1299076776U;
  c4_info[78].fileTimeHi = 0U;
  c4_info[78].mFileTimeLo = 0U;
  c4_info[78].mFileTimeHi = 0U;
  c4_info[79].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xger.m";
  c4_info[79].name = "eml_refblas_xgerx";
  c4_info[79].dominantType = "char";
  c4_info[79].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c4_info[79].fileTimeLo = 1299076778U;
  c4_info[79].fileTimeHi = 0U;
  c4_info[79].mFileTimeLo = 0U;
  c4_info[79].mFileTimeHi = 0U;
  c4_info[80].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c4_info[80].name = "eml_index_class";
  c4_info[80].dominantType = "";
  c4_info[80].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c4_info[80].fileTimeLo = 1323170578U;
  c4_info[80].fileTimeHi = 0U;
  c4_info[80].mFileTimeLo = 0U;
  c4_info[80].mFileTimeHi = 0U;
  c4_info[81].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c4_info[81].name = "abs";
  c4_info[81].dominantType = "coder.internal.indexInt";
  c4_info[81].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c4_info[81].fileTimeLo = 1343830366U;
  c4_info[81].fileTimeHi = 0U;
  c4_info[81].mFileTimeLo = 0U;
  c4_info[81].mFileTimeHi = 0U;
  c4_info[82].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c4_info[82].name = "eml_index_minus";
  c4_info[82].dominantType = "double";
  c4_info[82].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c4_info[82].fileTimeLo = 1286818778U;
  c4_info[82].fileTimeHi = 0U;
  c4_info[82].mFileTimeLo = 0U;
  c4_info[82].mFileTimeHi = 0U;
  c4_info[83].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c4_info[83].name = "eml_int_forloop_overflow_check";
  c4_info[83].dominantType = "";
  c4_info[83].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c4_info[83].fileTimeLo = 1346510340U;
  c4_info[83].fileTimeHi = 0U;
  c4_info[83].mFileTimeLo = 0U;
  c4_info[83].mFileTimeHi = 0U;
  c4_info[84].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c4_info[84].name = "eml_index_plus";
  c4_info[84].dominantType = "double";
  c4_info[84].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c4_info[84].fileTimeLo = 1286818778U;
  c4_info[84].fileTimeHi = 0U;
  c4_info[84].mFileTimeLo = 0U;
  c4_info[84].mFileTimeHi = 0U;
  c4_info[85].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgerx.m";
  c4_info[85].name = "eml_index_plus";
  c4_info[85].dominantType = "coder.internal.indexInt";
  c4_info[85].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c4_info[85].fileTimeLo = 1286818778U;
  c4_info[85].fileTimeHi = 0U;
  c4_info[85].mFileTimeLo = 0U;
  c4_info[85].mFileTimeHi = 0U;
  c4_info[86].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c4_info[86].name = "mtimes";
  c4_info[86].dominantType = "double";
  c4_info[86].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c4_info[86].fileTimeLo = 1289519692U;
  c4_info[86].fileTimeHi = 0U;
  c4_info[86].mFileTimeLo = 0U;
  c4_info[86].mFileTimeHi = 0U;
  c4_info[87].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/det.m";
  c4_info[87].name = "coder.internal.indexIntRelop";
  c4_info[87].dominantType = "";
  c4_info[87].resolved =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m";
  c4_info[87].fileTimeLo = 1326728322U;
  c4_info[87].fileTimeHi = 0U;
  c4_info[87].mFileTimeLo = 0U;
  c4_info[87].mFileTimeHi = 0U;
  c4_info[88].context =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!float_class_contains_indexIntClass";
  c4_info[88].name = "eml_float_model";
  c4_info[88].dominantType = "char";
  c4_info[88].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c4_info[88].fileTimeLo = 1326727996U;
  c4_info[88].fileTimeHi = 0U;
  c4_info[88].mFileTimeLo = 0U;
  c4_info[88].mFileTimeHi = 0U;
  c4_info[89].context =
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!is_signed_indexIntClass";
  c4_info[89].name = "intmin";
  c4_info[89].dominantType = "char";
  c4_info[89].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m";
  c4_info[89].fileTimeLo = 1311255318U;
  c4_info[89].fileTimeHi = 0U;
  c4_info[89].mFileTimeLo = 0U;
  c4_info[89].mFileTimeHi = 0U;
}

static void c4_realmin(SFc4_falter_libraryInstanceStruct *chartInstance)
{
}

static void c4_eps(SFc4_falter_libraryInstanceStruct *chartInstance)
{
}

static void c4_eml_matlab_zgetrf(SFc4_falter_libraryInstanceStruct
  *chartInstance, real_T c4_A[9], real_T c4_b_A[9], int32_T c4_ipiv[3], int32_T *
  c4_info)
{
  int32_T c4_i45;
  for (c4_i45 = 0; c4_i45 < 9; c4_i45++) {
    c4_b_A[c4_i45] = c4_A[c4_i45];
  }

  c4_b_eml_matlab_zgetrf(chartInstance, c4_b_A, c4_ipiv, c4_info);
}

static void c4_check_forloop_overflow_error(SFc4_falter_libraryInstanceStruct
  *chartInstance, boolean_T c4_overflow)
{
  int32_T c4_i46;
  static char_T c4_cv0[34] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'i', 'n', 't', '_', 'f', 'o', 'r', 'l', 'o', 'o', 'p',
    '_', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w' };

  char_T c4_u[34];
  const mxArray *c4_y = NULL;
  int32_T c4_i47;
  static char_T c4_cv1[23] = { 'c', 'o', 'd', 'e', 'r', '.', 'i', 'n', 't', 'e',
    'r', 'n', 'a', 'l', '.', 'i', 'n', 'd', 'e', 'x', 'I', 'n', 't' };

  char_T c4_b_u[23];
  const mxArray *c4_b_y = NULL;
  if (!c4_overflow) {
  } else {
    for (c4_i46 = 0; c4_i46 < 34; c4_i46++) {
      c4_u[c4_i46] = c4_cv0[c4_i46];
    }

    c4_y = NULL;
    sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 10, 0U, 1U, 0U, 2, 1, 34),
                  FALSE);
    for (c4_i47 = 0; c4_i47 < 23; c4_i47++) {
      c4_b_u[c4_i47] = c4_cv1[c4_i47];
    }

    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 23),
                  FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 2U,
      14, c4_y, 14, c4_b_y));
  }
}

static void c4_eml_xger(SFc4_falter_libraryInstanceStruct *chartInstance,
  int32_T c4_m, int32_T c4_n, real_T c4_alpha1, int32_T c4_ix0, int32_T c4_iy0,
  real_T c4_A[9], int32_T c4_ia0, real_T c4_b_A[9])
{
  int32_T c4_i48;
  for (c4_i48 = 0; c4_i48 < 9; c4_i48++) {
    c4_b_A[c4_i48] = c4_A[c4_i48];
  }

  c4_b_eml_xger(chartInstance, c4_m, c4_n, c4_alpha1, c4_ix0, c4_iy0, c4_b_A,
                c4_ia0);
}

static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, FALSE);
  return c4_mxArrayOutData;
}

static int32_T c4_e_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i49;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i49, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i49;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_f_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_falter_library, const char_T *
  c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_falter_library), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_falter_library);
  return c4_y;
}

static uint8_T c4_g_emlrt_marshallIn(SFc4_falter_libraryInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_eml_matlab_zgetrf(SFc4_falter_libraryInstanceStruct
  *chartInstance, real_T c4_A[9], int32_T c4_ipiv[3], int32_T *c4_info)
{
  int32_T c4_i50;
  int32_T c4_j;
  int32_T c4_b_j;
  int32_T c4_a;
  int32_T c4_jm1;
  int32_T c4_b;
  int32_T c4_mmj;
  int32_T c4_b_a;
  int32_T c4_c;
  int32_T c4_b_b;
  int32_T c4_jj;
  int32_T c4_c_a;
  int32_T c4_jp1j;
  int32_T c4_d_a;
  int32_T c4_b_c;
  int32_T c4_n;
  int32_T c4_ix0;
  int32_T c4_b_n;
  int32_T c4_b_ix0;
  int32_T c4_c_n;
  int32_T c4_c_ix0;
  int32_T c4_idxmax;
  int32_T c4_ix;
  real_T c4_x;
  real_T c4_b_x;
  real_T c4_c_x;
  real_T c4_y;
  real_T c4_d_x;
  real_T c4_e_x;
  real_T c4_b_y;
  real_T c4_smax;
  int32_T c4_d_n;
  int32_T c4_c_b;
  int32_T c4_d_b;
  boolean_T c4_overflow;
  int32_T c4_k;
  int32_T c4_b_k;
  int32_T c4_e_a;
  real_T c4_f_x;
  real_T c4_g_x;
  real_T c4_h_x;
  real_T c4_c_y;
  real_T c4_i_x;
  real_T c4_j_x;
  real_T c4_d_y;
  real_T c4_s;
  int32_T c4_f_a;
  int32_T c4_jpiv_offset;
  int32_T c4_g_a;
  int32_T c4_e_b;
  int32_T c4_jpiv;
  int32_T c4_h_a;
  int32_T c4_f_b;
  int32_T c4_c_c;
  int32_T c4_g_b;
  int32_T c4_jrow;
  int32_T c4_i_a;
  int32_T c4_h_b;
  int32_T c4_jprow;
  int32_T c4_d_ix0;
  int32_T c4_iy0;
  int32_T c4_e_ix0;
  int32_T c4_b_iy0;
  int32_T c4_f_ix0;
  int32_T c4_c_iy0;
  int32_T c4_b_ix;
  int32_T c4_iy;
  int32_T c4_c_k;
  real_T c4_temp;
  int32_T c4_j_a;
  int32_T c4_k_a;
  int32_T c4_b_jp1j;
  int32_T c4_l_a;
  int32_T c4_d_c;
  int32_T c4_m_a;
  int32_T c4_i_b;
  int32_T c4_i51;
  int32_T c4_n_a;
  int32_T c4_j_b;
  int32_T c4_o_a;
  int32_T c4_k_b;
  boolean_T c4_b_overflow;
  int32_T c4_i;
  int32_T c4_b_i;
  real_T c4_k_x;
  real_T c4_e_y;
  real_T c4_z;
  int32_T c4_l_b;
  int32_T c4_e_c;
  int32_T c4_p_a;
  int32_T c4_f_c;
  int32_T c4_q_a;
  int32_T c4_g_c;
  int32_T c4_m;
  int32_T c4_e_n;
  int32_T c4_g_ix0;
  int32_T c4_d_iy0;
  int32_T c4_ia0;
  real_T c4_d1;
  c4_realmin(chartInstance);
  c4_eps(chartInstance);
  for (c4_i50 = 0; c4_i50 < 3; c4_i50++) {
    c4_ipiv[c4_i50] = 1 + c4_i50;
  }

  *c4_info = 0;
  for (c4_j = 1; c4_j < 3; c4_j++) {
    c4_b_j = c4_j;
    c4_a = c4_b_j - 1;
    c4_jm1 = c4_a;
    c4_b = c4_b_j;
    c4_mmj = 3 - c4_b;
    c4_b_a = c4_jm1;
    c4_c = c4_b_a << 2;
    c4_b_b = c4_c + 1;
    c4_jj = c4_b_b;
    c4_c_a = c4_jj + 1;
    c4_jp1j = c4_c_a;
    c4_d_a = c4_mmj;
    c4_b_c = c4_d_a;
    c4_n = c4_b_c + 1;
    c4_ix0 = c4_jj;
    c4_b_n = c4_n;
    c4_b_ix0 = c4_ix0;
    c4_c_n = c4_b_n;
    c4_c_ix0 = c4_b_ix0;
    if (c4_c_n < 1) {
      c4_idxmax = 0;
    } else {
      c4_idxmax = 1;
      if (c4_c_n > 1) {
        c4_ix = c4_c_ix0;
        c4_x = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
          "", (real_T)c4_ix), 1, 9, 1, 0) - 1];
        c4_b_x = c4_x;
        c4_c_x = c4_b_x;
        c4_y = muDoubleScalarAbs(c4_c_x);
        c4_d_x = 0.0;
        c4_e_x = c4_d_x;
        c4_b_y = muDoubleScalarAbs(c4_e_x);
        c4_smax = c4_y + c4_b_y;
        c4_d_n = c4_c_n;
        c4_c_b = c4_d_n;
        c4_d_b = c4_c_b;
        if (2 > c4_d_b) {
          c4_overflow = FALSE;
        } else {
          c4_overflow = (c4_d_b > 2147483646);
        }

        if (c4_overflow) {
          c4_check_forloop_overflow_error(chartInstance, c4_overflow);
        }

        for (c4_k = 2; c4_k <= c4_d_n; c4_k++) {
          c4_b_k = c4_k;
          c4_e_a = c4_ix + 1;
          c4_ix = c4_e_a;
          c4_f_x = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c4_ix), 1, 9, 1, 0) - 1];
          c4_g_x = c4_f_x;
          c4_h_x = c4_g_x;
          c4_c_y = muDoubleScalarAbs(c4_h_x);
          c4_i_x = 0.0;
          c4_j_x = c4_i_x;
          c4_d_y = muDoubleScalarAbs(c4_j_x);
          c4_s = c4_c_y + c4_d_y;
          if (c4_s > c4_smax) {
            c4_idxmax = c4_b_k;
            c4_smax = c4_s;
          }
        }
      }
    }

    c4_f_a = c4_idxmax - 1;
    c4_jpiv_offset = c4_f_a;
    c4_g_a = c4_jj;
    c4_e_b = c4_jpiv_offset;
    c4_jpiv = c4_g_a + c4_e_b;
    if (c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_jpiv), 1, 9, 1, 0) - 1] != 0.0) {
      if (c4_jpiv_offset != 0) {
        c4_h_a = c4_b_j;
        c4_f_b = c4_jpiv_offset;
        c4_c_c = c4_h_a + c4_f_b;
        c4_ipiv[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_b_j), 1, 3, 1, 0) - 1] = c4_c_c;
        c4_g_b = c4_jm1 + 1;
        c4_jrow = c4_g_b;
        c4_i_a = c4_jrow;
        c4_h_b = c4_jpiv_offset;
        c4_jprow = c4_i_a + c4_h_b;
        c4_d_ix0 = c4_jrow;
        c4_iy0 = c4_jprow;
        c4_e_ix0 = c4_d_ix0;
        c4_b_iy0 = c4_iy0;
        c4_f_ix0 = c4_e_ix0;
        c4_c_iy0 = c4_b_iy0;
        c4_b_ix = c4_f_ix0;
        c4_iy = c4_c_iy0;
        for (c4_c_k = 1; c4_c_k < 4; c4_c_k++) {
          c4_temp = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
            _SFD_INTEGER_CHECK("", (real_T)c4_b_ix), 1, 9, 1, 0) - 1];
          c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_b_ix), 1, 9, 1, 0) - 1] =
            c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_iy), 1, 9, 1, 0) - 1];
          c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_iy), 1, 9, 1, 0) - 1] = c4_temp;
          c4_j_a = c4_b_ix + 3;
          c4_b_ix = c4_j_a;
          c4_k_a = c4_iy + 3;
          c4_iy = c4_k_a;
        }
      }

      c4_b_jp1j = c4_jp1j;
      c4_l_a = c4_mmj;
      c4_d_c = c4_l_a;
      c4_m_a = c4_jp1j;
      c4_i_b = c4_d_c - 1;
      c4_i51 = c4_m_a + c4_i_b;
      c4_n_a = c4_b_jp1j;
      c4_j_b = c4_i51;
      c4_o_a = c4_n_a;
      c4_k_b = c4_j_b;
      if (c4_o_a > c4_k_b) {
        c4_b_overflow = FALSE;
      } else {
        c4_b_overflow = (c4_k_b > 2147483646);
      }

      if (c4_b_overflow) {
        c4_check_forloop_overflow_error(chartInstance, c4_b_overflow);
      }

      for (c4_i = c4_b_jp1j; c4_i <= c4_i51; c4_i++) {
        c4_b_i = c4_i;
        c4_k_x = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c4_b_i), 1, 9, 1, 0) - 1];
        c4_e_y = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)
          _SFD_INTEGER_CHECK("", (real_T)c4_jj), 1, 9, 1, 0) - 1];
        c4_z = c4_k_x / c4_e_y;
        c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
          (real_T)c4_b_i), 1, 9, 1, 0) - 1] = c4_z;
      }
    } else {
      *c4_info = c4_b_j;
    }

    c4_l_b = c4_b_j;
    c4_e_c = 3 - c4_l_b;
    c4_p_a = c4_jj;
    c4_f_c = c4_p_a;
    c4_q_a = c4_jj;
    c4_g_c = c4_q_a;
    c4_m = c4_mmj;
    c4_e_n = c4_e_c;
    c4_g_ix0 = c4_jp1j;
    c4_d_iy0 = c4_f_c + 3;
    c4_ia0 = c4_g_c + 4;
    c4_d1 = -1.0;
    c4_b_eml_xger(chartInstance, c4_m, c4_e_n, c4_d1, c4_g_ix0, c4_d_iy0, c4_A,
                  c4_ia0);
  }

  if (*c4_info == 0) {
    if (!(c4_A[8] != 0.0)) {
      *c4_info = 3;
    }
  }
}

static void c4_b_eml_xger(SFc4_falter_libraryInstanceStruct *chartInstance,
  int32_T c4_m, int32_T c4_n, real_T c4_alpha1, int32_T c4_ix0, int32_T c4_iy0,
  real_T c4_A[9], int32_T c4_ia0)
{
  int32_T c4_b_m;
  int32_T c4_b_n;
  real_T c4_b_alpha1;
  int32_T c4_b_ix0;
  int32_T c4_b_iy0;
  int32_T c4_b_ia0;
  int32_T c4_c_m;
  int32_T c4_c_n;
  real_T c4_c_alpha1;
  int32_T c4_c_ix0;
  int32_T c4_c_iy0;
  int32_T c4_c_ia0;
  int32_T c4_d_m;
  int32_T c4_d_n;
  real_T c4_d_alpha1;
  int32_T c4_d_ix0;
  int32_T c4_d_iy0;
  int32_T c4_d_ia0;
  int32_T c4_ixstart;
  int32_T c4_a;
  int32_T c4_jA;
  int32_T c4_jy;
  int32_T c4_e_n;
  int32_T c4_b;
  int32_T c4_b_b;
  boolean_T c4_overflow;
  int32_T c4_j;
  real_T c4_yjy;
  real_T c4_temp;
  int32_T c4_ix;
  int32_T c4_c_b;
  int32_T c4_i52;
  int32_T c4_b_a;
  int32_T c4_d_b;
  int32_T c4_i53;
  int32_T c4_c_a;
  int32_T c4_e_b;
  int32_T c4_d_a;
  int32_T c4_f_b;
  boolean_T c4_b_overflow;
  int32_T c4_ijA;
  int32_T c4_b_ijA;
  int32_T c4_e_a;
  int32_T c4_f_a;
  int32_T c4_g_a;
  c4_b_m = c4_m;
  c4_b_n = c4_n;
  c4_b_alpha1 = c4_alpha1;
  c4_b_ix0 = c4_ix0;
  c4_b_iy0 = c4_iy0;
  c4_b_ia0 = c4_ia0;
  c4_c_m = c4_b_m;
  c4_c_n = c4_b_n;
  c4_c_alpha1 = c4_b_alpha1;
  c4_c_ix0 = c4_b_ix0;
  c4_c_iy0 = c4_b_iy0;
  c4_c_ia0 = c4_b_ia0;
  c4_d_m = c4_c_m;
  c4_d_n = c4_c_n;
  c4_d_alpha1 = c4_c_alpha1;
  c4_d_ix0 = c4_c_ix0;
  c4_d_iy0 = c4_c_iy0;
  c4_d_ia0 = c4_c_ia0;
  if (c4_d_alpha1 == 0.0) {
  } else {
    c4_ixstart = c4_d_ix0;
    c4_a = c4_d_ia0 - 1;
    c4_jA = c4_a;
    c4_jy = c4_d_iy0;
    c4_e_n = c4_d_n;
    c4_b = c4_e_n;
    c4_b_b = c4_b;
    if (1 > c4_b_b) {
      c4_overflow = FALSE;
    } else {
      c4_overflow = (c4_b_b > 2147483646);
    }

    if (c4_overflow) {
      c4_check_forloop_overflow_error(chartInstance, c4_overflow);
    }

    for (c4_j = 1; c4_j <= c4_e_n; c4_j++) {
      c4_yjy = c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
        "", (real_T)c4_jy), 1, 9, 1, 0) - 1];
      if (c4_yjy != 0.0) {
        c4_temp = c4_yjy * c4_d_alpha1;
        c4_ix = c4_ixstart;
        c4_c_b = c4_jA + 1;
        c4_i52 = c4_c_b;
        c4_b_a = c4_d_m;
        c4_d_b = c4_jA;
        c4_i53 = c4_b_a + c4_d_b;
        c4_c_a = c4_i52;
        c4_e_b = c4_i53;
        c4_d_a = c4_c_a;
        c4_f_b = c4_e_b;
        if (c4_d_a > c4_f_b) {
          c4_b_overflow = FALSE;
        } else {
          c4_b_overflow = (c4_f_b > 2147483646);
        }

        if (c4_b_overflow) {
          c4_check_forloop_overflow_error(chartInstance, c4_b_overflow);
        }

        for (c4_ijA = c4_i52; c4_ijA <= c4_i53; c4_ijA++) {
          c4_b_ijA = c4_ijA;
          c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_b_ijA), 1, 9, 1, 0) - 1] =
            c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_b_ijA), 1, 9, 1, 0) - 1] +
            c4_A[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c4_ix), 1, 9, 1, 0) - 1] * c4_temp;
          c4_e_a = c4_ix + 1;
          c4_ix = c4_e_a;
        }
      }

      c4_f_a = c4_jy + 3;
      c4_jy = c4_f_a;
      c4_g_a = c4_jA + 3;
      c4_jA = c4_g_a;
    }
  }
}

static void init_dsm_address_info(SFc4_falter_libraryInstanceStruct
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

void sf_c4_falter_library_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(85207460U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4017388683U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3044744609U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3544213713U);
}

mxArray *sf_c4_falter_library_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("SdAk9wRjxEDF8QegnnJJmH");
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
      pr[1] = (double)(768);
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
      pr[0] = (double)(768);
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

mxArray *sf_c4_falter_library_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c4_falter_library(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"Dt\",},{M[8],M[0],T\"is_active_c4_falter_library\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_falter_library_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_falter_libraryInstanceStruct *chartInstance;
    chartInstance = (SFc4_falter_libraryInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _falter_libraryMachineNumber_,
           4,
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
            1.0,0,0,(MexFcnForType)c4_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 768;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)
            c4_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 768;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c4_Plane)[6];
          real_T (*c4_Dt)[768];
          real_T (*c4_Position)[3];
          real_T (*c4_Directions)[2304];
          c4_Directions = (real_T (*)[2304])ssGetInputPortSignal
            (chartInstance->S, 2);
          c4_Position = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 1);
          c4_Dt = (real_T (*)[768])ssGetOutputPortSignal(chartInstance->S, 1);
          c4_Plane = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c4_Plane);
          _SFD_SET_DATA_VALUE_PTR(1U, *c4_Dt);
          _SFD_SET_DATA_VALUE_PTR(2U, *c4_Position);
          _SFD_SET_DATA_VALUE_PTR(3U, *c4_Directions);
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
  return "rrqpqsYOyrU3xXwZ9mLHQC";
}

static void sf_opaque_initialize_c4_falter_library(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_falter_libraryInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c4_falter_library((SFc4_falter_libraryInstanceStruct*)
    chartInstanceVar);
  initialize_c4_falter_library((SFc4_falter_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c4_falter_library(void *chartInstanceVar)
{
  enable_c4_falter_library((SFc4_falter_libraryInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_falter_library(void *chartInstanceVar)
{
  disable_c4_falter_library((SFc4_falter_libraryInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c4_falter_library(void *chartInstanceVar)
{
  sf_c4_falter_library((SFc4_falter_libraryInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_falter_library(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_falter_library
    ((SFc4_falter_libraryInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_falter_library();/* state var info */
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

extern void sf_internal_set_sim_state_c4_falter_library(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_falter_library();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_falter_library((SFc4_falter_libraryInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c4_falter_library(SimStruct* S)
{
  return sf_internal_get_sim_state_c4_falter_library(S);
}

static void sf_opaque_set_sim_state_c4_falter_library(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c4_falter_library(S, st);
}

static void sf_opaque_terminate_c4_falter_library(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_falter_libraryInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_falter_library_optimization_info();
    }

    finalize_c4_falter_library((SFc4_falter_libraryInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_falter_library((SFc4_falter_libraryInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_falter_library(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_falter_library((SFc4_falter_libraryInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_falter_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_falter_library_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,4,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4223529743U));
  ssSetChecksum1(S,(3187520535U));
  ssSetChecksum2(S,(944485558U));
  ssSetChecksum3(S,(1881218580U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_falter_library(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_falter_library(SimStruct *S)
{
  SFc4_falter_libraryInstanceStruct *chartInstance;
  chartInstance = (SFc4_falter_libraryInstanceStruct *)utMalloc(sizeof
    (SFc4_falter_libraryInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_falter_libraryInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c4_falter_library;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c4_falter_library;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c4_falter_library;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_falter_library;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_falter_library;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c4_falter_library;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c4_falter_library;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c4_falter_library;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_falter_library;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_falter_library;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_falter_library;
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

void c4_falter_library_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_falter_library(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_falter_library(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_falter_library(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_falter_library_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
