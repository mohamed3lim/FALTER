#include "__cf_model_AllInOne.h"
#ifndef RTW_HEADER_model_AllInOne_acc_h_
#define RTW_HEADER_model_AllInOne_acc_h_
#ifndef model_AllInOne_acc_COMMON_INCLUDES_
#define model_AllInOne_acc_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#include <float.h>
#include <string.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "mwmathutil.h"
#include "blas.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif
#include "model_AllInOne_acc_types.h"
typedef struct { int8_T Sqrt_DWORK1 ; char pad_Sqrt_DWORK1 [ 7 ] ; }
DW_CoreSubsys_model_AllInOne_gh_T ; typedef struct { int8_T Sqrt_DWORK1 ;
char pad_Sqrt_DWORK1 [ 7 ] ; } DW_CoreSubsys_model_AllInOne_ght_T ; typedef
struct { real_T B_14_4_0 [ 3 ] ; } B_CoreSubsys_model_AllInOne_bab0_T ;
typedef struct { int8_T If_ActiveSubsystem ; int8_T
Intersectionis0ifsensorisintheplane_SubsysRanBC ; int8_T
Intersectionisinfifplaneandsensorareparalell_SubsysRanBC ; int8_T
Intersectionifbothdeterminatesarenot0_SubsysRanBC ; int8_T
If1_ActiveSubsystem ; int8_T IfActionSubsystem_SubsysRanBC ; int8_T
Intersectionisinfifintersectionpointisinthewrongdirection_SubsysRanBC ; char
pad_Intersectionisinfifintersectionpointisinthewrongdirection_SubsysRanBC ; }
DW_CoreSubsys_model_AllInOne_ghtp_T ; typedef struct { real_T B_17_0_0 ;
real_T B_17_4_0 [ 768 ] ; real_T B_16_7_0 [ 6 ] ; real_T B_16_8_0 [ 3 ] ;
real_T B_16_9_0 [ 2304 ] ; real_T B_16_10_0 [ 2304 ] ; real_T B_15_5_0 [ 2304
] ; real_T B_8_0_1 [ 768 ] ; real_T B_7_0_1 [ 768 ] ; real_T B_6_3_0 [ 768 ]
; real_T B_4_4_0 [ 768 ] ; B_CoreSubsys_model_AllInOne_bab0_T CoreSubsys_mn2
[ 769 ] ; } B_CoreSubsys_model_AllInOne_T ; typedef struct { int32_T
ForEach_itr ; int32_T ForEach_ivar ; int32_T ForEach_itr_d ; int32_T
ForEach_ivar_g ; int32_T ForEach_itr_h ; int32_T ForEach_ivar_h ; int32_T
ForEach_itr_i ; int32_T ForEach_ivar_gi ; int8_T
Ifwallconsistsofzerosdonotcalculatedistances_ActiveSubsystem ; int8_T
ReturnzerosasDistances_SubsysRanBC ; int8_T CalculateDistances_SubsysRanBC ;
char pad_CalculateDistances_SubsysRanBC [ 5 ] ;
DW_CoreSubsys_model_AllInOne_ghtp_T CoreSubsys_mn2 [ 769 ] ;
DW_CoreSubsys_model_AllInOne_ght_T CoreSubsys_mn [ 769 ] ;
DW_CoreSubsys_model_AllInOne_gh_T CoreSubsys_m [ 769 ] ; }
DW_CoreSubsys_model_AllInOne_T ; typedef struct { real_T B_20_0_0 [ 9 ] ; }
B_Forwallsthataretofartake0asdistancevalue_model_AllInOne_T ; typedef struct
{ int8_T Forwallsthataretofartake0asdistancevalue_SubsysRanBC ; char
pad_Forwallsthataretofartake0asdistancevalue_SubsysRanBC [ 7 ] ; }
DW_Forwallsthataretofartake0asdistancevalue_model_AllInOne_T ; typedef struct
{ B_Forwallsthataretofartake0asdistancevalue_model_AllInOne_T
Forwallsthataretofartake0asdistancevalue ; }
B_CoreSubsys_model_AllInOne_bab0m_T ; typedef struct { int8_T
MathFunction1_DWORK1 ; int8_T
Checkifwallisnotmorethan7metersawayfromthesensorsposition_ActiveSubsystem ;
char
pad_Checkifwallisnotmorethan7metersawayfromthesensorsposition_ActiveSubsystem
[ 6 ] ; DW_Forwallsthataretofartake0asdistancevalue_model_AllInOne_T
Forwallsthataretofartake0asdistancevalue ; }
DW_CoreSubsys_model_AllInOne_ghtpe_T ; typedef struct { int8_T
nobox_SubsysRanBC ; char pad_nobox_SubsysRanBC [ 7 ] ; }
DW_nobox_model_AllInOne_T ; typedef struct { int8_T NoBO_SubsysRanBC ; char
pad_NoBO_SubsysRanBC [ 7 ] ; } DW_NoBO_model_AllInOne_T ; typedef struct {
real_T B_36_0_0 ; } B_BO_model_AllInOne_T ; typedef struct { struct { real_T
modelTStart ; } TransportDelay_RWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay_PWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK ; int8_T
BO_SubsysRanBC ; char pad_BO_SubsysRanBC [ 3 ] ; } DW_BO_model_AllInOne_T ;
typedef struct { real_T B_91_4_0 [ 3 ] ; } B_CoreSubsys_model_AllInOne_ooc_T
; typedef struct { int8_T If_ActiveSubsystem ; int8_T
Intersectionis0ifsensorisintheplane_SubsysRanBC ; int8_T
Intersectionisinfifplaneandsensorareparalell_SubsysRanBC ; int8_T
Intersectionifbothdeterminatesarenot0_SubsysRanBC ; int8_T
If1_ActiveSubsystem ; int8_T IfActionSubsystem_SubsysRanBC ; int8_T
Intersectionisinfifintersectionpointisinthewrongdirection_SubsysRanBC ; char
pad_Intersectionisinfifintersectionpointisinthewrongdirection_SubsysRanBC ; }
DW_CoreSubsys_model_AllInOne_ivz_T ; typedef struct { int8_T Sqrt_DWORK1 ;
char pad_Sqrt_DWORK1 [ 7 ] ; } DW_CoreSubsys_model_AllInOne_ivzok_T ; typedef
struct { int8_T Sqrt_DWORK1 ; char pad_Sqrt_DWORK1 [ 7 ] ; }
DW_CoreSubsys_model_AllInOne_ivzokk_T ; typedef struct { real_T B_100_0_0 ;
real_T B_100_4_0 [ 17 ] ; real_T B_99_6_0 [ 6 ] ; real_T B_99_7_0 [ 51 ] ;
real_T B_99_8_0 [ 51 ] ; real_T B_99_11_0 [ 3 ] ; real_T B_85_0_1 [ 17 ] ;
real_T B_84_0_1 [ 17 ] ; B_CoreSubsys_model_AllInOne_ooc_T CoreSubsys [ 18 ]
; } B_CoreSubsys_model_AllInOne_oo_T ; typedef struct { int32_T ForEach_itr ;
int32_T ForEach_ivar ; int32_T ForEach_itr_l ; int32_T ForEach_ivar_b ;
int32_T ForEach_itr_h ; int32_T ForEach_ivar_h ; int32_T ForEach_itr_k ;
int32_T ForEach_ivar_d ; int8_T
Ifwallconsistsofzerosdonotcalculatedistances_ActiveSubsystem ; int8_T
ReturnzerosasDistances_SubsysRanBC ; int8_T CalculateDistances_SubsysRanBC ;
char pad_CalculateDistances_SubsysRanBC [ 5 ] ;
DW_CoreSubsys_model_AllInOne_ivzokk_T CoreSubsys_nx2 [ 18 ] ;
DW_CoreSubsys_model_AllInOne_ivzok_T CoreSubsys_nx [ 18 ] ;
DW_CoreSubsys_model_AllInOne_ivz_T CoreSubsys [ 18 ] ; }
DW_CoreSubsys_model_AllInOne_iv_T ; typedef struct { real_T B_102_70_0 [ 51 ]
; real_T B_102_72_0 [ 17 ] ; real_T B_101_0_0 [ 9 ] ; real_T B_101_3_0 [ 2125
] ; B_CoreSubsys_model_AllInOne_oo_T CoreSubsys [ 126 ] ; }
B_CoreSubsys_model_AllInOne_o_T ; typedef struct { int32_T ForEach_itr ;
int32_T ForEach_ivar ; int8_T MathFunction1_DWORK1 ; int8_T sqrt_DWORK1 ;
char pad_sqrt_DWORK1 [ 6 ] ; DW_CoreSubsys_model_AllInOne_iv_T CoreSubsys [
126 ] ; } DW_CoreSubsys_model_AllInOne_i_T ; typedef struct {
B_Forwallsthataretofartake0asdistancevalue_model_AllInOne_T
Forwallsthataretofartake0asdistancevalue ; } B_CoreSubsys_model_AllInOne_p_T
; typedef struct { int8_T MathFunction1_DWORK1 ; int8_T
Checkifwallisnotmorethanu2metersawayfromthesensorsposition_ActiveSubsystem ;
char
pad_Checkifwallisnotmorethanu2metersawayfromthesensorsposition_ActiveSubsystem
[ 6 ] ; DW_Forwallsthataretofartake0asdistancevalue_model_AllInOne_T
Forwallsthataretofartake0asdistancevalue ; } DW_CoreSubsys_model_AllInOne_n_T
; typedef struct { real_T B_107_0_0 [ 3 ] ; real_T B_107_3_0 ; real_T
B_107_4_0 [ 3 ] ; real_T B_107_5_0 ; real_T B_107_15_0 [ 3 ] ; real_T
B_107_23_0 [ 3 ] ; real_T B_107_24_0 ; real_T B_107_25_0 ; real_T B_107_26_0
; real_T B_107_27_0 ; real_T B_107_31_0 ; real_T B_107_32_0 ; real_T
B_107_36_0 ; real_T B_107_37_0 ; real_T B_107_45_0 [ 3 ] ; real_T B_107_48_0
; real_T B_107_50_0 ; real_T B_107_52_0 ; real_T B_107_54_0 ; real_T
B_107_56_0 ; real_T B_107_58_0 ; real_T B_107_60_0 ; real_T B_107_62_0 ;
real_T B_107_64_0 ; real_T B_107_66_0 ; real_T B_107_68_0 ; real_T B_107_70_0
; real_T B_107_72_0 ; real_T B_107_74_0 ; real_T B_107_76_0 ; real_T
B_107_78_0 ; real_T B_107_80_0 ; real_T B_107_82_0 ; real_T B_107_84_0 ;
real_T B_107_86_0 ; real_T B_107_88_0 ; real_T B_107_90_0 ; real_T B_107_92_0
; real_T B_107_94_0 ; real_T B_107_95_0 [ 6 ] ; real_T B_107_97_0 ; real_T
B_107_98_0 ; real_T B_107_102_0 ; real_T B_107_107_0 ; real_T B_107_114_0 ;
real_T B_107_115_0 ; real_T B_107_116_0 ; real_T B_107_117_0 ; real_T
B_107_118_0 ; real_T B_107_125_0 ; real_T B_107_126_0 ; real_T B_107_127_0 ;
real_T B_107_128_0 ; real_T B_107_135_0 ; real_T B_107_136_0 ; real_T
B_107_137_0 ; real_T B_107_140_0 ; real_T B_107_143_0 [ 3 ] ; real_T
B_107_155_0 [ 9 ] ; real_T B_107_157_0 [ 3 ] ; real_T B_107_159_0 [ 3 ] ;
real_T B_107_162_0 ; real_T B_107_163_0 ; real_T B_107_164_0 ; real_T
B_107_165_0 ; real_T B_107_166_0 [ 4 ] ; real_T B_107_169_0 [ 963 ] ; real_T
B_107_174_0 ; real_T B_107_175_0 [ 54 ] ; real_T B_107_182_0 ; real_T
B_107_183_0 [ 54 ] ; real_T B_107_190_0 ; real_T B_107_191_0 [ 54 ] ; real_T
B_107_195_0 [ 54 ] ; real_T B_107_196_0 [ 54 ] ; real_T B_107_197_0 [ 54 ] ;
real_T B_107_199_0 [ 1125 ] ; real_T B_107_209_0 [ 136 ] ; real_T B_107_211_0
[ 17 ] ; real_T B_107_212_0 [ 17 ] ; real_T B_107_213_0 [ 17 ] ; real_T
B_107_214_0 [ 17 ] ; real_T B_107_215_0 [ 17 ] ; real_T B_107_216_0 [ 17 ] ;
real_T B_107_217_0 [ 17 ] ; real_T B_107_218_0 [ 17 ] ; real_T B_107_219_0 ;
real_T B_107_226_0 ; real_T B_107_227_0 ; real_T B_107_231_0 ; real_T
B_107_232_0 ; real_T B_107_236_0 ; real_T B_107_237_0 ; real_T B_107_241_0 ;
real_T B_107_242_0 ; real_T B_107_249_0 ; real_T B_107_253_0 ; real_T
B_107_253_1 ; real_T B_107_253_2 ; real_T B_107_253_3 ; real_T B_107_253_4 ;
real_T B_107_253_5 [ 20 ] ; real_T B_107_253_6 ; real_T B_107_253_7 ; real_T
B_107_253_8 ; real_T B_107_253_9 ; real_T B_107_260_0 [ 4 ] ; real_T
B_107_261_0 ; real_T B_107_262_0 ; real_T B_107_263_0 [ 4 ] ; real_T
B_107_292_0 ; real_T B_107_293_0 ; real_T B_107_297_0 ; real_T B_107_298_0 ;
real_T B_107_299_0 ; real_T B_107_300_0 ; real_T B_107_303_0 ; real_T
B_107_309_0 ; real_T B_107_310_0 ; real_T B_107_313_0 ; real_T B_107_321_0 ;
real_T B_107_326_0 ; real_T B_107_328_0 ; real_T B_107_329_0 ; real_T
B_107_330_0 ; real_T B_107_331_0 [ 9 ] ; real_T B_107_333_0 [ 9 ] ; real_T
B_107_344_0 [ 9 ] ; real_T B_107_345_0 [ 3 ] ; real_T B_107_347_0 ; real_T
B_107_349_0 ; real_T B_107_350_0 ; real_T B_107_351_0 ; real_T B_107_352_0 ;
real_T B_107_353_0 ; real_T B_107_354_0 ; real_T B_107_355_0 ; real_T
B_107_356_0 ; real_T B_107_357_0 ; real_T B_107_362_0 ; real_T B_107_363_0 ;
real_T B_107_368_0 ; real_T B_107_369_0 ; real_T B_107_374_0 ; real_T
B_107_375_0 ; real_T B_107_380_0 ; real_T B_107_381_0 ; real_T B_107_386_0 ;
real_T B_107_387_0 ; real_T B_107_392_0 ; real_T B_107_393_0 ; real_T
B_107_398_0 ; real_T B_107_399_0 ; real_T B_107_404_0 ; real_T B_107_405_0 ;
real_T B_107_410_0 ; real_T B_107_411_0 ; real_T B_107_416_0 ; real_T
B_107_417_0 ; real_T B_107_422_0 ; real_T B_107_423_0 ; real_T B_107_428_0 ;
real_T B_107_429_0 ; real_T B_107_434_0 ; real_T B_107_435_0 ; real_T
B_107_440_0 ; real_T B_107_441_0 ; real_T B_107_446_0 ; real_T B_107_447_0 ;
real_T B_107_452_0 ; real_T B_107_453_0 ; real_T B_107_458_0 ; real_T
B_107_459_0 ; real_T B_106_3_0 [ 1125 ] ; real_T B_103_3_0 [ 136 ] ; real_T
B_33_2_0 [ 6 ] ; real_T B_31_2_0 [ 6 ] ; real_T B_29_2_0 [ 6 ] ; real_T
B_27_0_0 ; real_T B_27_1_0 ; real_T B_27_4_0 ; real_T B_27_5_0 ; real_T
B_23_1_0 ; real_T B_22_3_0 [ 1125 ] ; real_T B_19_5_0 [ 2304 ] ; real_T
B_19_10_0 [ 768 ] ; real_T B_18_0_0 [ 9 ] ; real_T B_18_3_0 [ 288000 ] ;
real_T B_18_4_0 [ 96000 ] ; real_T B_18_5_0 [ 96000 ] ; real_T B_18_6_0 [
96000 ] ; real_T B_107_96_0 [ 3 ] ; real_T B_107_106_0 [ 3 ] ; real_T
B_107_173_0 [ 3 ] ; real_T B_107_181_0 [ 2 ] ; real_T B_107_189_0 [ 2 ] ;
real_T B_107_210_0 [ 136 ] ; real_T B_107_267_0 [ 768 ] ; real_T B_33_0_0 [ 6
] ; real_T B_31_0_0 [ 6 ] ; real_T B_29_0_0 [ 6 ] ; real_T B_19_2_0 [ 2304 ]
; real_T B_19_4_0 [ 2304 ] ; real_T B_19_12_0 [ 2 ] ; real_T B_19_18_0 [ 3 ]
; real_T B_19_26_0 [ 2304 ] ; real_T B_19_96_0 [ 9 ] ; real_T B_107_314_0 ;
real_T B_19_28_0 [ 3 ] ; real_T B_19_24_0 ; real_T B_107_325_0 ; real32_T
B_107_250_0 [ 768 ] ; real32_T B_107_252_0 [ 768 ] ; uint32_T B_107_167_0 [ 8
] ; boolean_T B_107_306_0 ; boolean_T B_107_307_0 ; char pad_B_107_307_0 [ 6
] ; B_CoreSubsys_model_AllInOne_p_T CoreSubsys_n1 [ 126 ] ;
B_CoreSubsys_model_AllInOne_o_T CoreSubsys_n [ 9 ] ; B_BO_model_AllInOne_T
BO_ku ; B_BO_model_AllInOne_T BO_no ; B_BO_model_AllInOne_T BO_cr ;
B_BO_model_AllInOne_T BO_k ; B_BO_model_AllInOne_T BO_db ;
B_BO_model_AllInOne_T BO_nh ; B_BO_model_AllInOne_T BO_l ;
B_BO_model_AllInOne_T BO_c ; B_BO_model_AllInOne_T BO_d ;
B_BO_model_AllInOne_T BO_j ; B_BO_model_AllInOne_T BO_e ;
B_BO_model_AllInOne_T BO_h ; B_BO_model_AllInOne_T BO_iu ;
B_BO_model_AllInOne_T BO_af ; B_BO_model_AllInOne_T BO_i ;
B_BO_model_AllInOne_T BO_a ; B_BO_model_AllInOne_T BO_n ;
B_BO_model_AllInOne_T BO_o ; B_BO_model_AllInOne_T BO_g ;
B_BO_model_AllInOne_T BO_p ; B_BO_model_AllInOne_T BO_mz ;
B_BO_model_AllInOne_T BO_eh ; B_BO_model_AllInOne_T BO_m ;
B_BO_model_AllInOne_T BO ; B_CoreSubsys_model_AllInOne_bab0m_T CoreSubsys_m [
126 ] ; B_CoreSubsys_model_AllInOne_T CoreSubsys [ 126 ] ; }
B_model_AllInOne_T ; typedef struct { real_T UnitDelay1_DSTATE ; real_T
UnitDelay3_DSTATE ; real_T UnitDelay2_DSTATE ; real_T UnitDelay_DSTATE ;
real_T NextOutput ; real_T NextOutput_a ; real_T NextOutput_g ; real_T
NextOutput_f ; real_T NextOutput_i ; real_T NextOutput_iq ; real_T
NextOutput_e ; real_T NextOutput_k ; real_T NextOutput_ka ; real_T
NextOutput_a1 ; real_T NextOutput_kr ; real_T NextOutput_c ; real_T
NextOutput_o ; real_T NextOutput_b ; real_T NextOutput_l ; real_T
NextOutput_e0 ; real_T NextOutput_b5 ; real_T NextOutput_ld ; real_T
NextOutput_p ; real_T NextOutput_aj ; real_T NextOutput_bv ; real_T
NextOutput_m ; real_T NextOutput_c0 ; real_T NextOutput_gm ; real_T
controltask_DWORK1 ; real_T NextOutput_mt ; real_T NextOutput_op ; real_T
Product2_DWORK1 [ 9 ] ; real_T Product2_DWORK3 [ 9 ] ; real_T Product2_DWORK4
[ 9 ] ; real_T Product2_DWORK5 [ 9 ] ; struct { real_T modelTStart ; }
TransportDelay_RWORK ; struct { real_T modelTStart ; } TransportDelay1_RWORK
; struct { real_T modelTStart ; } TransportDelay_RWORK_l ; struct { real_T
modelTStart ; } TransportDelay_RWORK_d ; struct { real_T modelTStart ; }
TransportDelay_RWORK_k ; struct { void * TUbufferPtrs [ 6 ] ; }
TransportDelay_PWORK ; struct { void * LoggedData ; } ACCZsingle_PWORK ;
struct { void * LoggedData ; } AltitudeControlIntermediateValues_PWORK ;
struct { void * LoggedData ; } Altitudesingle_PWORK ; struct { void *
LoggedData ; } Commands_PWORK ; struct { void * LoggedData ; } Gas_PWORK ;
void * DSimulation_PWORK [ 12 ] ; struct { void * LoggedData ; } Scope_PWORK
; struct { void * LoggedData ; } angularvelo_PWORK ; struct { void *
LoggedData ; } speedXsingle_PWORK ; struct { void * LoggedData ; }
speedYsingle_PWORK ; struct { void * LoggedData ; } speedZsingle_PWORK ;
struct { void * LoggedData ; } accmeasured_PWORK ; struct { void * LoggedData
; } accmeasured1_PWORK ; struct { void * LoggedData ; } acc_real1_PWORK ;
struct { void * LoggedData ; } Position_PWORK ; struct { void * LoggedData ;
} X_PWORK ; struct { void * LoggedData ; } Y_PWORK ; struct { void *
LoggedData ; } Yaw_PWORK ; struct { void * LoggedData ; } Zco_PWORK ; struct
{ void * LoggedData ; } adcvalues_PWORK ; struct { void * LoggedData ; }
angles_PWORK ; struct { void * LoggedData ; } angularvelos_PWORK ; struct {
void * LoggedData ; } Scope_PWORK_d ; struct { void * LoggedData ; }
Scope1_PWORK ; struct { void * LoggedData ; } IR150_PWORK ; struct { void *
LoggedData ; } Noise_PWORK ; struct { void * LoggedData ; } position_PWORK ;
struct { void * LoggedData ; } positionwithnoise_PWORK ; struct { void *
LoggedData ; } Noise_PWORK_k ; struct { void * LoggedData ; }
positionwithnoise_PWORK_m ; struct { void * TUbufferPtrs [ 6 ] ; }
TransportDelay1_PWORK ; struct { void * LoggedData ; } Force_PWORK ; struct {
void * LoggedData ; } Force1_PWORK ; struct { void * LoggedData ; }
Scope_PWORK_k ; struct { void * TUbufferPtrs [ 12 ] ; }
TransportDelay_PWORK_p ; struct { void * TUbufferPtrs [ 12 ] ; }
TransportDelay_PWORK_n ; struct { void * TUbufferPtrs [ 12 ] ; }
TransportDelay_PWORK_o ; struct { void * LoggedData ; } D_PWORK ; struct {
void * LoggedData ; } Distaces_PWORK ; struct { void * LoggedData ; }
Dt_PWORK ; struct { void * LoggedData ; } Gas1_PWORK ; struct { void *
LoggedData ; } Gas2_PWORK ; struct { void * LoggedData ; } Gas3_PWORK ;
struct { void * LoggedData ; } Intersections_PWORK ; struct { void *
LoggedData ; } Scope_PWORK_n ; struct { void * LoggedData ; } Scope1_PWORK_l
; struct { void * LoggedData ; } Scope2_PWORK ; int32_T Product2_DWORK2 [ 3 ]
; int32_T ForEach_itr ; int32_T ForEach_ivar ; int32_T ForEach_itr_c ;
int32_T ForEach_ivar_h ; int32_T ForEach_itr_g ; int32_T ForEach_ivar_hk ;
int32_T ForEach_itr_b ; int32_T ForEach_ivar_k ; uint32_T RandSeed ; uint32_T
RandSeed_f ; uint32_T RandSeed_c ; uint32_T RandSeed_i ; uint32_T RandSeed_o
; uint32_T RandSeed_n ; uint32_T RandSeed_k ; uint32_T RandSeed_b ; uint32_T
RandSeed_cr ; uint32_T RandSeed_g ; uint32_T RandSeed_h ; uint32_T
RandSeed_nr ; uint32_T RandSeed_l ; uint32_T RandSeed_fb ; uint32_T
RandSeed_p ; uint32_T RandSeed_cm ; uint32_T RandSeed_og ; uint32_T
RandSeed_lr ; uint32_T RandSeed_ct ; uint32_T RandSeed_hl ; uint32_T
RandSeed_n1 ; uint32_T RandSeed_in ; uint32_T RandSeed_of ; uint32_T
RandSeed_d ; uint32_T RandSeed_o1 ; uint32_T RandSeed_bi ; struct { int_T
Tail [ 3 ] ; int_T Head [ 3 ] ; int_T Last [ 3 ] ; int_T CircularBufSize [ 3
] ; int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct { int_T Tail [ 3 ]
; int_T Head [ 3 ] ; int_T Last [ 3 ] ; int_T CircularBufSize [ 3 ] ; int_T
MaxNewBufSize ; } TransportDelay1_IWORK ; struct { int_T Tail [ 6 ] ; int_T
Head [ 6 ] ; int_T Last [ 6 ] ; int_T CircularBufSize [ 6 ] ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_j ; struct { int_T Tail [ 6 ] ; int_T
Head [ 6 ] ; int_T Last [ 6 ] ; int_T CircularBufSize [ 6 ] ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_a ; struct { int_T Tail [ 6 ] ; int_T
Head [ 6 ] ; int_T Last [ 6 ] ; int_T CircularBufSize [ 6 ] ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_e ; int_T Saturation_MODE ; int_T
Saturation_MODE_c ; int_T Saturation_MODE_n ; int_T DeadZone_MODE ; int_T
SignPreSat_MODE ; int_T SignPreIntegrator_MODE ; int8_T If_ActiveSubsystem ;
int8_T passthrough_SubsysRanBC ; int8_T gtezeroonly_SubsysRanBC ; int8_T
If_ActiveSubsystem_b ; int8_T If_ActiveSubsystem_m ; int8_T
If_ActiveSubsystem_i ; int8_T If_ActiveSubsystem_m5 ; int8_T
timedbox_SubsysRanBC ; int8_T If_ActiveSubsystem_j ; int8_T
timedbox_SubsysRanBC_a ; int8_T If_ActiveSubsystem_g ; int8_T
timedbox_SubsysRanBC_g ; int8_T Sqrt_DWORK1 ; int8_T If_ActiveSubsystem_p ;
int8_T If_ActiveSubsystem_bo ; int8_T If_ActiveSubsystem_ik ; int8_T
If_ActiveSubsystem_pt ; int8_T If_ActiveSubsystem_e ; int8_T
If_ActiveSubsystem_f ; int8_T If_ActiveSubsystem_jy ; int8_T
If_ActiveSubsystem_e4 ; int8_T If_ActiveSubsystem_pw ; int8_T
If_ActiveSubsystem_ju ; int8_T If_ActiveSubsystem_ed ; int8_T
If_ActiveSubsystem_a ; int8_T If_ActiveSubsystem_h ; int8_T
If_ActiveSubsystem_k ; int8_T If_ActiveSubsystem_ko ; int8_T
If_ActiveSubsystem_o ; int8_T If_ActiveSubsystem_mi ; int8_T
If_ActiveSubsystem_d ; int8_T If_ActiveSubsystem_ap ; int8_T
If_ActiveSubsystem_gj ; int8_T If_ActiveSubsystem_kp ; int8_T
If2_ActiveSubsystem ; int8_T passthroughA1_SubsysRanBC ; int8_T
zeroFn_SubsysRanBC ; int8_T MathFunction1_DWORK1 ; int8_T sqrt_DWORK1 ;
boolean_T NotEqual_Mode ; boolean_T Memory_PreviousInput ; char
pad_Memory_PreviousInput [ 7 ] ; DW_CoreSubsys_model_AllInOne_n_T
CoreSubsys_n1 [ 126 ] ; DW_CoreSubsys_model_AllInOne_i_T CoreSubsys_n [ 9 ] ;
DW_BO_model_AllInOne_T BO_ku ; DW_NoBO_model_AllInOne_T NoBO_eh ;
DW_BO_model_AllInOne_T BO_no ; DW_NoBO_model_AllInOne_T NoBO_jp ;
DW_BO_model_AllInOne_T BO_cr ; DW_NoBO_model_AllInOne_T NoBO_j ;
DW_BO_model_AllInOne_T BO_k ; DW_NoBO_model_AllInOne_T NoBO_jb ;
DW_BO_model_AllInOne_T BO_db ; DW_NoBO_model_AllInOne_T NoBO_d ;
DW_BO_model_AllInOne_T BO_nh ; DW_NoBO_model_AllInOne_T NoBO_f ;
DW_BO_model_AllInOne_T BO_l ; DW_NoBO_model_AllInOne_T NoBO_k ;
DW_BO_model_AllInOne_T BO_c ; DW_NoBO_model_AllInOne_T NoBO_la ;
DW_BO_model_AllInOne_T BO_d ; DW_NoBO_model_AllInOne_T NoBO_nj ;
DW_BO_model_AllInOne_T BO_j ; DW_NoBO_model_AllInOne_T NoBO_h ;
DW_BO_model_AllInOne_T BO_e ; DW_NoBO_model_AllInOne_T NoBO_g ;
DW_BO_model_AllInOne_T BO_h ; DW_NoBO_model_AllInOne_T NoBO_b ;
DW_BO_model_AllInOne_T BO_iu ; DW_NoBO_model_AllInOne_T NoBO_ma ;
DW_BO_model_AllInOne_T BO_af ; DW_NoBO_model_AllInOne_T NoBO_ek ;
DW_BO_model_AllInOne_T BO_i ; DW_NoBO_model_AllInOne_T NoBO_m ;
DW_BO_model_AllInOne_T BO_a ; DW_NoBO_model_AllInOne_T NoBO_l ;
DW_BO_model_AllInOne_T BO_n ; DW_NoBO_model_AllInOne_T NoBO_le ;
DW_BO_model_AllInOne_T BO_o ; DW_NoBO_model_AllInOne_T NoBO_e ;
DW_BO_model_AllInOne_T BO_g ; DW_NoBO_model_AllInOne_T NoBO_o ;
DW_BO_model_AllInOne_T BO_p ; DW_NoBO_model_AllInOne_T NoBO_n ;
DW_BO_model_AllInOne_T BO_mz ; DW_NoBO_model_AllInOne_T NoBO_a ;
DW_BO_model_AllInOne_T BO_eh ; DW_NoBO_model_AllInOne_T NoBO_c ;
DW_BO_model_AllInOne_T BO_m ; DW_NoBO_model_AllInOne_T NoBO_g4 ;
DW_BO_model_AllInOne_T BO ; DW_NoBO_model_AllInOne_T NoBO ;
DW_nobox_model_AllInOne_T nobox_a ; DW_nobox_model_AllInOne_T nobox_j ;
DW_nobox_model_AllInOne_T nobox ; DW_CoreSubsys_model_AllInOne_ghtpe_T
CoreSubsys_m [ 126 ] ; DW_CoreSubsys_model_AllInOne_T CoreSubsys [ 126 ] ; }
DW_model_AllInOne_T ; typedef struct { real_T xeyeze_CSTATE [ 3 ] ; real_T
ubvbwb_CSTATE [ 3 ] ; real_T pqr_CSTATE [ 3 ] ; real_T phithetapsi_CSTATE [ 3
] ; real_T Integrator_CSTATE ; real_T Filter_CSTATE ; real_T
Integrator_CSTATE_j ; real_T Filter_CSTATE_k ; real_T Integrator_CSTATE_a ;
real_T Filter_CSTATE_e ; real_T Integrator_CSTATE_h ; real_T Filter_CSTATE_n
; real_T Integrator_CSTATE_k ; real_T Integrator1_CSTATE ; real_T
Integrator2_CSTATE ; } X_model_AllInOne_T ; typedef struct { real_T
xeyeze_CSTATE [ 3 ] ; real_T ubvbwb_CSTATE [ 3 ] ; real_T pqr_CSTATE [ 3 ] ;
real_T phithetapsi_CSTATE [ 3 ] ; real_T Integrator_CSTATE ; real_T
Filter_CSTATE ; real_T Integrator_CSTATE_j ; real_T Filter_CSTATE_k ; real_T
Integrator_CSTATE_a ; real_T Filter_CSTATE_e ; real_T Integrator_CSTATE_h ;
real_T Filter_CSTATE_n ; real_T Integrator_CSTATE_k ; real_T
Integrator1_CSTATE ; real_T Integrator2_CSTATE ; } XDot_model_AllInOne_T ;
typedef struct { boolean_T xeyeze_CSTATE [ 3 ] ; boolean_T ubvbwb_CSTATE [ 3
] ; boolean_T pqr_CSTATE [ 3 ] ; boolean_T phithetapsi_CSTATE [ 3 ] ;
boolean_T Integrator_CSTATE ; boolean_T Filter_CSTATE ; boolean_T
Integrator_CSTATE_j ; boolean_T Filter_CSTATE_k ; boolean_T
Integrator_CSTATE_a ; boolean_T Filter_CSTATE_e ; boolean_T
Integrator_CSTATE_h ; boolean_T Filter_CSTATE_n ; boolean_T
Integrator_CSTATE_k ; boolean_T Integrator1_CSTATE ; boolean_T
Integrator2_CSTATE ; } XDis_model_AllInOne_T ; typedef struct { real_T
xeyeze_CSTATE [ 3 ] ; real_T ubvbwb_CSTATE [ 3 ] ; real_T pqr_CSTATE [ 3 ] ;
real_T phithetapsi_CSTATE [ 3 ] ; real_T Integrator_CSTATE ; real_T
Filter_CSTATE ; real_T Integrator_CSTATE_j ; real_T Filter_CSTATE_k ; real_T
Integrator_CSTATE_a ; real_T Filter_CSTATE_e ; real_T Integrator_CSTATE_h ;
real_T Filter_CSTATE_n ; real_T Integrator_CSTATE_k ; real_T
Integrator1_CSTATE ; real_T Integrator2_CSTATE ; }
CStateAbsTol_model_AllInOne_T ; typedef struct { real_T If_IfInput_ZC ;
real_T Saturation_UprLim_ZC ; real_T Saturation_LwrLim_ZC ; real_T
Saturation_UprLim_ZC_j ; real_T Saturation_LwrLim_ZC_n ; real_T
Saturation_UprLim_ZC_f ; real_T Saturation_LwrLim_ZC_d ; real_T
DeadZone_LwrReg_ZC ; real_T DeadZone_UprReg_ZC ; real_T
NotEqual_RelopInput_ZC ; real_T SignPreSat_Input_ZC ; real_T
SignPreIntegrator_Input_ZC ; real_T If2_IfInput_ZC ; } ZCV_model_AllInOne_T ;
typedef struct { ZCSigState If_IfInput_ZCE ; ZCSigState Saturation_UprLim_ZCE
; ZCSigState Saturation_LwrLim_ZCE ; ZCSigState Saturation_UprLim_ZCE_c ;
ZCSigState Saturation_LwrLim_ZCE_g ; ZCSigState Saturation_UprLim_ZCE_f ;
ZCSigState Saturation_LwrLim_ZCE_l ; ZCSigState DeadZone_LwrReg_ZCE ;
ZCSigState DeadZone_UprReg_ZCE ; ZCSigState NotEqual_RelopInput_ZCE ;
ZCSigState SignPreSat_Input_ZCE ; ZCSigState SignPreIntegrator_Input_ZCE ;
ZCSigState If2_IfInput_ZCE ; } PrevZCX_model_AllInOne_T ; typedef struct {
const real_T B_1_2_0 ; const real_T B_1_5_0 ; const real_T B_1_10_0 ; const
real_T B_1_13_0 ; } ConstB_CoreSubsys_model_AllInOne_g_T ; typedef struct {
ConstB_CoreSubsys_model_AllInOne_g_T CoreSubsys ; }
ConstB_CoreSubsys_model_AllInOne_T ; typedef struct { const real_T B_93_2_0 ;
const real_T B_93_5_0 ; const real_T B_93_10_0 ; const real_T B_93_13_0 ; }
ConstB_CoreSubsys_model_AllInOne_dmvy_T ; typedef struct {
ConstB_CoreSubsys_model_AllInOne_dmvy_T CoreSubsys_n ; }
ConstB_CoreSubsys_model_AllInOne_dm_T ; typedef struct {
ConstB_CoreSubsys_model_AllInOne_dm_T CoreSubsys ; }
ConstB_CoreSubsys_model_AllInOne_d_T ; typedef struct { const real_T
B_107_308_0 ; ConstB_CoreSubsys_model_AllInOne_d_T CoreSubsys_n ;
ConstB_CoreSubsys_model_AllInOne_T CoreSubsys ; } ConstB_model_AllInOne_T ;
#define model_AllInOne_rtC(S) ((ConstB_model_AllInOne_T *) _ssGetConstBlockIO(S))
struct P_CoreSubsys_model_AllInOne_k_T_ { real_T P_0 ; real_T P_1 ; real_T
P_2 ; real_T P_3 ; } ; struct P_CoreSubsys_model_AllInOne_kf_T_ { real_T P_0
; real_T P_1 ; } ; struct P_CoreSubsys_model_AllInOne_kfm0_T_ { real_T P_0 [
3 ] ; real_T P_1 [ 3 ] ; real_T P_2 [ 3 ] ; real_T P_3 [ 3 ] ; real_T P_4 [ 3
] ; real_T P_5 [ 3 ] ; real_T P_6 [ 3 ] ; real_T P_8 [ 3 ] ; } ; struct
P_CoreSubsys_model_AllInOne_T_ { real_T P_0 [ 768 ] ; real_T P_1 [ 768 ] ;
real_T P_2 ; real_T P_3 ; real_T P_4 [ 768 ] ;
P_CoreSubsys_model_AllInOne_kfm0_T CoreSubsys_mn2 ;
P_CoreSubsys_model_AllInOne_kf_T CoreSubsys_m ;
P_CoreSubsys_model_AllInOne_k_T CoreSubsys ; } ; struct
P_CoreSubsys_model_AllInOne_kfm0i_T_ { real_T P_0 ; real_T P_1 ; } ; struct
P_BO_model_AllInOne_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; } ; struct
P_CoreSubsys_model_AllInOne_min_T_ { real_T P_0 [ 3 ] ; real_T P_1 [ 3 ] ;
real_T P_2 [ 3 ] ; real_T P_3 [ 3 ] ; real_T P_4 [ 3 ] ; real_T P_5 [ 3 ] ;
real_T P_6 [ 3 ] ; real_T P_8 [ 3 ] ; } ; struct
P_CoreSubsys_model_AllInOne_minl_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ;
real_T P_3 ; } ; struct P_CoreSubsys_model_AllInOne_minlgp_T_ { real_T P_0 ;
} ; struct P_CoreSubsys_model_AllInOne_mi_T_ { real_T P_0 [ 17 ] ; real_T P_1
[ 17 ] ; real_T P_2 ; real_T P_3 ; real_T P_4 [ 17 ] ;
P_CoreSubsys_model_AllInOne_minlgp_T CoreSubsys_nx2 ;
P_CoreSubsys_model_AllInOne_minl_T CoreSubsys_n ;
P_CoreSubsys_model_AllInOne_min_T CoreSubsys ; } ; struct
P_CoreSubsys_model_AllInOne_m_T_ { real_T P_0 [ 3 ] ; real_T P_1 ; real_T P_2
; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8
; real_T P_9 ; P_CoreSubsys_model_AllInOne_mi_T CoreSubsys ; } ; struct
P_CoreSubsys_model_AllInOne_f_T_ { real_T P_0 ; real_T P_1 ; } ; struct
P_model_AllInOne_T_ { real_T P_0 [ 2304 ] ; real_T P_1 [ 9 ] ; real_T P_2 ;
real_T P_3 [ 2 ] ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T
P_8 ; real_T P_9 [ 3 ] ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T
P_13 ; real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ;
real_T P_19 ; real_T P_20 [ 18 ] ; real_T P_21 ; real_T P_22 ; real_T P_23 ;
real_T P_24 ; real_T P_25 ; real_T P_26 ; real_T P_27 [ 6 ] ; real_T P_28 ;
real_T P_29 ; real_T P_30 [ 6 ] ; real_T P_31 ; real_T P_32 ; real_T P_33 [ 6
] ; real_T P_34 ; real_T P_35 ; real_T P_36 ; real_T P_37 ; real_T P_38 [ 3 ]
; real_T P_39 ; real_T P_40 [ 3 ] ; real_T P_41 [ 3 ] ; real_T P_42 ; real_T
P_43 ; real_T P_44 ; real_T P_45 ; real_T P_46 ; real_T P_47 ; real_T P_48 ;
real_T P_49 ; real_T P_50 [ 3 ] ; real_T P_51 ; real_T P_52 ; real_T P_53 ;
real_T P_54 ; real_T P_55 ; real_T P_56 ; real_T P_57 ; real_T P_58 ; real_T
P_59 ; real_T P_60 ; real_T P_61 ; real_T P_62 ; real_T P_63 ; real_T P_64 ;
real_T P_65 ; real_T P_66 ; real_T P_67 ; real_T P_68 ; real_T P_69 ; real_T
P_70 ; real_T P_71 ; real_T P_72 ; real_T P_73 ; real_T P_74 ; real_T P_75 ;
real_T P_76 ; real_T P_77 ; real_T P_78 ; real_T P_79 ; real_T P_80 ; real_T
P_81 ; real_T P_82 ; real_T P_83 ; real_T P_84 ; real_T P_85 ; real_T P_86 ;
real_T P_87 ; real_T P_88 ; real_T P_89 ; real_T P_90 ; real_T P_91 ; real_T
P_92 ; real_T P_93 ; real_T P_94 ; real_T P_95 ; real_T P_96 ; real_T P_97 ;
real_T P_98 ; real_T P_99 ; real_T P_100 ; real_T P_101 ; real_T P_102 ;
real_T P_103 ; real_T P_104 ; real_T P_105 ; real_T P_106 ; real_T P_107 ;
real_T P_108 ; real_T P_109 ; real_T P_110 ; real_T P_111 ; real_T P_112 ;
real_T P_113 ; real_T P_114 ; real_T P_115 ; real_T P_116 ; real_T P_117 ;
real_T P_118 ; real_T P_119 ; real_T P_120 ; real_T P_121 ; real_T P_122 ;
real_T P_123 ; real_T P_124 ; real_T P_125 ; real_T P_126 ; real_T P_127 ;
real_T P_128 ; real_T P_129 ; real_T P_130 ; real_T P_131 ; real_T P_132 ;
real_T P_133 ; real_T P_134 ; real_T P_135 ; real_T P_136 ; real_T P_137 ;
real_T P_138 ; real_T P_139 ; real_T P_140 ; real_T P_141 ; real_T P_142 ;
real_T P_143 ; real_T P_144 ; real_T P_145 ; real_T P_146 ; real_T P_147 ;
real_T P_148 ; real_T P_149 ; real_T P_150 ; real_T P_151 ; real_T P_152 ;
real_T P_153 ; real_T P_154 ; real_T P_155 ; real_T P_156 ; real_T P_157 ;
real_T P_158 ; real_T P_159 ; real_T P_160 ; real_T P_161 ; real_T P_162 ;
real_T P_163 ; real_T P_164 ; real_T P_165 ; real_T P_166 ; real_T P_167 ;
real_T P_168 ; real_T P_169 ; real_T P_170 ; real_T P_171 ; real_T P_172 ;
real_T P_173 ; real_T P_174 ; real_T P_175 ; real_T P_176 ; real_T P_177 ;
real_T P_178 ; real_T P_179 ; real_T P_180 [ 48 ] ; real_T P_181 [ 963 ] ;
real_T P_182 ; real_T P_183 [ 2 ] ; real_T P_184 [ 54 ] ; real_T P_185 ;
real_T P_186 [ 54 ] ; real_T P_187 ; real_T P_188 [ 54 ] ; real_T P_189 [ 54
] ; real_T P_190 [ 54 ] ; real_T P_191 [ 54 ] ; real_T P_192 [ 51 ] ; real_T
P_193 [ 2 ] ; real_T P_194 ; real_T P_195 ; real_T P_196 ; real_T P_197 ;
real_T P_198 ; real_T P_199 ; real_T P_200 ; real_T P_201 [ 6 ] ; real_T
P_202 ; real_T P_203 ; real_T P_204 ; real_T P_205 ; real_T P_206 ; real_T
P_207 ; real_T P_208 [ 3 ] ; real_T P_209 ; real_T P_210 ; real_T P_211 ;
real_T P_212 ; real_T P_213 ; real_T P_214 ; real_T P_215 ; real_T P_216 ;
real_T P_217 ; real_T P_218 ; real_T P_219 ; real_T P_220 ; real_T P_221 ;
real_T P_222 ; real_T P_223 ; real_T P_224 ; real_T P_225 ; real_T P_226 ;
real_T P_227 ; real_T P_228 ; real_T P_229 ; real_T P_230 ; real_T P_231 ;
real_T P_232 ; real_T P_233 ; real_T P_234 ; real_T P_235 ; real_T P_236 ;
real_T P_237 ; real_T P_238 ; real_T P_239 ; real_T P_240 ; real_T P_241 ;
real_T P_242 ; real_T P_243 ; real_T P_244 ; real_T P_245 ; real_T P_246 ;
real_T P_247 ; real_T P_248 ; real_T P_249 ; real_T P_250 ; real_T P_251 ;
real_T P_252 ; real_T P_253 ; real_T P_254 ; real_T P_255 ; real_T P_256 ;
real_T P_257 ; real_T P_258 ; real_T P_259 ; real_T P_260 ; real_T P_261 ;
real_T P_262 ; real_T P_263 ; real_T P_264 ; real_T P_265 ; real_T P_266 ;
real_T P_267 ; real_T P_268 ; real_T P_269 ; real_T P_270 ; real_T P_271 ;
real32_T P_272 ; boolean_T P_273 ; char pad_P_273 [ 3 ] ;
P_CoreSubsys_model_AllInOne_f_T CoreSubsys_n1 ;
P_CoreSubsys_model_AllInOne_m_T CoreSubsys_n ; P_BO_model_AllInOne_T BO_ku ;
P_BO_model_AllInOne_T BO_no ; P_BO_model_AllInOne_T BO_cr ;
P_BO_model_AllInOne_T BO_k ; P_BO_model_AllInOne_T BO_db ;
P_BO_model_AllInOne_T BO_nh ; P_BO_model_AllInOne_T BO_l ;
P_BO_model_AllInOne_T BO_c ; P_BO_model_AllInOne_T BO_d ;
P_BO_model_AllInOne_T BO_j ; P_BO_model_AllInOne_T BO_e ;
P_BO_model_AllInOne_T BO_h ; P_BO_model_AllInOne_T BO_iu ;
P_BO_model_AllInOne_T BO_af ; P_BO_model_AllInOne_T BO_i ;
P_BO_model_AllInOne_T BO_a ; P_BO_model_AllInOne_T BO_n ;
P_BO_model_AllInOne_T BO_o ; P_BO_model_AllInOne_T BO_g ;
P_BO_model_AllInOne_T BO_p ; P_BO_model_AllInOne_T BO_mz ;
P_BO_model_AllInOne_T BO_eh ; P_BO_model_AllInOne_T BO_m ;
P_BO_model_AllInOne_T BO ; P_CoreSubsys_model_AllInOne_kfm0i_T CoreSubsys_m ;
P_CoreSubsys_model_AllInOne_T CoreSubsys ; } ; extern P_model_AllInOne_T
model_AllInOne_rtDefaultP ; extern const ConstB_model_AllInOne_T
model_AllInOne_rtInvariant ;
#endif
