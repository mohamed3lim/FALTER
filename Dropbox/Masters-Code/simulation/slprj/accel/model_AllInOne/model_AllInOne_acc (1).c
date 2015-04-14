#include "__cf_model_AllInOne.h"
#include <math.h>
#include "model_AllInOne_acc.h"
#include "model_AllInOne_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr
, int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay ,
real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr , boolean_T
isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr ) { int_T
testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf =
* tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail <
( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] )
&& ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T *
tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024
; if ( newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU
= ( real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if (
tempU == ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if (
istransportdelay ) * xBufPtr = tempX ; } else { * tailPtr = testIdx ; }
return ( true ) ; } real_T model_AllInOne_acc_rt_TDelayInterpolate ( real_T
tMinusDelay , real_T tStart , real_T * tBuf , real_T * uBuf , int_T bufSz ,
int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput ,
boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ;
real_T yout , t1 , t2 , u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } void
model_AllInOne_Forwallsthataretofartake0asdistancevalue_Enable ( SimStruct *
const S ) { if ( ssGetTaskTime ( S , 5 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } void
model_AllInOne_Forwallsthataretofartake0asdistancevalue_Disable ( SimStruct *
const S ) { ssSetSolverNeedsReset ( S ) ; } void
model_AllInOne_Forwallsthataretofartake0asdistancevalue ( const real_T rtu_0
[ 9 ] , B_Forwallsthataretofartake0asdistancevalue_model_AllInOne_T * localB
) { memcpy ( & localB -> B_20_0_0 [ 0 ] , & rtu_0 [ 0 ] , 9U * sizeof (
real_T ) ) ; } void
model_AllInOne_Forwallsthataretofartake0asdistancevalue_Term ( SimStruct *
const S ) { } void model_AllInOne_nobox_Enable ( SimStruct * const S ) { if (
ssGetTaskTime ( S , 0 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } void model_AllInOne_nobox_Disable ( SimStruct * const S ) {
ssSetSolverNeedsReset ( S ) ; } void model_AllInOne_nobox ( const real_T
rtu_0 [ 54 ] , real_T rty_no_box [ 54 ] ) { memcpy ( & rty_no_box [ 0 ] , &
rtu_0 [ 0 ] , 54U * sizeof ( real_T ) ) ; } void model_AllInOne_nobox_Term (
SimStruct * const S ) { } void model_AllInOne_NoBO_Enable ( SimStruct * const
S ) { if ( ssGetTaskTime ( S , 0 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } void model_AllInOne_NoBO_Disable (
SimStruct * const S ) { ssSetSolverNeedsReset ( S ) ; } void
model_AllInOne_NoBO ( real_T rtu_0 , real_T * rty_bo ) { * rty_bo = rtu_0 ; }
void model_AllInOne_NoBO_Term ( SimStruct * const S ) { } void
model_AllInOne_BO_Enable ( SimStruct * const S ) { if ( ssGetTaskTime ( S , 0
) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } void
model_AllInOne_BO_Disable ( SimStruct * const S ) { ssSetSolverNeedsReset ( S
) ; } void model_AllInOne_BO ( SimStruct * const S , real_T * rty_bo ,
B_BO_model_AllInOne_T * localB , DW_BO_model_AllInOne_T * localDW ,
P_BO_model_AllInOne_T * localP ) { if ( ssIsSampleHit ( S , 1 , 0 ) ) {
localB -> B_36_0_0 = localP -> P_0 ; } { real_T * * uBuffer = ( real_T * * )
& localDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & localDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ;
real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - localP -> P_1
; ( * rty_bo ) = model_AllInOne_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0
, * tBuffer , * uBuffer , localDW -> TransportDelay_IWORK . CircularBufSize ,
& localDW -> TransportDelay_IWORK . Last , localDW -> TransportDelay_IWORK .
Tail , localDW -> TransportDelay_IWORK . Head , localP -> P_2 , 1 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } } void model_AllInOne_BO_Update ( SimStruct * const S
, B_BO_model_AllInOne_T * localB , DW_BO_model_AllInOne_T * localDW ,
P_BO_model_AllInOne_T * localP ) { { real_T * * uBuffer = ( real_T * * ) &
localDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = (
real_T * * ) & localDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; localDW -> TransportDelay_IWORK . Head = ( ( localDW
-> TransportDelay_IWORK . Head < ( localDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( localDW -> TransportDelay_IWORK . Head + 1 ) : 0
) ; if ( localDW -> TransportDelay_IWORK . Head == localDW ->
TransportDelay_IWORK . Tail ) { if ( !
model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK . CircularBufSize , & localDW -> TransportDelay_IWORK .
Tail , & localDW -> TransportDelay_IWORK . Head , & localDW ->
TransportDelay_IWORK . Last , simTime - localP -> P_1 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , FALSE , & localDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ localDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ localDW -> TransportDelay_IWORK . Head ] = localB
-> B_36_0_0 ; } } void model_AllInOne_BO_Term ( void ) { } real_T
rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { uint32_T lo ; uint32_T hi ; lo
= * u % 127773U * 16807U ; hi = * u / 127773U * 2836U ; if ( lo < hi ) { * u
= 2147483647U - ( hi - lo ) ; } else { * u = lo - hi ; } return ( real_T ) *
u * 4.6566128752457969E-10 ; } real_T rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T *
u ) { real_T y ; real_T sr ; real_T si ; do { sr = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = 2.0 *
rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = sr * sr + si * si ; } while (
si > 1.0 ) ; y = muDoubleScalarSqrt ( - 2.0 * muDoubleScalarLog ( si ) / si )
* sr ; return y ; } void rt_mrdivide_U1d1x3_U2d3x3_Yd1x3_snf ( const real_T
u0 [ 3 ] , const real_T u1 [ 9 ] , real_T y [ 3 ] ) { real_T A [ 9 ] ; real_T
A_0 [ 9 ] ; int32_T r1 ; int32_T r ; int32_T r_0 ; real_T maxval ; real_T a ;
int32_T rtemp ; for ( r1 = 0 ; r1 < 3 ; r1 ++ ) { A [ 3 * r1 ] = u1 [ r1 ] ;
A [ 1 + 3 * r1 ] = u1 [ r1 + 3 ] ; A [ 2 + 3 * r1 ] = u1 [ r1 + 6 ] ; }
memcpy ( & A_0 [ 0 ] , & A [ 0 ] , 9U * sizeof ( real_T ) ) ; r1 = 1 ; r = 2
; r_0 = 3 ; maxval = muDoubleScalarAbs ( A [ 0 ] ) ; a = muDoubleScalarAbs (
A [ 1 ] ) ; if ( a > maxval ) { maxval = a ; r1 = 2 ; r = 1 ; } if (
muDoubleScalarAbs ( A [ 2 ] ) > maxval ) { r1 = 3 ; r = 2 ; r_0 = 1 ; } A_0 [
r - 1 ] = A [ r - 1 ] / A [ r1 - 1 ] ; A_0 [ r_0 - 1 ] /= A_0 [ r1 - 1 ] ;
A_0 [ r + 2 ] -= A_0 [ r - 1 ] * A_0 [ r1 + 2 ] ; A_0 [ r_0 + 2 ] -= A_0 [
r_0 - 1 ] * A_0 [ r1 + 2 ] ; A_0 [ r + 5 ] -= A_0 [ r - 1 ] * A_0 [ r1 + 5 ]
; A_0 [ r_0 + 5 ] -= A_0 [ r_0 - 1 ] * A_0 [ r1 + 5 ] ; if (
muDoubleScalarAbs ( A_0 [ r_0 + 2 ] ) > muDoubleScalarAbs ( A_0 [ r + 2 ] ) )
{ rtemp = r ; r = r_0 ; r_0 = rtemp ; } A_0 [ r_0 + 2 ] /= A_0 [ r + 2 ] ;
A_0 [ r_0 + 5 ] -= A_0 [ r_0 + 2 ] * A_0 [ r + 5 ] ; maxval = u0 [ r - 1 ] -
u0 [ r1 - 1 ] * A_0 [ r - 1 ] ; a = ( ( u0 [ r_0 - 1 ] - u0 [ r1 - 1 ] * A_0
[ r_0 - 1 ] ) - A_0 [ r_0 + 2 ] * maxval ) / A_0 [ r_0 + 5 ] ; maxval -= A_0
[ r + 5 ] * a ; maxval /= A_0 [ r + 2 ] ; y [ 0 ] = ( ( u0 [ r1 - 1 ] - A_0 [
r1 + 5 ] * a ) - A_0 [ r1 + 2 ] * maxval ) / A_0 [ r1 - 1 ] ; y [ 1 ] =
maxval ; y [ 2 ] = a ; } static void mdlOutputs ( SimStruct * S , int_T tid )
{ real_T B_107_11_0 ; real_T B_107_41_0 ; real_T B_107_42_0 ; real_T
B_107_43_0 ; real_T B_107_99_0 ; real_T B_107_246_0 ; real_T B_107_247_0 ;
real_T B_107_248_0 ; real_T B_107_294_0 ; real_T B_107_295_0 ; real_T
B_107_296_0 ; real_T B_107_361_0 ; real_T B_107_367_0 ; real_T B_107_373_0 ;
real_T B_107_379_0 ; real_T B_107_385_0 ; real_T B_107_391_0 ; real_T
B_107_397_0 ; real_T B_107_403_0 ; real_T B_107_409_0 ; real_T B_107_415_0 ;
real_T B_107_421_0 ; real_T B_107_427_0 ; real_T B_107_433_0 ; real_T
B_107_439_0 ; real_T B_107_445_0 ; real_T B_107_451_0 ; real_T B_107_457_0 ;
real_T B_107_463_0 ; real_T B_107_343_0 [ 3 ] ; real_T B_107_341_0 ; real_T
B_107_338_0 ; real_T B_107_340_0 ; real_T B_107_339_0 ; real_T B_106_0_0 [ 9
] ; real_T B_22_0_0 [ 9 ] ; real_T B_107_302_0 ; int8_T rtPrevAction ; int8_T
rtAction ; real_T B_107_337_0 ; real_T B_107_336_0 ; real_T B_107_46_0 ;
real_T B_107_334_0 [ 3 ] ; real_T B_107_342_0 [ 3 ] ; boolean_T B_107_301_0 ;
real_T B_107_9_0 ; real_T B_28_0_0 ; real_T B_19_59_0 ; real_T B_102_68_0 [ 9
] ; real_T B_19_36_0 [ 6 ] ; real_T B_19_1_0 [ 3 ] ; real_T B_96_3_0 [ 17 ] ;
real_T B_98_4_0 [ 17 ] ; real_T B_107_168_0 [ 48 ] ; real_T B_107_200_0 [ 51
] ; real_T B_23_2_0 [ 18 ] ; boolean_T B_2_3_0 [ 768 ] ; real_T B_92_5_0 [ 51
] ; boolean_T B_94_3_0 [ 17 ] ; char_T TRANSA ; char_T TRANSB ; ptrdiff_t M ;
ptrdiff_t N ; ptrdiff_t K ; ptrdiff_t LDA ; ptrdiff_t LDB ; ptrdiff_t LDC ;
int32_T i ; int32_T i_0 ; real_T tmp [ 6 ] ; real_T B [ 6 ] ; real_T B_0 [ 51
] ; real_T B_107_13_0_idx ; real_T B_19_46_0_idx ; real_T B_107_13_0_idx_0 ;
real_T B_107_13_0_idx_1 ; real_T tmpForInput_idx ; real_T tmpForInput_idx_0 ;
real_T B_19_46_0_idx_0 ; real_T B_19_46_0_idx_1 ; real_T B_107_259_0_idx ;
real_T B_107_259_0_idx_0 ; real_T B_107_259_0_idx_1 ; real_T B_16_1_0_idx ;
real_T B_16_1_0_idx_0 ; real_T B_16_1_0_idx_1 ; real_T B_16_2_0_idx ; real_T
B_16_2_0_idx_0 ; real_T B_16_2_0_idx_1 ; B_model_AllInOne_T * _rtB ;
P_model_AllInOne_T * _rtP ; DW_model_AllInOne_T * _rtDW ; _rtDW = ( (
DW_model_AllInOne_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ; _rtB = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) ; { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 3
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay ; tMinusDelay = ( (
_rtP -> P_34 > 0.0 ) ? _rtP -> P_34 : 0.0 ) ; tMinusDelay = simTime -
tMinusDelay ; ( ( B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_0_0 [
0 ] = model_AllInOne_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer
, * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize [ 0 ] , & _rtDW
-> TransportDelay_IWORK . Last [ 0 ] , _rtDW -> TransportDelay_IWORK . Tail [
0 ] , _rtDW -> TransportDelay_IWORK . Head [ 0 ] , _rtP -> P_35 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; tBuffer ++ ; uBuffer ++ ; tMinusDelay = ( ( _rtP -> P_34
> 0.0 ) ? _rtP -> P_34 : 0.0 ) ; tMinusDelay = simTime - tMinusDelay ; ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_0_0 [ 1 ] =
model_AllInOne_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize [ 1 ] , & _rtDW ->
TransportDelay_IWORK . Last [ 1 ] , _rtDW -> TransportDelay_IWORK . Tail [ 1
] , _rtDW -> TransportDelay_IWORK . Head [ 1 ] , _rtP -> P_35 , 1 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; tBuffer ++ ; uBuffer ++ ; tMinusDelay = ( ( _rtP -> P_34
> 0.0 ) ? _rtP -> P_34 : 0.0 ) ; tMinusDelay = simTime - tMinusDelay ; ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_0_0 [ 2 ] =
model_AllInOne_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize [ 2 ] , & _rtDW ->
TransportDelay_IWORK . Last [ 2 ] , _rtDW -> TransportDelay_IWORK . Tail [ 2
] , _rtDW -> TransportDelay_IWORK . Head [ 2 ] , _rtP -> P_35 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { B_107_302_0 =
_rtP -> P_37 ; _rtB -> B_107_3_0 = _rtP -> P_36 * _rtP -> P_37 ; } ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_4_0 [ 0 ] = ( (
X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> xeyeze_CSTATE [ 0 ] ; ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_4_0 [ 1 ] = ( (
X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> xeyeze_CSTATE [ 1 ] ; ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_4_0 [ 2 ] = ( (
X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> xeyeze_CSTATE [ 2 ] ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_107_5_0 = _rtP -> P_39 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem ; if ( ssIsMajorTimeStep ( S ) ) {
if ( _rtB -> B_107_4_0 [ 1 ] > 0.12 ) { rtAction = 0 ; } else { rtAction = 1
; } _rtDW -> If_ActiveSubsystem = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
ssSetSolverNeedsReset ( S ) ; switch ( _rtDW -> If2_ActiveSubsystem ) { case
0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 : ssSetSolverNeedsReset ( S
) ; break ; } _rtDW -> If2_ActiveSubsystem = - 1 ; break ; } } switch (
rtAction ) { case 0 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime (
S , 0 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } B_107_9_0
= _rtB -> B_107_5_0 ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW ->
passthrough_SubsysRanBC ) ; } break ; case 1 : if ( rtAction != rtPrevAction
) { if ( ssGetTaskTime ( S , 0 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB
-> B_27_0_0 = _rtP -> P_21 ; _rtB -> B_27_1_0 = _rtP -> P_22 ; } _rtB ->
B_27_4_0 = ( _rtB -> B_27_0_0 * _rtB -> B_27_1_0 + _rtB -> B_107_0_0 [ 1 ] )
* _rtP -> P_23 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_27_5_0 = _rtP
-> P_24 ; } rtPrevAction = _rtDW -> If2_ActiveSubsystem ; if (
ssIsMajorTimeStep ( S ) ) { if ( _rtB -> B_27_4_0 > 0.0 ) { rtAction = 0 ; }
else { rtAction = 1 ; } _rtDW -> If2_ActiveSubsystem = rtAction ; } else {
rtAction = _rtDW -> If2_ActiveSubsystem ; } if ( rtPrevAction != rtAction ) {
switch ( rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case
1 : ssSetSolverNeedsReset ( S ) ; break ; } } switch ( rtAction ) { case 0 :
if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 0 ) != ssGetTStart
( S ) ) { ssSetSolverNeedsReset ( S ) ; } } B_107_9_0 = _rtB -> B_27_4_0 ; if
( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> passthroughA1_SubsysRanBC
) ; } break ; case 1 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime (
S , 0 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } B_107_9_0
= _rtB -> B_27_5_0 ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW ->
zeroFn_SubsysRanBC ) ; } break ; } if ( ssIsMajorTimeStep ( S ) ) {
srUpdateBC ( _rtDW -> gtezeroonly_SubsysRanBC ) ; } break ; } B_107_11_0 = (
_rtB -> B_107_3_0 + B_107_9_0 ) + _rtB -> B_107_0_0 [ 1 ] ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_23_1_0 = _rtP -> P_19 ; memcpy ( &
B_23_2_0 [ 0 ] , & _rtP -> P_20 [ 0 ] , 18U * sizeof ( real_T ) ) ; }
B_107_13_0_idx_0 = _rtB -> B_107_0_0 [ 0 ] / _rtB -> B_23_1_0 ;
B_107_13_0_idx = B_107_11_0 / _rtB -> B_23_1_0 ; B_107_13_0_idx_1 = _rtB ->
B_107_0_0 [ 2 ] / _rtB -> B_23_1_0 ; B_107_343_0 [ 0 ] = ( (
X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> ubvbwb_CSTATE [ 0 ] ;
B_107_343_0 [ 1 ] = ( ( X_model_AllInOne_T * ) ssGetContStates ( S ) ) ->
ubvbwb_CSTATE [ 1 ] ; B_107_343_0 [ 2 ] = ( ( X_model_AllInOne_T * )
ssGetContStates ( S ) ) -> ubvbwb_CSTATE [ 2 ] ; ( ( B_model_AllInOne_T * )
_ssGetBlockIO ( S ) ) -> B_107_15_0 [ 0 ] = ( ( X_model_AllInOne_T * )
ssGetContStates ( S ) ) -> pqr_CSTATE [ 0 ] ; ( ( B_model_AllInOne_T * )
_ssGetBlockIO ( S ) ) -> B_107_15_0 [ 1 ] = ( ( X_model_AllInOne_T * )
ssGetContStates ( S ) ) -> pqr_CSTATE [ 1 ] ; ( ( B_model_AllInOne_T * )
_ssGetBlockIO ( S ) ) -> B_107_15_0 [ 2 ] = ( ( X_model_AllInOne_T * )
ssGetContStates ( S ) ) -> pqr_CSTATE [ 2 ] ; B_107_341_0 = B_107_343_0 [ 1 ]
* _rtB -> B_107_15_0 [ 2 ] ; B_107_340_0 = B_107_343_0 [ 2 ] * _rtB ->
B_107_15_0 [ 0 ] ; B_107_339_0 = B_107_343_0 [ 0 ] * _rtB -> B_107_15_0 [ 1 ]
; B_107_338_0 = B_107_343_0 [ 2 ] * _rtB -> B_107_15_0 [ 1 ] ; _rtB ->
B_107_23_0 [ 0 ] = ( B_107_341_0 - B_107_338_0 ) + B_107_13_0_idx_0 ; _rtB ->
B_107_23_0 [ 1 ] = ( B_107_340_0 - B_107_343_0 [ 0 ] * _rtB -> B_107_15_0 [ 2
] ) + B_107_13_0_idx ; _rtB -> B_107_23_0 [ 2 ] = ( B_107_339_0 - B_107_343_0
[ 1 ] * _rtB -> B_107_15_0 [ 0 ] ) + B_107_13_0_idx_1 ; if ( ssIsSampleHit (
S , 2 , 0 ) ) { _rtB -> B_107_24_0 = _rtDW -> UnitDelay1_DSTATE ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_107_25_0 = _rtP -> P_43 ; _rtB ->
B_107_26_0 = _rtP -> P_44 ; _rtB -> B_107_27_0 = _rtP -> P_45 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_b ; if ( ssIsMajorTimeStep ( S ) )
{ if ( _rtB -> B_107_26_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ; }
_rtDW -> If_ActiveSubsystem_b = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_b ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_27_0 , & B_107_41_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO . NoBO_SubsysRanBC ) ;
} break ; case 1 : if ( rtAction != rtPrevAction ) { model_AllInOne_BO_Enable
( S ) ; } model_AllInOne_BO ( S , & B_107_41_0 , & _rtB -> BO , & _rtDW -> BO
, ( P_BO_model_AllInOne_T * ) & _rtP -> BO ) ; if ( ssIsMajorTimeStep ( S ) )
{ srUpdateBC ( _rtDW -> BO . BO_SubsysRanBC ) ; } break ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_107_31_0 = _rtP -> P_46 ; _rtB ->
B_107_32_0 = _rtP -> P_47 ; } rtPrevAction = _rtDW -> If_ActiveSubsystem_m ;
if ( ssIsMajorTimeStep ( S ) ) { if ( _rtB -> B_107_31_0 < 0.0 ) { rtAction =
0 ; } else { rtAction = 1 ; } _rtDW -> If_ActiveSubsystem_m = rtAction ; }
else { rtAction = _rtDW -> If_ActiveSubsystem_m ; } if ( rtPrevAction !=
rtAction ) { switch ( rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable (
S ) ; break ; case 1 : model_AllInOne_BO_Disable ( S ) ; break ; } } switch (
rtAction ) { case 0 : if ( rtAction != rtPrevAction ) {
model_AllInOne_NoBO_Enable ( S ) ; } model_AllInOne_NoBO ( _rtB -> B_107_32_0
, & B_107_42_0 ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW ->
NoBO_l . NoBO_SubsysRanBC ) ; } break ; case 1 : if ( rtAction !=
rtPrevAction ) { model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , &
B_107_42_0 , & _rtB -> BO_a , & _rtDW -> BO_a , ( P_BO_model_AllInOne_T * ) &
_rtP -> BO_a ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_a
. BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_36_0 = _rtP -> P_48 ; _rtB -> B_107_37_0 = _rtP -> P_49 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_i ; if ( ssIsMajorTimeStep ( S ) )
{ if ( _rtB -> B_107_36_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ; }
_rtDW -> If_ActiveSubsystem_i = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_i ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_37_0 , & B_107_43_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_la . NoBO_SubsysRanBC
) ; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_43_0 , &
_rtB -> BO_c , & _rtDW -> BO_c , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_c )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_c .
BO_SubsysRanBC ) ; } break ; } switch ( ( int32_T ) _rtB -> B_107_25_0 ) {
case 1 : B_19_59_0 = B_107_41_0 ; break ; case 2 : B_19_59_0 = B_107_43_0 ;
break ; default : B_19_59_0 = B_107_42_0 ; break ; } ( ( B_model_AllInOne_T *
) _ssGetBlockIO ( S ) ) -> B_107_45_0 [ 0 ] = ( ( X_model_AllInOne_T * )
ssGetContStates ( S ) ) -> phithetapsi_CSTATE [ 0 ] ; ( ( B_model_AllInOne_T
* ) _ssGetBlockIO ( S ) ) -> B_107_45_0 [ 1 ] = ( ( X_model_AllInOne_T * )
ssGetContStates ( S ) ) -> phithetapsi_CSTATE [ 1 ] ; ( ( B_model_AllInOne_T
* ) _ssGetBlockIO ( S ) ) -> B_107_45_0 [ 2 ] = ( ( X_model_AllInOne_T * )
ssGetContStates ( S ) ) -> phithetapsi_CSTATE [ 2 ] ; if ( ssIsSampleHit ( S
, 1 , 0 ) ) { B_107_46_0 = _rtP -> P_51 ; } if ( ssIsSampleHit ( S , 2 , 0 )
) { _rtB -> B_107_48_0 = _rtP -> P_55 * _rtDW -> NextOutput ; _rtB ->
B_107_50_0 = _rtP -> P_59 * _rtDW -> NextOutput_a ; _rtB -> B_107_52_0 = _rtP
-> P_63 * _rtDW -> NextOutput_g ; _rtB -> B_107_54_0 = _rtP -> P_67 * _rtDW
-> NextOutput_f ; _rtB -> B_107_56_0 = _rtP -> P_71 * _rtDW -> NextOutput_i ;
_rtB -> B_107_58_0 = _rtP -> P_75 * _rtDW -> NextOutput_iq ; _rtB ->
B_107_60_0 = _rtP -> P_79 * _rtDW -> NextOutput_e ; _rtB -> B_107_62_0 = _rtP
-> P_83 * _rtDW -> NextOutput_k ; _rtB -> B_107_64_0 = _rtP -> P_87 * _rtDW
-> NextOutput_ka ; _rtB -> B_107_66_0 = _rtP -> P_91 * _rtDW -> NextOutput_a1
; _rtB -> B_107_68_0 = _rtP -> P_95 * _rtDW -> NextOutput_kr ; _rtB ->
B_107_70_0 = _rtP -> P_99 * _rtDW -> NextOutput_c ; _rtB -> B_107_72_0 = _rtP
-> P_103 * _rtDW -> NextOutput_o ; _rtB -> B_107_74_0 = _rtP -> P_107 * _rtDW
-> NextOutput_b ; _rtB -> B_107_76_0 = _rtP -> P_111 * _rtDW -> NextOutput_l
; _rtB -> B_107_78_0 = _rtP -> P_115 * _rtDW -> NextOutput_e0 ; _rtB ->
B_107_80_0 = _rtP -> P_119 * _rtDW -> NextOutput_b5 ; _rtB -> B_107_82_0 =
_rtP -> P_123 * _rtDW -> NextOutput_ld ; _rtB -> B_107_84_0 = _rtP -> P_127 *
_rtDW -> NextOutput_p ; _rtB -> B_107_86_0 = _rtP -> P_131 * _rtDW ->
NextOutput_aj ; _rtB -> B_107_88_0 = _rtP -> P_135 * _rtDW -> NextOutput_bv ;
_rtB -> B_107_90_0 = _rtP -> P_139 * _rtDW -> NextOutput_m ; _rtB ->
B_107_92_0 = _rtP -> P_143 * _rtDW -> NextOutput_c0 ; _rtB -> B_107_94_0 =
_rtP -> P_147 * _rtDW -> NextOutput_gm ; } if ( ssIsSampleHit ( S , 1 , 0 ) )
{ switch ( ( int32_T ) B_107_46_0 ) { case 1 : _rtB -> B_107_95_0 [ 0 ] =
_rtB -> B_107_48_0 ; _rtB -> B_107_95_0 [ 1 ] = _rtB -> B_107_50_0 ; _rtB ->
B_107_95_0 [ 2 ] = _rtB -> B_107_52_0 ; _rtB -> B_107_95_0 [ 3 ] = _rtB ->
B_107_54_0 ; _rtB -> B_107_95_0 [ 4 ] = _rtB -> B_107_56_0 ; _rtB ->
B_107_95_0 [ 5 ] = _rtB -> B_107_58_0 ; break ; case 2 : _rtB -> B_107_95_0 [
0 ] = _rtB -> B_107_60_0 ; _rtB -> B_107_95_0 [ 1 ] = _rtB -> B_107_62_0 ;
_rtB -> B_107_95_0 [ 2 ] = _rtB -> B_107_64_0 ; _rtB -> B_107_95_0 [ 3 ] =
_rtB -> B_107_66_0 ; _rtB -> B_107_95_0 [ 4 ] = _rtB -> B_107_68_0 ; _rtB ->
B_107_95_0 [ 5 ] = _rtB -> B_107_70_0 ; break ; case 3 : _rtB -> B_107_95_0 [
0 ] = _rtB -> B_107_72_0 ; _rtB -> B_107_95_0 [ 1 ] = _rtB -> B_107_74_0 ;
_rtB -> B_107_95_0 [ 2 ] = _rtB -> B_107_76_0 ; _rtB -> B_107_95_0 [ 3 ] =
_rtB -> B_107_78_0 ; _rtB -> B_107_95_0 [ 4 ] = _rtB -> B_107_80_0 ; _rtB ->
B_107_95_0 [ 5 ] = _rtB -> B_107_82_0 ; break ; default : _rtB -> B_107_95_0
[ 0 ] = _rtB -> B_107_84_0 ; _rtB -> B_107_95_0 [ 1 ] = _rtB -> B_107_86_0 ;
_rtB -> B_107_95_0 [ 2 ] = _rtB -> B_107_88_0 ; _rtB -> B_107_95_0 [ 3 ] =
_rtB -> B_107_90_0 ; _rtB -> B_107_95_0 [ 4 ] = _rtB -> B_107_92_0 ; _rtB ->
B_107_95_0 [ 5 ] = _rtB -> B_107_94_0 ; break ; } } _rtB -> B_107_96_0 [ 0 ]
= _rtB -> B_107_45_0 [ 0 ] + _rtB -> B_107_95_0 [ 3 ] ; _rtB -> B_107_96_0 [
1 ] = _rtB -> B_107_45_0 [ 1 ] + _rtB -> B_107_95_0 [ 4 ] ; _rtB ->
B_107_96_0 [ 2 ] = _rtB -> B_107_45_0 [ 2 ] + _rtB -> B_107_95_0 [ 5 ] ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_107_97_0 = _rtP -> P_148 ; _rtB ->
B_107_98_0 = _rtP -> P_149 ; } B_107_99_0 = ssGetT ( S ) ; B_107_9_0 = 0.008
* B_107_99_0 ; B_107_46_0 = - 0.003 * B_107_99_0 ; if ( ssIsSampleHit ( S , 1
, 0 ) ) { _rtB -> B_107_102_0 = _rtP -> P_150 ; } switch ( ( int32_T ) _rtB
-> B_107_97_0 ) { case 1 : B_19_36_0 [ 0 ] = _rtB -> B_107_98_0 ; B_19_36_0 [
1 ] = _rtB -> B_107_98_0 ; B_19_36_0 [ 2 ] = _rtB -> B_107_98_0 ; B_19_36_0 [
3 ] = B_107_9_0 ; B_19_36_0 [ 4 ] = B_107_46_0 ; B_19_36_0 [ 5 ] = B_107_46_0
; break ; case 2 : B_28_0_0 = 0.002 * muDoubleScalarPower ( B_107_99_0 , 2.0
) ; B_19_36_0 [ 0 ] = B_107_9_0 ; B_19_36_0 [ 1 ] = B_107_46_0 ; B_19_36_0 [
2 ] = _rtB -> B_107_98_0 ; B_19_36_0 [ 3 ] = B_28_0_0 ; B_19_36_0 [ 4 ] =
B_28_0_0 ; B_19_36_0 [ 5 ] = B_107_46_0 ; break ; default : B_19_36_0 [ 0 ] =
_rtB -> B_107_102_0 ; B_19_36_0 [ 1 ] = _rtB -> B_107_102_0 ; B_19_36_0 [ 2 ]
= _rtB -> B_107_102_0 ; B_19_36_0 [ 3 ] = _rtB -> B_107_102_0 ; B_19_36_0 [ 4
] = _rtB -> B_107_102_0 ; B_19_36_0 [ 5 ] = _rtB -> B_107_102_0 ; break ; }
_rtB -> B_107_106_0 [ 0 ] = ( _rtB -> B_107_96_0 [ 0 ] + B_19_36_0 [ 3 ] ) *
B_19_59_0 ; _rtB -> B_107_106_0 [ 1 ] = ( _rtB -> B_107_96_0 [ 1 ] +
B_19_36_0 [ 4 ] ) * B_19_59_0 ; _rtB -> B_107_106_0 [ 2 ] = ( _rtB ->
B_107_96_0 [ 2 ] + B_19_36_0 [ 5 ] ) * B_19_59_0 ; _rtB -> B_107_107_0 = _rtP
-> P_151 * _rtB -> B_107_106_0 [ 1 ] ; B_107_337_0 = _rtB -> B_107_107_0 -
_rtB -> B_107_24_0 ; B_107_9_0 = _rtP -> P_152 * B_107_337_0 ; B_107_338_0 =
( ( X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> Integrator_CSTATE ;
B_107_46_0 = _rtP -> P_154 * B_107_337_0 ; B_107_339_0 = ( (
X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> Filter_CSTATE ; _rtB ->
B_107_114_0 = ( B_107_46_0 - B_107_339_0 ) * _rtP -> P_156 ; _rtB ->
B_107_115_0 = ( B_107_9_0 + B_107_338_0 ) + _rtB -> B_107_114_0 ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> Saturation_MODE = _rtB -> B_107_115_0 >=
_rtP -> P_157 ? 1 : _rtB -> B_107_115_0 > _rtP -> P_158 ? 0 : - 1 ; } _rtB ->
B_107_116_0 = _rtDW -> Saturation_MODE == 1 ? _rtP -> P_157 : _rtDW ->
Saturation_MODE == - 1 ? _rtP -> P_158 : _rtB -> B_107_115_0 ; if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> B_107_117_0 = _rtDW ->
UnitDelay3_DSTATE ; } _rtB -> B_107_118_0 = _rtP -> P_160 * _rtB -> B_107_4_0
[ 0 ] ; B_107_338_0 = _rtB -> B_107_117_0 - _rtB -> B_107_118_0 ; B_107_9_0 =
_rtP -> P_161 * B_107_338_0 ; B_107_339_0 = ( ( X_model_AllInOne_T * )
ssGetContStates ( S ) ) -> Integrator_CSTATE_j ; B_107_46_0 = _rtP -> P_163 *
B_107_338_0 ; B_107_340_0 = ( ( X_model_AllInOne_T * ) ssGetContStates ( S )
) -> Filter_CSTATE_k ; _rtB -> B_107_125_0 = ( B_107_46_0 - B_107_340_0 ) *
_rtP -> P_165 ; _rtB -> B_107_126_0 = ( B_107_9_0 + B_107_339_0 ) + _rtB ->
B_107_125_0 ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Saturation_MODE_c =
_rtB -> B_107_126_0 >= _rtP -> P_166 ? 1 : _rtB -> B_107_126_0 > _rtP ->
P_167 ? 0 : - 1 ; } _rtB -> B_107_127_0 = _rtDW -> Saturation_MODE_c == 1 ?
_rtP -> P_166 : _rtDW -> Saturation_MODE_c == - 1 ? _rtP -> P_167 : _rtB ->
B_107_126_0 ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> B_107_128_0 =
_rtDW -> UnitDelay2_DSTATE ; } B_107_339_0 = _rtB -> B_107_128_0 - _rtB ->
B_107_4_0 [ 2 ] ; B_107_9_0 = _rtP -> P_169 * B_107_339_0 ; B_107_340_0 = ( (
X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> Integrator_CSTATE_a ;
B_107_46_0 = _rtP -> P_171 * B_107_339_0 ; B_107_341_0 = ( (
X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> Filter_CSTATE_e ; _rtB ->
B_107_135_0 = ( B_107_46_0 - B_107_341_0 ) * _rtP -> P_173 ; _rtB ->
B_107_136_0 = ( B_107_9_0 + B_107_340_0 ) + _rtB -> B_107_135_0 ; if (
ssIsMajorTimeStep ( S ) ) { _rtDW -> Saturation_MODE_n = _rtB -> B_107_136_0
>= _rtP -> P_174 ? 1 : _rtB -> B_107_136_0 > _rtP -> P_175 ? 0 : - 1 ; } _rtB
-> B_107_137_0 = _rtDW -> Saturation_MODE_n == 1 ? _rtP -> P_174 : _rtDW ->
Saturation_MODE_n == - 1 ? _rtP -> P_175 : _rtB -> B_107_136_0 ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_107_140_0 = _rtP -> P_176 ; } _rtB
-> B_107_314_0 = ( ( ( _rtB -> B_107_23_0 [ 1 ] + _rtB -> B_107_95_0 [ 1 ] )
+ B_19_36_0 [ 1 ] ) + _rtB -> B_107_140_0 ) * _rtP -> P_177 ; _rtB ->
B_107_143_0 [ 0 ] = ( ( _rtB -> B_107_23_0 [ 0 ] + _rtB -> B_107_95_0 [ 0 ] )
+ B_19_36_0 [ 0 ] ) * B_19_59_0 ; _rtB -> B_107_143_0 [ 1 ] = ( ( _rtB ->
B_107_23_0 [ 2 ] + _rtB -> B_107_95_0 [ 2 ] ) + B_19_36_0 [ 2 ] ) * B_19_59_0
; _rtB -> B_107_143_0 [ 2 ] = B_19_59_0 * _rtB -> B_107_314_0 ;
muDoubleScalarSinCos ( _rtB -> B_107_45_0 [ 2 ] , & B_107_9_0 , & B_107_46_0
) ; B_107_342_0 [ 0 ] = B_107_46_0 ; B_107_334_0 [ 0 ] = B_107_9_0 ;
muDoubleScalarSinCos ( _rtB -> B_107_45_0 [ 1 ] , & B_107_9_0 , & B_107_46_0
) ; B_107_342_0 [ 1 ] = B_107_46_0 ; B_107_334_0 [ 1 ] = B_107_9_0 ;
muDoubleScalarSinCos ( _rtB -> B_107_45_0 [ 0 ] , & B_107_9_0 , & B_107_46_0
) ; _rtB -> B_107_155_0 [ 0 ] = B_107_342_0 [ 1 ] * B_107_342_0 [ 0 ] ; _rtB
-> B_107_155_0 [ 1 ] = B_107_9_0 * B_107_334_0 [ 1 ] * B_107_342_0 [ 0 ] -
B_107_46_0 * B_107_334_0 [ 0 ] ; _rtB -> B_107_155_0 [ 2 ] = B_107_46_0 *
B_107_334_0 [ 1 ] * B_107_342_0 [ 0 ] + B_107_9_0 * B_107_334_0 [ 0 ] ; _rtB
-> B_107_155_0 [ 3 ] = B_107_342_0 [ 1 ] * B_107_334_0 [ 0 ] ; _rtB ->
B_107_155_0 [ 4 ] = B_107_9_0 * B_107_334_0 [ 1 ] * B_107_334_0 [ 0 ] +
B_107_46_0 * B_107_342_0 [ 0 ] ; _rtB -> B_107_155_0 [ 5 ] = B_107_46_0 *
B_107_334_0 [ 1 ] * B_107_334_0 [ 0 ] - B_107_9_0 * B_107_342_0 [ 0 ] ; _rtB
-> B_107_155_0 [ 6 ] = - B_107_334_0 [ 1 ] ; _rtB -> B_107_155_0 [ 7 ] =
B_107_9_0 * B_107_342_0 [ 1 ] ; _rtB -> B_107_155_0 [ 8 ] = B_107_46_0 *
B_107_342_0 [ 1 ] ; for ( i = 0 ; i < 3 ; i ++ ) { _rtB -> B_107_157_0 [ i ]
= 0.0 ; _rtB -> B_107_157_0 [ i ] += _rtB -> B_107_155_0 [ 3 * i ] *
B_107_343_0 [ 0 ] ; _rtB -> B_107_157_0 [ i ] += _rtB -> B_107_155_0 [ 3 * i
+ 1 ] * B_107_343_0 [ 1 ] ; _rtB -> B_107_157_0 [ i ] += _rtB -> B_107_155_0
[ 3 * i + 2 ] * B_107_343_0 [ 2 ] ; } for ( i = 0 ; i < 3 ; i ++ ) { _rtB ->
B_107_159_0 [ i ] = 0.0 ; _rtB -> B_107_159_0 [ i ] += _rtP -> P_178 * _rtB
-> B_107_157_0 [ 0 ] * _rtB -> B_107_155_0 [ i ] ; _rtB -> B_107_159_0 [ i ]
+= _rtB -> B_107_155_0 [ i + 3 ] * ( _rtP -> P_178 * _rtB -> B_107_157_0 [ 1
] ) ; _rtB -> B_107_159_0 [ i ] += _rtB -> B_107_155_0 [ i + 6 ] * ( _rtP ->
P_178 * _rtB -> B_107_157_0 [ 2 ] ) ; } muDoubleScalarSinCos ( _rtP -> P_179
* _rtB -> B_107_106_0 [ 0 ] , & B_107_9_0 , & B_107_46_0 ) ; B_107_334_0 [ 0
] = B_107_46_0 ; B_107_342_0 [ 0 ] = B_107_9_0 ; muDoubleScalarSinCos ( _rtP
-> P_179 * _rtB -> B_107_106_0 [ 2 ] , & B_107_9_0 , & B_107_46_0 ) ;
B_107_334_0 [ 1 ] = B_107_46_0 ; B_107_342_0 [ 1 ] = B_107_9_0 ;
muDoubleScalarSinCos ( _rtP -> P_179 * _rtB -> B_107_107_0 , & B_107_9_0 , &
B_107_46_0 ) ; _rtB -> B_107_162_0 = B_107_334_0 [ 0 ] * B_107_334_0 [ 1 ] *
B_107_46_0 - B_107_342_0 [ 0 ] * B_107_342_0 [ 1 ] * B_107_9_0 ; _rtB ->
B_107_163_0 = B_107_334_0 [ 0 ] * B_107_342_0 [ 1 ] * B_107_9_0 + B_107_342_0
[ 0 ] * B_107_334_0 [ 1 ] * B_107_46_0 ; _rtB -> B_107_164_0 = B_107_334_0 [
0 ] * B_107_342_0 [ 1 ] * B_107_46_0 - B_107_342_0 [ 0 ] * B_107_334_0 [ 1 ]
* B_107_9_0 ; _rtB -> B_107_165_0 = B_107_334_0 [ 0 ] * B_107_334_0 [ 1 ] *
B_107_9_0 + B_107_342_0 [ 0 ] * B_107_342_0 [ 1 ] * B_107_46_0 ; if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> B_107_166_0 [ 0 ] = _rtB ->
B_107_162_0 ; _rtB -> B_107_166_0 [ 1 ] = _rtB -> B_107_163_0 ; _rtB ->
B_107_166_0 [ 2 ] = _rtB -> B_107_164_0 ; _rtB -> B_107_166_0 [ 3 ] = _rtB ->
B_107_165_0 ; for ( i = 0 ; i < 8 ; i ++ ) { _rtB -> B_107_167_0 [ i ] = 0U ;
} } if ( ssIsSampleHit ( S , 3 , 0 ) ) { memcpy ( & B_107_168_0 [ 0 ] , &
_rtP -> P_180 [ 0 ] , 48U * sizeof ( real_T ) ) ; } if ( ssIsSampleHit ( S ,
1 , 0 ) ) { memcpy ( & _rtB -> B_107_169_0 [ 0 ] , & _rtP -> P_181 [ 0 ] ,
963U * sizeof ( real_T ) ) ; B_107_302_0 = _rtP -> P_182 ; _rtB ->
B_107_173_0 [ 0 ] = _rtP -> P_182 ; _rtB -> B_107_173_0 [ 1 ] = _rtP -> P_183
[ 0 ] ; _rtB -> B_107_173_0 [ 2 ] = _rtP -> P_183 [ 1 ] ; ssCallAccelRunBlock
( S , 107 , 174 , SS_CALL_MDL_OUTPUTS ) ; memcpy ( & _rtB -> B_107_175_0 [ 0
] , & _rtP -> P_184 [ 0 ] , 54U * sizeof ( real_T ) ) ; } rtPrevAction =
_rtDW -> If_ActiveSubsystem_m5 ; if ( ssIsMajorTimeStep ( S ) ) { if ( _rtB
-> B_107_174_0 == 1.0 ) { rtAction = 0 ; } else { rtAction = 1 ; } _rtDW ->
If_ActiveSubsystem_m5 = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_m5 ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
model_AllInOne_nobox_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 0 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK_o . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_o .
TUbufferPtrs [ 6 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay ; {
int_T i1 ; real_T * y0 = ( ( B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) ->
B_29_0_0 ; int_T * iw_Tail = & _rtDW -> TransportDelay_IWORK_e . Tail [ 0 ] ;
int_T * iw_Head = & _rtDW -> TransportDelay_IWORK_e . Head [ 0 ] ; int_T *
iw_Last = & _rtDW -> TransportDelay_IWORK_e . Last [ 0 ] ; int_T *
iw_CircularBufSize = & _rtDW -> TransportDelay_IWORK_e . CircularBufSize [ 0
] ; for ( i1 = 0 ; i1 < 6 ; i1 ++ ) { tMinusDelay = ( ( _rtP -> P_25 > 0.0 )
? _rtP -> P_25 : 0.0 ) ; tMinusDelay = simTime - tMinusDelay ; y0 [ i1 ] =
model_AllInOne_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , iw_CircularBufSize [ i1 ] , & iw_Last [ i1 ] , iw_Tail [ i1 ] ,
iw_Head [ i1 ] , _rtP -> P_26 , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( S )
&& ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; tBuffer ++ ; uBuffer
++ ; } } } ssCallAccelRunBlock ( S , 29 , 1 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { for ( i = 0 ; i < 6 ; i ++ ) { _rtB ->
B_29_2_0 [ i ] = _rtP -> P_27 [ i ] ; } } ssCallAccelRunBlock ( S , 29 , 3 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW
-> timedbox_SubsysRanBC ) ; } break ; case 1 : if ( rtAction != rtPrevAction
) { model_AllInOne_nobox_Enable ( S ) ; } model_AllInOne_nobox ( _rtB ->
B_107_175_0 , _rtB -> B_107_195_0 ) ; if ( ssIsMajorTimeStep ( S ) ) {
srUpdateBC ( _rtDW -> nobox . nobox_SubsysRanBC ) ; } break ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_107_181_0 [ 0 ] = B_107_302_0 ;
_rtB -> B_107_181_0 [ 1 ] = _rtP -> P_185 ; ssCallAccelRunBlock ( S , 107 ,
182 , SS_CALL_MDL_OUTPUTS ) ; memcpy ( & _rtB -> B_107_183_0 [ 0 ] , & _rtP
-> P_186 [ 0 ] , 54U * sizeof ( real_T ) ) ; } rtPrevAction = _rtDW ->
If_ActiveSubsystem_j ; if ( ssIsMajorTimeStep ( S ) ) { if ( _rtB ->
B_107_182_0 == 1.0 ) { rtAction = 0 ; } else { rtAction = 1 ; } _rtDW ->
If_ActiveSubsystem_j = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_j ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
model_AllInOne_nobox_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 0 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK_n . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_n .
TUbufferPtrs [ 6 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay ; {
int_T i1 ; real_T * y0 = ( ( B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) ->
B_31_0_0 ; int_T * iw_Tail = & _rtDW -> TransportDelay_IWORK_a . Tail [ 0 ] ;
int_T * iw_Head = & _rtDW -> TransportDelay_IWORK_a . Head [ 0 ] ; int_T *
iw_Last = & _rtDW -> TransportDelay_IWORK_a . Last [ 0 ] ; int_T *
iw_CircularBufSize = & _rtDW -> TransportDelay_IWORK_a . CircularBufSize [ 0
] ; for ( i1 = 0 ; i1 < 6 ; i1 ++ ) { tMinusDelay = ( ( _rtP -> P_28 > 0.0 )
? _rtP -> P_28 : 0.0 ) ; tMinusDelay = simTime - tMinusDelay ; y0 [ i1 ] =
model_AllInOne_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , iw_CircularBufSize [ i1 ] , & iw_Last [ i1 ] , iw_Tail [ i1 ] ,
iw_Head [ i1 ] , _rtP -> P_29 , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( S )
&& ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; tBuffer ++ ; uBuffer
++ ; } } } ssCallAccelRunBlock ( S , 31 , 1 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { for ( i = 0 ; i < 6 ; i ++ ) { _rtB ->
B_31_2_0 [ i ] = _rtP -> P_30 [ i ] ; } } ssCallAccelRunBlock ( S , 31 , 3 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW
-> timedbox_SubsysRanBC_a ) ; } break ; case 1 : if ( rtAction !=
rtPrevAction ) { model_AllInOne_nobox_Enable ( S ) ; } model_AllInOne_nobox (
_rtB -> B_107_183_0 , _rtB -> B_107_196_0 ) ; if ( ssIsMajorTimeStep ( S ) )
{ srUpdateBC ( _rtDW -> nobox_j . nobox_SubsysRanBC ) ; } break ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_107_189_0 [ 0 ] = B_107_302_0 ;
_rtB -> B_107_189_0 [ 1 ] = _rtP -> P_187 ; ssCallAccelRunBlock ( S , 107 ,
190 , SS_CALL_MDL_OUTPUTS ) ; memcpy ( & _rtB -> B_107_191_0 [ 0 ] , & _rtP
-> P_188 [ 0 ] , 54U * sizeof ( real_T ) ) ; } rtPrevAction = _rtDW ->
If_ActiveSubsystem_g ; if ( ssIsMajorTimeStep ( S ) ) { if ( _rtB ->
B_107_190_0 == 1.0 ) { rtAction = 0 ; } else { rtAction = 1 ; } _rtDW ->
If_ActiveSubsystem_g = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_g ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
model_AllInOne_nobox_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 0 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay_PWORK_p . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_p .
TUbufferPtrs [ 6 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay ; {
int_T i1 ; real_T * y0 = ( ( B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) ->
B_33_0_0 ; int_T * iw_Tail = & _rtDW -> TransportDelay_IWORK_j . Tail [ 0 ] ;
int_T * iw_Head = & _rtDW -> TransportDelay_IWORK_j . Head [ 0 ] ; int_T *
iw_Last = & _rtDW -> TransportDelay_IWORK_j . Last [ 0 ] ; int_T *
iw_CircularBufSize = & _rtDW -> TransportDelay_IWORK_j . CircularBufSize [ 0
] ; for ( i1 = 0 ; i1 < 6 ; i1 ++ ) { tMinusDelay = ( ( _rtP -> P_31 > 0.0 )
? _rtP -> P_31 : 0.0 ) ; tMinusDelay = simTime - tMinusDelay ; y0 [ i1 ] =
model_AllInOne_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , iw_CircularBufSize [ i1 ] , & iw_Last [ i1 ] , iw_Tail [ i1 ] ,
iw_Head [ i1 ] , _rtP -> P_32 , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( S )
&& ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; tBuffer ++ ; uBuffer
++ ; } } } ssCallAccelRunBlock ( S , 33 , 1 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { for ( i = 0 ; i < 6 ; i ++ ) { _rtB ->
B_33_2_0 [ i ] = _rtP -> P_33 [ i ] ; } } ssCallAccelRunBlock ( S , 33 , 3 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW
-> timedbox_SubsysRanBC_g ) ; } break ; case 1 : if ( rtAction !=
rtPrevAction ) { model_AllInOne_nobox_Enable ( S ) ; } model_AllInOne_nobox (
_rtB -> B_107_191_0 , _rtB -> B_107_197_0 ) ; if ( ssIsMajorTimeStep ( S ) )
{ srUpdateBC ( _rtDW -> nobox_a . nobox_SubsysRanBC ) ; } break ; } for ( i =
0 ; i < 9 ; i ++ ) { memcpy ( & _rtB -> B_107_199_0 [ 125 * i ] , & _rtB ->
B_107_169_0 [ 107 * i ] , 107U * sizeof ( real_T ) ) ; } for ( i = 0 ; i < 9
; i ++ ) { for ( i_0 = 0 ; i_0 < 6 ; i_0 ++ ) { _rtB -> B_107_199_0 [ ( i_0 +
125 * i ) + 107 ] = _rtB -> B_107_195_0 [ 6 * i + i_0 ] ; } } for ( i = 0 ; i
< 9 ; i ++ ) { for ( i_0 = 0 ; i_0 < 6 ; i_0 ++ ) { _rtB -> B_107_199_0 [ (
i_0 + 125 * i ) + 113 ] = _rtB -> B_107_196_0 [ 6 * i + i_0 ] ; } } for ( i =
0 ; i < 9 ; i ++ ) { for ( i_0 = 0 ; i_0 < 6 ; i_0 ++ ) { _rtB -> B_107_199_0
[ ( i_0 + 125 * i ) + 119 ] = _rtB -> B_107_197_0 [ 6 * i + i_0 ] ; } } if (
ssIsSampleHit ( S , 3 , 0 ) ) { memcpy ( & B_107_200_0 [ 0 ] , & _rtP ->
P_192 [ 0 ] , 51U * sizeof ( real_T ) ) ; B_107_9_0 = ( _rtP -> P_192 [ 0 ] *
_rtP -> P_192 [ 0 ] + _rtP -> P_192 [ 17 ] * _rtP -> P_192 [ 17 ] ) + _rtP ->
P_192 [ 34 ] * _rtP -> P_192 [ 34 ] ; if ( ssIsMajorTimeStep ( S ) ) { if (
_rtDW -> Sqrt_DWORK1 != 0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW ->
Sqrt_DWORK1 = 0 ; } B_107_9_0 = muDoubleScalarSqrt ( B_107_9_0 ) ; } else {
if ( B_107_9_0 < 0.0 ) { B_107_9_0 = - muDoubleScalarSqrt ( muDoubleScalarAbs
( B_107_9_0 ) ) ; } else { B_107_9_0 = muDoubleScalarSqrt ( B_107_9_0 ) ; }
_rtDW -> Sqrt_DWORK1 = 1 ; } _rtDW -> ForEach_ivar = 0 ; while ( _rtDW ->
ForEach_ivar < 125 ) { _rtDW -> ForEach_itr = _rtDW -> ForEach_ivar ; for ( i
= 0 ; i < 9 ; i ++ ) { B_106_0_0 [ i ] = _rtB -> B_107_199_0 [ 125 * i +
_rtDW -> ForEach_itr ] ; } B_107_13_0_idx_0 = B_106_0_0 [ 4 ] * B_106_0_0 [ 8
] - B_106_0_0 [ 5 ] * B_106_0_0 [ 7 ] ; B_107_13_0_idx = B_106_0_0 [ 5 ] *
B_106_0_0 [ 6 ] - B_106_0_0 [ 3 ] * B_106_0_0 [ 8 ] ; B_107_13_0_idx_1 =
B_106_0_0 [ 3 ] * B_106_0_0 [ 7 ] - B_106_0_0 [ 4 ] * B_106_0_0 [ 6 ] ;
B_107_336_0 = ( B_107_13_0_idx_0 * B_107_13_0_idx_0 + B_107_13_0_idx *
B_107_13_0_idx ) + B_107_13_0_idx_1 * B_107_13_0_idx_1 ; if ( B_107_336_0 <
0.0 ) { B_107_336_0 = - muDoubleScalarSqrt ( muDoubleScalarAbs ( B_107_336_0
) ) ; } else { B_107_336_0 = muDoubleScalarSqrt ( B_107_336_0 ) ; } if (
B_107_336_0 > _rtP -> CoreSubsys_n1 . P_1 ) { B_19_46_0_idx_0 =
B_107_13_0_idx_0 ; B_28_0_0 = B_107_13_0_idx ; B_19_46_0_idx_1 =
B_107_13_0_idx_1 ; B_19_46_0_idx = B_107_336_0 ; } else { B_19_46_0_idx_0 =
B_107_13_0_idx_0 * 0.0 ; B_28_0_0 = B_107_13_0_idx * 0.0 ; B_19_46_0_idx_1 =
B_107_13_0_idx_1 * 0.0 ; B_19_46_0_idx = _rtP -> CoreSubsys_n1 . P_0 ; }
B_107_13_0_idx_0 = B_19_46_0_idx_0 / B_19_46_0_idx ; B_107_13_0_idx =
B_28_0_0 / B_19_46_0_idx ; B_107_13_0_idx_1 = B_19_46_0_idx_1 / B_19_46_0_idx
; rtPrevAction = _rtDW -> CoreSubsys_n1 [ _rtDW -> ForEach_ivar + 1 ] .
Checkifwallisnotmorethanu2metersawayfromthesensorsposition_ActiveSubsystem ;
rtAction = - 1 ; if ( muDoubleScalarAbs ( ( ( _rtB -> B_107_4_0 [ 0 ] *
B_107_13_0_idx_0 + _rtB -> B_107_4_0 [ 1 ] * B_107_13_0_idx ) + _rtB ->
B_107_4_0 [ 2 ] * B_107_13_0_idx_1 ) - ( ( B_106_0_0 [ 0 ] * B_107_13_0_idx_0
+ B_106_0_0 [ 1 ] * B_107_13_0_idx ) + B_106_0_0 [ 2 ] * B_107_13_0_idx_1 ) )
<= B_107_9_0 ) { rtAction = 0 ; } _rtDW -> CoreSubsys_n1 [ _rtDW ->
ForEach_ivar + 1 ] .
Checkifwallisnotmorethanu2metersawayfromthesensorsposition_ActiveSubsystem =
rtAction ; if ( ( rtPrevAction != rtAction ) && ( rtPrevAction == 0 ) ) {
model_AllInOne_Forwallsthataretofartake0asdistancevalue_Disable ( S ) ; } if
( rtAction == 0 ) { if ( 0 != rtPrevAction ) {
model_AllInOne_Forwallsthataretofartake0asdistancevalue_Enable ( S ) ; }
model_AllInOne_Forwallsthataretofartake0asdistancevalue ( B_106_0_0 , & _rtB
-> CoreSubsys_n1 [ _rtDW -> ForEach_ivar + 1 ] .
Forwallsthataretofartake0asdistancevalue ) ; srUpdateBC ( _rtDW ->
CoreSubsys_n1 [ _rtDW -> ForEach_ivar + 1 ] .
Forwallsthataretofartake0asdistancevalue .
Forwallsthataretofartake0asdistancevalue_SubsysRanBC ) ; } for ( i = 0 ; i <
9 ; i ++ ) { _rtB -> B_106_3_0 [ _rtDW -> ForEach_itr + 125 * i ] = _rtB ->
CoreSubsys_n1 [ _rtDW -> ForEach_ivar + 1 ] .
Forwallsthataretofartake0asdistancevalue . B_20_0_0 [ i ] ; } _rtDW ->
ForEach_ivar ++ ; } _rtDW -> ForEach_ivar_h = 0 ; while ( _rtDW ->
ForEach_ivar_h < 8 ) { _rtDW -> ForEach_itr_c = _rtDW -> ForEach_ivar_h ;
ssCallAccelCopyCacheForIIS ( S , 103 , ( void * ) 1 ) ; for ( i = 0 ; i < 3 ;
i ++ ) { B_19_1_0 [ i ] = ( ( _rtB -> B_107_155_0 [ 3 * i + 1 ] * B_107_168_0
[ _rtDW -> ForEach_itr_c + 8 ] + _rtB -> B_107_155_0 [ 3 * i ] * B_107_168_0
[ _rtDW -> ForEach_itr_c ] ) + _rtB -> B_107_155_0 [ 3 * i + 2 ] *
B_107_168_0 [ _rtDW -> ForEach_itr_c + 16 ] ) + _rtB -> B_107_4_0 [ i ] ; }
B_28_0_0 = ( B_107_168_0 [ _rtDW -> ForEach_itr_c + 24 ] * _rtP ->
CoreSubsys_n . P_0 [ 0 ] + B_107_168_0 [ _rtDW -> ForEach_itr_c + 32 ] * _rtP
-> CoreSubsys_n . P_0 [ 1 ] ) + B_107_168_0 [ _rtDW -> ForEach_itr_c + 40 ] *
_rtP -> CoreSubsys_n . P_0 [ 2 ] ; if ( B_28_0_0 >= 1.0 ) { B_28_0_0 = 1.0 ;
} else { if ( B_28_0_0 <= - 1.0 ) { B_28_0_0 = - 1.0 ; } }
muDoubleScalarSinCos ( muDoubleScalarAcos ( B_28_0_0 ) / _rtP -> CoreSubsys_n
. P_1 , & B_107_9_0 , & B_19_46_0_idx_0 ) ; tmp [ 0 ] = _rtP -> CoreSubsys_n
. P_0 [ 1 ] ; tmp [ 1 ] = _rtP -> CoreSubsys_n . P_0 [ 2 ] ; tmp [ 2 ] = _rtP
-> CoreSubsys_n . P_0 [ 0 ] ; tmp [ 3 ] = _rtP -> CoreSubsys_n . P_0 [ 2 ] ;
tmp [ 4 ] = _rtP -> CoreSubsys_n . P_0 [ 0 ] ; tmp [ 5 ] = _rtP ->
CoreSubsys_n . P_0 [ 1 ] ; B [ 0 ] = B_107_168_0 [ 40 + _rtDW ->
ForEach_itr_c ] ; B [ 1 ] = B_107_168_0 [ _rtDW -> ForEach_itr_c + 24 ] ; B [
2 ] = B_107_168_0 [ _rtDW -> ForEach_itr_c + 32 ] ; B [ 3 ] = B_107_168_0 [
_rtDW -> ForEach_itr_c + 32 ] ; B [ 4 ] = B_107_168_0 [ _rtDW ->
ForEach_itr_c + 40 ] ; B [ 5 ] = B_107_168_0 [ 24 + _rtDW -> ForEach_itr_c ]
; for ( i = 0 ; i < 6 ; i ++ ) { B_19_36_0 [ i ] = tmp [ i ] * B [ i ] ; }
B_107_13_0_idx_0 = B_19_36_0 [ 0 ] - B_19_36_0 [ 3 ] ; B_107_13_0_idx =
B_19_36_0 [ 1 ] - B_19_36_0 [ 4 ] ; B_107_13_0_idx_1 = B_19_36_0 [ 2 ] -
B_19_36_0 [ 5 ] ; B_19_59_0 = ( B_107_13_0_idx_0 * B_107_13_0_idx_0 +
B_107_13_0_idx * B_107_13_0_idx ) + B_107_13_0_idx_1 * B_107_13_0_idx_1 ; if
( B_19_59_0 < 0.0 ) { B_19_59_0 = - muDoubleScalarSqrt ( muDoubleScalarAbs (
B_19_59_0 ) ) ; } else { B_19_59_0 = muDoubleScalarSqrt ( B_19_59_0 ) ; } if
( ! ( B_19_59_0 > _rtP -> CoreSubsys_n . P_3 ) ) { B_107_13_0_idx_0 *= 0.0 ;
B_107_13_0_idx *= 0.0 ; B_107_13_0_idx_1 *= 0.0 ; B_19_59_0 = _rtP ->
CoreSubsys_n . P_2 ; } B_28_0_0 = B_107_13_0_idx_0 / B_19_59_0 * B_107_9_0 ;
B_19_46_0_idx_1 = B_107_13_0_idx / B_19_59_0 * B_107_9_0 ; B_19_46_0_idx =
B_107_13_0_idx_1 / B_19_59_0 * B_107_9_0 ; B_107_9_0 = ( ( B_19_46_0_idx_0 *
B_19_46_0_idx_0 + B_28_0_0 * B_28_0_0 ) + B_19_46_0_idx_1 * B_19_46_0_idx_1 )
+ B_19_46_0_idx * B_19_46_0_idx ; if ( ssIsMajorTimeStep ( S ) ) { if ( _rtDW
-> CoreSubsys_n [ 0 ] . sqrt_DWORK1 != 0 ) { ssSetSolverNeedsReset ( S ) ;
_rtDW -> CoreSubsys_n [ 0 ] . sqrt_DWORK1 = 0 ; } B_107_9_0 =
muDoubleScalarSqrt ( B_107_9_0 ) ; } else { if ( B_107_9_0 < 0.0 ) {
B_107_9_0 = - muDoubleScalarSqrt ( muDoubleScalarAbs ( B_107_9_0 ) ) ; } else
{ B_107_9_0 = muDoubleScalarSqrt ( B_107_9_0 ) ; } _rtDW -> CoreSubsys_n [ 0
] . sqrt_DWORK1 = 1 ; } B_19_59_0 = B_19_46_0_idx_0 / B_107_9_0 ; B_107_46_0
= B_28_0_0 / B_107_9_0 ; B_28_0_0 = B_19_46_0_idx_1 / B_107_9_0 ; B_107_9_0 =
B_19_46_0_idx / B_107_9_0 ; B_102_68_0 [ 0 ] = ( ( B_19_59_0 * B_19_59_0 +
B_107_46_0 * B_107_46_0 ) - B_28_0_0 * B_28_0_0 ) - B_107_9_0 * B_107_9_0 ;
B_102_68_0 [ 1 ] = ( B_107_46_0 * B_28_0_0 - B_107_9_0 * B_19_59_0 ) * _rtP
-> CoreSubsys_n . P_4 ; B_102_68_0 [ 2 ] = ( B_19_59_0 * B_28_0_0 +
B_107_46_0 * B_107_9_0 ) * _rtP -> CoreSubsys_n . P_5 ; B_102_68_0 [ 3 ] = (
B_107_9_0 * B_19_59_0 + B_107_46_0 * B_28_0_0 ) * _rtP -> CoreSubsys_n . P_6
; B_102_68_0 [ 4 ] = ( ( B_19_59_0 * B_19_59_0 - B_107_46_0 * B_107_46_0 ) +
B_28_0_0 * B_28_0_0 ) - B_107_9_0 * B_107_9_0 ; B_102_68_0 [ 5 ] = ( B_28_0_0
* B_107_9_0 - B_19_59_0 * B_107_46_0 ) * _rtP -> CoreSubsys_n . P_7 ;
B_102_68_0 [ 6 ] = ( B_107_46_0 * B_107_9_0 - B_19_59_0 * B_28_0_0 ) * _rtP
-> CoreSubsys_n . P_8 ; B_102_68_0 [ 7 ] = ( B_19_59_0 * B_107_46_0 +
B_28_0_0 * B_107_9_0 ) * _rtP -> CoreSubsys_n . P_9 ; B_102_68_0 [ 8 ] = ( (
B_19_59_0 * B_19_59_0 - B_107_46_0 * B_107_46_0 ) - B_28_0_0 * B_28_0_0 ) +
B_107_9_0 * B_107_9_0 ; for ( i = 0 ; i < 17 ; i ++ ) { for ( i_0 = 0 ; i_0 <
3 ; i_0 ++ ) { B_0 [ i + 17 * i_0 ] = 0.0 ; B_0 [ i + 17 * i_0 ] +=
B_102_68_0 [ 3 * i_0 ] * B_107_200_0 [ i ] ; B_0 [ i + 17 * i_0 ] +=
B_102_68_0 [ 3 * i_0 + 1 ] * B_107_200_0 [ i + 17 ] ; B_0 [ i + 17 * i_0 ] +=
B_102_68_0 [ 3 * i_0 + 2 ] * B_107_200_0 [ i + 34 ] ; } } for ( i = 0 ; i <
17 ; i ++ ) { for ( i_0 = 0 ; i_0 < 3 ; i_0 ++ ) { _rtB -> CoreSubsys_n [ 0 ]
. B_102_70_0 [ i + 17 * i_0 ] = 0.0 ; _rtB -> CoreSubsys_n [ 0 ] . B_102_70_0
[ i + 17 * i_0 ] += _rtB -> B_107_155_0 [ 3 * i_0 ] * B_0 [ i ] ; _rtB ->
CoreSubsys_n [ 0 ] . B_102_70_0 [ i + 17 * i_0 ] += _rtB -> B_107_155_0 [ 3 *
i_0 + 1 ] * B_0 [ i + 17 ] ; _rtB -> CoreSubsys_n [ 0 ] . B_102_70_0 [ i + 17
* i_0 ] += _rtB -> B_107_155_0 [ 3 * i_0 + 2 ] * B_0 [ i + 34 ] ; } } _rtDW
-> CoreSubsys_n [ 0 ] . ForEach_ivar = 0 ; while ( _rtDW -> CoreSubsys_n [ 0
] . ForEach_ivar < 125 ) { _rtDW -> CoreSubsys_n [ 0 ] . ForEach_itr = _rtDW
-> CoreSubsys_n [ 0 ] . ForEach_ivar ; ssCallAccelCopyCacheForIIS ( S , 101 ,
( void * ) 1 ) ; for ( i = 0 ; i < 9 ; i ++ ) { _rtB -> CoreSubsys_n [ 0 ] .
B_101_0_0 [ i ] = _rtB -> B_106_3_0 [ 125 * i + _rtDW -> CoreSubsys_n [ 0 ] .
ForEach_itr ] ; } ssCallAccelRunBlock ( S , 100 , 0 , SS_CALL_MDL_OUTPUTS ) ;
rtPrevAction = _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
Ifwallconsistsofzerosdonotcalculatedistances_ActiveSubsystem ; if ( _rtB ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_100_0_0 == 0.0 ) { rtAction = 0 ; }
else { rtAction = 1 ; } _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
Ifwallconsistsofzerosdonotcalculatedistances_ActiveSubsystem = rtAction ; if
( rtPrevAction != rtAction ) { switch ( rtPrevAction ) { case 0 :
ssSetSolverNeedsReset ( S ) ; break ; case 1 : ssSetSolverNeedsReset ( S ) ;
ssCallAccelRunBlock ( S , 84 , 0 , SS_CALL_RTW_GENERATED_DISABLE ) ;
ssCallAccelRunBlock ( S , 85 , 0 , SS_CALL_RTW_GENERATED_DISABLE ) ; _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d = 0 ; while ( _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d < 17 ) { switch (
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] .
If_ActiveSubsystem ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1
: ssSetSolverNeedsReset ( S ) ; break ; case 2 : ssSetSolverNeedsReset ( S )
; switch ( _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] .
If1_ActiveSubsystem ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1
: ssSetSolverNeedsReset ( S ) ; break ; } _rtDW -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0
] . ForEach_ivar_d + 1 ] . If1_ActiveSubsystem = - 1 ; break ; } _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [
0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] . If_ActiveSubsystem = - 1 ;
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d ++ ; } break
; } } switch ( rtAction ) { case 0 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( S , 3 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S )
; } } memcpy ( & _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_100_4_0 [
0 ] , & _rtP -> CoreSubsys_n . CoreSubsys . P_1 [ 0 ] , 17U * sizeof ( real_T
) ) ; srUpdateBC ( _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
ReturnzerosasDistances_SubsysRanBC ) ; break ; case 1 : if ( rtAction !=
rtPrevAction ) { if ( ssGetTaskTime ( S , 3 ) != ssGetTStart ( S ) ) {
ssSetSolverNeedsReset ( S ) ; } ssCallAccelRunBlock ( S , 84 , 0 ,
SS_CALL_RTW_GENERATED_ENABLE ) ; ssCallAccelRunBlock ( S , 85 , 0 ,
SS_CALL_RTW_GENERATED_ENABLE ) ; } B_19_46_0_idx = _rtB -> CoreSubsys_n [ 0 ]
. B_101_0_0 [ 3 ] ; tmpForInput_idx = _rtB -> CoreSubsys_n [ 0 ] . B_101_0_0
[ 4 ] ; tmpForInput_idx_0 = _rtB -> CoreSubsys_n [ 0 ] . B_101_0_0 [ 5 ] ;
B_16_1_0_idx = _rtB -> CoreSubsys_n [ 0 ] . B_101_0_0 [ 6 ] ; B_16_1_0_idx_0
= _rtB -> CoreSubsys_n [ 0 ] . B_101_0_0 [ 7 ] ; B_16_1_0_idx_1 = _rtB ->
CoreSubsys_n [ 0 ] . B_101_0_0 [ 8 ] ; _rtB -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . B_99_6_0 [ 0 ] = _rtB -> CoreSubsys_n [ 0 ] . B_101_0_0 [
3 ] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_6_0 [ 1 ] = _rtB
-> CoreSubsys_n [ 0 ] . B_101_0_0 [ 4 ] ; _rtB -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . B_99_6_0 [ 2 ] = _rtB -> CoreSubsys_n [ 0 ] . B_101_0_0 [
5 ] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_6_0 [ 3 ] = _rtB
-> CoreSubsys_n [ 0 ] . B_101_0_0 [ 6 ] ; _rtB -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . B_99_6_0 [ 4 ] = _rtB -> CoreSubsys_n [ 0 ] . B_101_0_0 [
7 ] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_6_0 [ 5 ] = _rtB
-> CoreSubsys_n [ 0 ] . B_101_0_0 [ 8 ] ; ssCallAccelRunBlock ( S , 99 , 7 ,
SS_CALL_MDL_OUTPUTS ) ; for ( i = 0 ; i < 51 ; i ++ ) { _rtB -> CoreSubsys_n
[ 0 ] . CoreSubsys [ 0 ] . B_99_8_0 [ i ] = _rtP -> CoreSubsys_n . CoreSubsys
. P_2 * _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_7_0 [ i ] ; }
ssCallAccelRunBlock ( S , 84 , 0 , SS_CALL_MDL_OUTPUTS ) ; B_16_2_0_idx =
_rtB -> CoreSubsys_n [ 0 ] . B_101_0_0 [ 0 ] ; B_16_2_0_idx_0 = _rtB ->
CoreSubsys_n [ 0 ] . B_101_0_0 [ 1 ] ; B_16_2_0_idx_1 = _rtB -> CoreSubsys_n
[ 0 ] . B_101_0_0 [ 2 ] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
B_99_11_0 [ 0 ] = B_19_1_0 [ 0 ] - _rtB -> CoreSubsys_n [ 0 ] . B_101_0_0 [ 0
] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_11_0 [ 1 ] =
B_19_1_0 [ 1 ] - _rtB -> CoreSubsys_n [ 0 ] . B_101_0_0 [ 1 ] ; _rtB ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_11_0 [ 2 ] = B_19_1_0 [ 2 ] -
_rtB -> CoreSubsys_n [ 0 ] . B_101_0_0 [ 2 ] ; ssCallAccelRunBlock ( S , 85 ,
0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
ForEach_ivar_d = 0 ; while ( _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
ForEach_ivar_d < 17 ) { _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
ForEach_itr_k = _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
ForEach_ivar_d ; B_107_9_0 = _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
B_85_0_1 [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_k ] ;
B_107_46_0 = _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_84_0_1 [ _rtDW
-> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_k ] ; B_107_13_0_idx_0
= _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_7_0 [ 3 * _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_k ] ; B_107_13_0_idx =
_rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_7_0 [ 3 * _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_k + 1 ] ;
B_107_13_0_idx_1 = _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_7_0 [
3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_k + 2 ] ;
rtPrevAction = _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] .
If_ActiveSubsystem ; if ( ( _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
B_85_0_1 [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_k ]
== 0.0 ) && ( _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_84_0_1 [
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_k ] == 0.0 ) ) {
rtAction = 0 ; } else if ( ( _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
B_85_0_1 [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_k ]
!= 0.0 ) && ( _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_84_0_1 [
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_k ] == 0.0 ) ) {
rtAction = 1 ; } else { rtAction = 2 ; } _rtDW -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0
] . ForEach_ivar_d + 1 ] . If_ActiveSubsystem = rtAction ; if ( rtPrevAction
!= rtAction ) { switch ( rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S
) ; break ; case 1 : ssSetSolverNeedsReset ( S ) ; break ; case 2 :
ssSetSolverNeedsReset ( S ) ; switch ( _rtDW -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0
] . ForEach_ivar_d + 1 ] . If1_ActiveSubsystem ) { case 0 :
ssSetSolverNeedsReset ( S ) ; break ; case 1 : ssSetSolverNeedsReset ( S ) ;
break ; } _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW
-> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] .
If1_ActiveSubsystem = - 1 ; break ; } } switch ( rtAction ) { case 0 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 3 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0
] . ForEach_ivar_d + 1 ] . B_91_4_0 [ 0 ] = _rtP -> CoreSubsys_n . CoreSubsys
. CoreSubsys . P_1 [ 0 ] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d
+ 1 ] . B_91_4_0 [ 1 ] = _rtP -> CoreSubsys_n . CoreSubsys . CoreSubsys . P_1
[ 1 ] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] . B_91_4_0 [ 2 ]
= _rtP -> CoreSubsys_n . CoreSubsys . CoreSubsys . P_1 [ 2 ] ; srUpdateBC (
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] .
Intersectionis0ifsensorisintheplane_SubsysRanBC ) ; break ; case 1 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 3 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0
] . ForEach_ivar_d + 1 ] . B_91_4_0 [ 0 ] = _rtP -> CoreSubsys_n . CoreSubsys
. CoreSubsys . P_3 [ 0 ] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d
+ 1 ] . B_91_4_0 [ 1 ] = _rtP -> CoreSubsys_n . CoreSubsys . CoreSubsys . P_3
[ 1 ] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] . B_91_4_0 [ 2 ]
= _rtP -> CoreSubsys_n . CoreSubsys . CoreSubsys . P_3 [ 2 ] ; srUpdateBC (
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] .
Intersectionisinfifplaneandsensorareparalell_SubsysRanBC ) ; break ; case 2 :
if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 3 ) != ssGetTStart
( S ) ) { ssSetSolverNeedsReset ( S ) ; } } B_107_9_0 /= B_107_46_0 ;
rtPrevAction = _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] .
If1_ActiveSubsystem ; if ( B_107_9_0 > 0.0 ) { rtAction = 0 ; } else {
rtAction = 1 ; } _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys
[ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] .
If1_ActiveSubsystem = rtAction ; if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
ssSetSolverNeedsReset ( S ) ; break ; } } switch ( rtAction ) { case 0 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 3 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0
] . ForEach_ivar_d + 1 ] . B_91_4_0 [ 0 ] = B_107_13_0_idx_0 * B_107_9_0 +
B_19_1_0 [ 0 ] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] .
B_91_4_0 [ 1 ] = B_107_13_0_idx * B_107_9_0 + B_19_1_0 [ 1 ] ; _rtB ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [
0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] . B_91_4_0 [ 2 ] =
B_107_13_0_idx_1 * B_107_9_0 + B_19_1_0 [ 2 ] ; srUpdateBC ( _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [
0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] . IfActionSubsystem_SubsysRanBC
) ; break ; case 1 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S
, 3 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [
0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] . B_91_4_0 [ 0 ] = _rtP ->
CoreSubsys_n . CoreSubsys . CoreSubsys . P_5 [ 0 ] ; _rtB -> CoreSubsys_n [ 0
] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys
[ 0 ] . ForEach_ivar_d + 1 ] . B_91_4_0 [ 1 ] = _rtP -> CoreSubsys_n .
CoreSubsys . CoreSubsys . P_5 [ 1 ] ; _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys
[ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
ForEach_ivar_d + 1 ] . B_91_4_0 [ 2 ] = _rtP -> CoreSubsys_n . CoreSubsys .
CoreSubsys . P_5 [ 2 ] ; srUpdateBC ( _rtDW -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0
] . ForEach_ivar_d + 1 ] .
Intersectionisinfifintersectionpointisinthewrongdirection_SubsysRanBC ) ;
break ; } srUpdateBC ( _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d
+ 1 ] . Intersectionifbothdeterminatesarenot0_SubsysRanBC ) ; break ; }
B_92_5_0 [ 3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_k
] = _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys [ _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] . B_91_4_0 [ 0 ]
; B_92_5_0 [ 1 + 3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
ForEach_itr_k ] = _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys
[ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d + 1 ] .
B_91_4_0 [ 1 ] ; B_92_5_0 [ 2 + 3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys
[ 0 ] . ForEach_itr_k ] = _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
CoreSubsys [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_d
+ 1 ] . B_91_4_0 [ 2 ] ; _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
ForEach_ivar_d ++ ; } B_19_59_0 = _rtP -> CoreSubsys_n . CoreSubsys . P_3 ;
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_h = 0 ; while (
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_h < 17 ) {
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_h = _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_h ; B_107_13_0_idx_0 =
B_92_5_0 [ 3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_h
] - B_16_2_0_idx ; B_107_13_0_idx = B_92_5_0 [ 3 * _rtDW -> CoreSubsys_n [ 0
] . CoreSubsys [ 0 ] . ForEach_itr_h + 1 ] - B_16_2_0_idx_0 ;
B_107_13_0_idx_1 = B_92_5_0 [ 3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [
0 ] . ForEach_itr_h + 2 ] - B_16_2_0_idx_1 ; B_28_0_0 = ( B_107_13_0_idx_0 *
B_19_46_0_idx + B_107_13_0_idx * tmpForInput_idx ) + B_107_13_0_idx_1 *
tmpForInput_idx_0 ; B_19_46_0_idx_1 = ( B_107_13_0_idx_0 * B_16_1_0_idx +
B_107_13_0_idx * B_16_1_0_idx_0 ) + B_107_13_0_idx_1 * B_16_1_0_idx_1 ;
B_107_13_0_idx_0 = B_92_5_0 [ 3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [
0 ] . ForEach_itr_h ] - ( ( B_16_2_0_idx + B_19_46_0_idx ) + B_16_1_0_idx ) ;
B_107_13_0_idx = B_92_5_0 [ 3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0
] . ForEach_itr_h + 1 ] - ( ( B_16_2_0_idx_0 + tmpForInput_idx ) +
B_16_1_0_idx_0 ) ; B_107_13_0_idx_1 = B_92_5_0 [ 3 * _rtDW -> CoreSubsys_n [
0 ] . CoreSubsys [ 0 ] . ForEach_itr_h + 2 ] - ( ( B_16_2_0_idx_1 +
tmpForInput_idx_0 ) + B_16_1_0_idx_1 ) ; B_94_3_0 [ _rtDW -> CoreSubsys_n [ 0
] . CoreSubsys [ 0 ] . ForEach_itr_h ] = ! ( boolean_T ) ( ( boolean_T ) ( (
( B_107_13_0_idx_0 * B_19_46_0_idx + B_107_13_0_idx * tmpForInput_idx ) +
B_107_13_0_idx_1 * tmpForInput_idx_0 <= model_AllInOne_rtC ( S ) ->
CoreSubsys_n . CoreSubsys . CoreSubsys_n . B_93_10_0 ) ^ ( boolean_T ) ( (
B_28_0_0 >= model_AllInOne_rtC ( S ) -> CoreSubsys_n . CoreSubsys .
CoreSubsys_n . B_93_2_0 ) ^ ( B_19_46_0_idx_1 >= model_AllInOne_rtC ( S ) ->
CoreSubsys_n . CoreSubsys . CoreSubsys_n . B_93_5_0 ) ) ) ^ ( (
B_107_13_0_idx_0 * B_16_1_0_idx + B_107_13_0_idx * B_16_1_0_idx_0 ) +
B_107_13_0_idx_1 * B_16_1_0_idx_1 <= model_AllInOne_rtC ( S ) -> CoreSubsys_n
. CoreSubsys . CoreSubsys_n . B_93_13_0 ) ) ; _rtDW -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . ForEach_ivar_h ++ ; } _rtDW -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . ForEach_ivar_b = 0 ; while ( _rtDW -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . ForEach_ivar_b < 17 ) { _rtDW -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . ForEach_itr_l = _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [
0 ] . ForEach_ivar_b ; B_107_13_0_idx_0 = B_92_5_0 [ 3 * _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_l ] - B_19_1_0 [ 0 ] ;
B_107_13_0_idx = B_92_5_0 [ 3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0
] . ForEach_itr_l + 1 ] - B_19_1_0 [ 1 ] ; B_107_13_0_idx_1 = B_92_5_0 [ 3 *
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_l + 2 ] -
B_19_1_0 [ 2 ] ; B_107_9_0 = ( B_107_13_0_idx_0 * B_107_13_0_idx_0 +
B_107_13_0_idx * B_107_13_0_idx ) + B_107_13_0_idx_1 * B_107_13_0_idx_1 ; if
( ssIsMajorTimeStep ( S ) ) { if ( _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [
0 ] . CoreSubsys_nx [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
ForEach_ivar_b + 1 ] . Sqrt_DWORK1 != 0 ) { ssSetSolverNeedsReset ( S ) ;
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys_nx [ _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_b + 1 ] . Sqrt_DWORK1 =
0 ; } B_107_9_0 = muDoubleScalarSqrt ( B_107_9_0 ) ; } else { if ( B_107_9_0
< 0.0 ) { B_107_9_0 = - muDoubleScalarSqrt ( muDoubleScalarAbs ( B_107_9_0 )
) ; } else { B_107_9_0 = muDoubleScalarSqrt ( B_107_9_0 ) ; } _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys_nx [ _rtDW -> CoreSubsys_n
[ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_b + 1 ] . Sqrt_DWORK1 = 1 ; }
B_96_3_0 [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr_l ] =
B_107_9_0 ; _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar_b
++ ; } _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar = 0 ;
while ( _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar < 17 )
{ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr = _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar ; B_107_9_0 = B_96_3_0 [
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr ] ; B_107_46_0 =
_rtP -> CoreSubsys_n . CoreSubsys . CoreSubsys_nx2 . P_0 ; B_28_0_0 = ( _rtB
-> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_7_0 [ 3 * _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr + 1 ] * _rtB ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_7_0 [ 3 * _rtDW -> CoreSubsys_n
[ 0 ] . CoreSubsys [ 0 ] . ForEach_itr + 1 ] + _rtB -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . B_99_7_0 [ 3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [
0 ] . ForEach_itr ] * _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
B_99_7_0 [ 3 * _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr ]
) + _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_7_0 [ 3 * _rtDW ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr + 2 ] * _rtB ->
CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_99_7_0 [ 3 * _rtDW -> CoreSubsys_n
[ 0 ] . CoreSubsys [ 0 ] . ForEach_itr + 2 ] ; if ( ssIsMajorTimeStep ( S ) )
{ if ( _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . CoreSubsys_nx2 [
_rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
Sqrt_DWORK1 != 0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW -> CoreSubsys_n [ 0
] . CoreSubsys [ 0 ] . CoreSubsys_nx2 [ _rtDW -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . ForEach_ivar + 1 ] . Sqrt_DWORK1 = 0 ; } B_28_0_0 =
muDoubleScalarSqrt ( B_28_0_0 ) ; } else { if ( B_28_0_0 < 0.0 ) { B_28_0_0 =
- muDoubleScalarSqrt ( muDoubleScalarAbs ( B_28_0_0 ) ) ; } else { B_28_0_0 =
muDoubleScalarSqrt ( B_28_0_0 ) ; } _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys
[ 0 ] . CoreSubsys_nx2 [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
ForEach_ivar + 1 ] . Sqrt_DWORK1 = 1 ; } if ( B_107_9_0 > B_28_0_0 ) {
B_98_4_0 [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . ForEach_itr ] =
B_107_46_0 ; } else { B_98_4_0 [ _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0
] . ForEach_itr ] = B_107_9_0 ; } _rtDW -> CoreSubsys_n [ 0 ] . CoreSubsys [
0 ] . ForEach_ivar ++ ; } for ( i = 0 ; i < 17 ; i ++ ) { if ( B_94_3_0 [ i ]
) { _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] . B_100_4_0 [ i ] =
B_98_4_0 [ i ] ; } else { _rtB -> CoreSubsys_n [ 0 ] . CoreSubsys [ 0 ] .
B_100_4_0 [ i ] = B_19_59_0 ; } } srUpdateBC ( _rtDW -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . CalculateDistances_SubsysRanBC ) ; break ; } for ( i = 0 ;
i < 17 ; i ++ ) { _rtB -> CoreSubsys_n [ 0 ] . B_101_3_0 [ _rtDW ->
CoreSubsys_n [ 0 ] . ForEach_itr + 125 * i ] = _rtB -> CoreSubsys_n [ 0 ] .
CoreSubsys [ 0 ] . B_100_4_0 [ i ] ; } ssCallAccelCopyCacheForIIS ( S , 101 ,
( void * ) 0 ) ; _rtDW -> CoreSubsys_n [ 0 ] . ForEach_ivar ++ ; }
ssCallAccelRunBlock ( S , 102 , 72 , SS_CALL_MDL_OUTPUTS ) ; memcpy ( & _rtB
-> B_103_3_0 [ _rtDW -> ForEach_itr_c * 17 ] , & _rtB -> CoreSubsys_n [ 0 ] .
B_102_72_0 [ 0 ] , 17U * sizeof ( real_T ) ) ; ssCallAccelCopyCacheForIIS ( S
, 103 , ( void * ) 0 ) ; _rtDW -> ForEach_ivar_h ++ ; } ssCallAccelRunBlock (
S , 107 , 209 , SS_CALL_MDL_OUTPUTS ) ; for ( i = 0 ; i < 17 ; i ++ ) { for (
i_0 = 0 ; i_0 < 8 ; i_0 ++ ) { _rtB -> B_107_210_0 [ i_0 + ( i << 3 ) ] =
_rtB -> B_107_209_0 [ 17 * i_0 + i ] ; } } for ( i = 0 ; i < 17 ; i ++ ) {
_rtB -> B_107_211_0 [ i ] = _rtB -> B_107_210_0 [ i << 3 ] ; _rtB ->
B_107_212_0 [ i ] = _rtB -> B_107_210_0 [ ( i << 3 ) + 1 ] ; _rtB ->
B_107_213_0 [ i ] = _rtB -> B_107_210_0 [ ( i << 3 ) + 2 ] ; _rtB ->
B_107_214_0 [ i ] = _rtB -> B_107_210_0 [ ( i << 3 ) + 3 ] ; _rtB ->
B_107_215_0 [ i ] = _rtB -> B_107_210_0 [ ( i << 3 ) + 4 ] ; _rtB ->
B_107_216_0 [ i ] = _rtB -> B_107_210_0 [ ( i << 3 ) + 5 ] ; _rtB ->
B_107_217_0 [ i ] = _rtB -> B_107_210_0 [ ( i << 3 ) + 6 ] ; _rtB ->
B_107_218_0 [ i ] = _rtB -> B_107_210_0 [ ( i << 3 ) + 7 ] ; } } if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> B_107_219_0 = _rtDW ->
UnitDelay_DSTATE ; } B_107_336_0 = _rtB -> B_107_219_0 - _rtB -> B_107_4_0 [
1 ] ; B_107_9_0 = _rtP -> P_196 * B_107_336_0 ; B_107_340_0 = ( (
X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> Integrator_CSTATE_h ;
B_107_46_0 = _rtP -> P_198 * B_107_336_0 ; B_107_341_0 = ( (
X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> Filter_CSTATE_n ; _rtB ->
B_107_226_0 = ( B_107_46_0 - B_107_341_0 ) * _rtP -> P_200 ; _rtB ->
B_107_227_0 = ( B_107_9_0 + B_107_340_0 ) + _rtB -> B_107_226_0 ; if (
ssIsSampleHit ( S , 5 , 0 ) ) { for ( i = 0 ; i < 6 ; i ++ ) { B_19_36_0 [ i
] = _rtP -> P_201 [ i ] ; } _rtDW -> ForEach_ivar_hk = 0 ; while ( _rtDW ->
ForEach_ivar_hk < 125 ) { _rtDW -> ForEach_itr_g = _rtDW -> ForEach_ivar_hk ;
for ( i = 0 ; i < 9 ; i ++ ) { B_22_0_0 [ i ] = _rtB -> B_107_199_0 [ 125 * i
+ _rtDW -> ForEach_itr_g ] ; } B_107_13_0_idx_0 = B_22_0_0 [ 4 ] * B_22_0_0 [
8 ] - B_22_0_0 [ 5 ] * B_22_0_0 [ 7 ] ; B_107_13_0_idx = B_22_0_0 [ 5 ] *
B_22_0_0 [ 6 ] - B_22_0_0 [ 3 ] * B_22_0_0 [ 8 ] ; B_107_13_0_idx_1 =
B_22_0_0 [ 3 ] * B_22_0_0 [ 7 ] - B_22_0_0 [ 4 ] * B_22_0_0 [ 6 ] ;
B_19_46_0_idx = ( B_107_13_0_idx_0 * B_107_13_0_idx_0 + B_107_13_0_idx *
B_107_13_0_idx ) + B_107_13_0_idx_1 * B_107_13_0_idx_1 ; if ( B_19_46_0_idx <
0.0 ) { B_19_46_0_idx = - muDoubleScalarSqrt ( muDoubleScalarAbs (
B_19_46_0_idx ) ) ; } else { B_19_46_0_idx = muDoubleScalarSqrt (
B_19_46_0_idx ) ; } if ( B_19_46_0_idx > _rtP -> CoreSubsys_m . P_1 ) {
B_19_46_0_idx_0 = B_107_13_0_idx_0 ; B_28_0_0 = B_107_13_0_idx ;
B_19_46_0_idx_1 = B_107_13_0_idx_1 ; } else { B_19_46_0_idx_0 =
B_107_13_0_idx_0 * 0.0 ; B_28_0_0 = B_107_13_0_idx * 0.0 ; B_19_46_0_idx_1 =
B_107_13_0_idx_1 * 0.0 ; B_19_46_0_idx = _rtP -> CoreSubsys_m . P_0 ; }
B_107_13_0_idx_0 = B_19_46_0_idx_0 / B_19_46_0_idx ; B_107_13_0_idx =
B_28_0_0 / B_19_46_0_idx ; B_107_13_0_idx_1 = B_19_46_0_idx_1 / B_19_46_0_idx
; rtPrevAction = _rtDW -> CoreSubsys_m [ _rtDW -> ForEach_ivar_hk + 1 ] .
Checkifwallisnotmorethan7metersawayfromthesensorsposition_ActiveSubsystem ;
rtAction = - 1 ; if ( muDoubleScalarAbs ( ( ( _rtB -> B_107_4_0 [ 0 ] *
B_107_13_0_idx_0 + _rtB -> B_107_4_0 [ 1 ] * B_107_13_0_idx ) + _rtB ->
B_107_4_0 [ 2 ] * B_107_13_0_idx_1 ) - ( ( B_22_0_0 [ 0 ] * B_107_13_0_idx_0
+ B_22_0_0 [ 1 ] * B_107_13_0_idx ) + B_22_0_0 [ 2 ] * B_107_13_0_idx_1 ) )
<= 15.0 ) { rtAction = 0 ; } _rtDW -> CoreSubsys_m [ _rtDW -> ForEach_ivar_hk
+ 1 ] .
Checkifwallisnotmorethan7metersawayfromthesensorsposition_ActiveSubsystem =
rtAction ; if ( ( rtPrevAction != rtAction ) && ( rtPrevAction == 0 ) ) {
model_AllInOne_Forwallsthataretofartake0asdistancevalue_Disable ( S ) ; } if
( rtAction == 0 ) { if ( 0 != rtPrevAction ) {
model_AllInOne_Forwallsthataretofartake0asdistancevalue_Enable ( S ) ; }
model_AllInOne_Forwallsthataretofartake0asdistancevalue ( B_22_0_0 , & _rtB
-> CoreSubsys_m [ _rtDW -> ForEach_ivar_hk + 1 ] .
Forwallsthataretofartake0asdistancevalue ) ; srUpdateBC ( _rtDW ->
CoreSubsys_m [ _rtDW -> ForEach_ivar_hk + 1 ] .
Forwallsthataretofartake0asdistancevalue .
Forwallsthataretofartake0asdistancevalue_SubsysRanBC ) ; } for ( i = 0 ; i <
9 ; i ++ ) { _rtB -> B_22_3_0 [ _rtDW -> ForEach_itr_g + 125 * i ] = _rtB ->
CoreSubsys_m [ _rtDW -> ForEach_ivar_hk + 1 ] .
Forwallsthataretofartake0asdistancevalue . B_20_0_0 [ i ] ; } _rtDW ->
ForEach_ivar_hk ++ ; } for ( i = 0 ; i < 3 ; i ++ ) { B_19_1_0 [ i ] = ( (
_rtB -> B_107_155_0 [ 3 * i + 1 ] * B_19_36_0 [ 1 ] + _rtB -> B_107_155_0 [ 3
* i ] * B_19_36_0 [ 0 ] ) + _rtB -> B_107_155_0 [ 3 * i + 2 ] * B_19_36_0 [ 2
] ) + _rtB -> B_107_4_0 [ i ] ; } memcpy ( & _rtB -> B_19_2_0 [ 0 ] , & _rtP
-> P_0 [ 0 ] , 2304U * sizeof ( real_T ) ) ; TRANSA = 'N' ; TRANSB = 'N' ; M
= 768L ; N = 3L ; K = 3L ; B_107_9_0 = 1.0 ; LDA = 768L ; LDB = 3L ;
B_107_46_0 = 0.0 ; LDC = 768L ; dgemm ( & TRANSA , & TRANSB , & M , & N , & K
, ( void * ) & B_107_9_0 , _rtB -> B_19_2_0 , & LDA , _rtP -> P_1 , & LDB , (
void * ) & B_107_46_0 , * ( real_T ( * ) [ 2304 ] ) & _rtB -> B_19_4_0 [ 0 ]
, & LDC ) ; TRANSA = 'N' ; TRANSB = 'N' ; M = 768L ; N = 3L ; K = 3L ;
B_107_9_0 = 1.0 ; LDA = 768L ; LDB = 3L ; B_107_46_0 = 0.0 ; LDC = 768L ;
dgemm ( & TRANSA , & TRANSB , & M , & N , & K , ( void * ) & B_107_9_0 , _rtB
-> B_19_4_0 , & LDA , _rtB -> B_107_155_0 , & LDB , ( void * ) & B_107_46_0 ,
* ( real_T ( * ) [ 2304 ] ) & _rtB -> B_19_5_0 [ 0 ] , & LDC ) ; _rtDW ->
ForEach_ivar_k = 0 ; while ( _rtDW -> ForEach_ivar_k < 125 ) { _rtDW ->
ForEach_itr_b = _rtDW -> ForEach_ivar_k ; ssCallAccelCopyCacheForIIS ( S , 18
, ( void * ) 1 ) ; for ( i = 0 ; i < 9 ; i ++ ) { _rtB -> B_18_0_0 [ i ] =
_rtB -> B_22_3_0 [ 125 * i + _rtDW -> ForEach_itr_b ] ; } ssCallAccelRunBlock
( S , 17 , 0 , SS_CALL_MDL_OUTPUTS ) ; rtPrevAction = _rtDW -> CoreSubsys [ 0
] . Ifwallconsistsofzerosdonotcalculatedistances_ActiveSubsystem ; if ( _rtB
-> CoreSubsys [ 0 ] . B_17_0_0 == 0.0 ) { rtAction = 0 ; } else { rtAction =
1 ; } _rtDW -> CoreSubsys [ 0 ] .
Ifwallconsistsofzerosdonotcalculatedistances_ActiveSubsystem = rtAction ; if
( rtPrevAction != rtAction ) { switch ( rtPrevAction ) { case 0 :
ssSetSolverNeedsReset ( S ) ; break ; case 1 : ssSetSolverNeedsReset ( S ) ;
ssCallAccelRunBlock ( S , 8 , 0 , SS_CALL_RTW_GENERATED_DISABLE ) ;
ssCallAccelRunBlock ( S , 7 , 0 , SS_CALL_RTW_GENERATED_DISABLE ) ; _rtDW ->
CoreSubsys [ 0 ] . ForEach_ivar = 0 ; while ( _rtDW -> CoreSubsys [ 0 ] .
ForEach_ivar < 768 ) { switch ( _rtDW -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [
_rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] . If_ActiveSubsystem ) { case
0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 : ssSetSolverNeedsReset ( S
) ; break ; case 2 : ssSetSolverNeedsReset ( S ) ; switch ( _rtDW ->
CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar
+ 1 ] . If1_ActiveSubsystem ) { case 0 : ssSetSolverNeedsReset ( S ) ; break
; case 1 : ssSetSolverNeedsReset ( S ) ; break ; } _rtDW -> CoreSubsys [ 0 ]
. CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
If1_ActiveSubsystem = - 1 ; break ; } _rtDW -> CoreSubsys [ 0 ] .
CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
If_ActiveSubsystem = - 1 ; _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar ++ ; }
break ; } } switch ( rtAction ) { case 0 : if ( rtAction != rtPrevAction ) {
if ( ssGetTaskTime ( S , 5 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset (
S ) ; } } memcpy ( & _rtB -> CoreSubsys [ 0 ] . B_17_4_0 [ 0 ] , & _rtP ->
CoreSubsys . P_1 [ 0 ] , 768U * sizeof ( real_T ) ) ; srUpdateBC ( _rtDW ->
CoreSubsys [ 0 ] . ReturnzerosasDistances_SubsysRanBC ) ; break ; case 1 : if
( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 5 ) != ssGetTStart (
S ) ) { ssSetSolverNeedsReset ( S ) ; } ssCallAccelRunBlock ( S , 8 , 0 ,
SS_CALL_RTW_GENERATED_ENABLE ) ; ssCallAccelRunBlock ( S , 7 , 0 ,
SS_CALL_RTW_GENERATED_ENABLE ) ; } B_19_46_0_idx = _rtB -> B_18_0_0 [ 3 ] ;
tmpForInput_idx = _rtB -> B_18_0_0 [ 4 ] ; tmpForInput_idx_0 = _rtB ->
B_18_0_0 [ 5 ] ; B_16_1_0_idx = _rtB -> B_18_0_0 [ 6 ] ; B_16_1_0_idx_0 =
_rtB -> B_18_0_0 [ 7 ] ; B_16_1_0_idx_1 = _rtB -> B_18_0_0 [ 8 ] ;
B_16_2_0_idx = _rtB -> B_18_0_0 [ 0 ] ; B_16_2_0_idx_0 = _rtB -> B_18_0_0 [ 1
] ; B_16_2_0_idx_1 = _rtB -> B_18_0_0 [ 2 ] ; _rtB -> CoreSubsys [ 0 ] .
B_16_7_0 [ 0 ] = _rtB -> B_18_0_0 [ 3 ] ; _rtB -> CoreSubsys [ 0 ] . B_16_7_0
[ 1 ] = _rtB -> B_18_0_0 [ 4 ] ; _rtB -> CoreSubsys [ 0 ] . B_16_7_0 [ 2 ] =
_rtB -> B_18_0_0 [ 5 ] ; _rtB -> CoreSubsys [ 0 ] . B_16_7_0 [ 3 ] = _rtB ->
B_18_0_0 [ 6 ] ; _rtB -> CoreSubsys [ 0 ] . B_16_7_0 [ 4 ] = _rtB -> B_18_0_0
[ 7 ] ; _rtB -> CoreSubsys [ 0 ] . B_16_7_0 [ 5 ] = _rtB -> B_18_0_0 [ 8 ] ;
_rtB -> CoreSubsys [ 0 ] . B_16_8_0 [ 0 ] = B_19_1_0 [ 0 ] - _rtB -> B_18_0_0
[ 0 ] ; _rtB -> CoreSubsys [ 0 ] . B_16_8_0 [ 1 ] = B_19_1_0 [ 1 ] - _rtB ->
B_18_0_0 [ 1 ] ; _rtB -> CoreSubsys [ 0 ] . B_16_8_0 [ 2 ] = B_19_1_0 [ 2 ] -
_rtB -> B_18_0_0 [ 2 ] ; ssCallAccelRunBlock ( S , 16 , 9 ,
SS_CALL_MDL_OUTPUTS ) ; for ( i = 0 ; i < 2304 ; i ++ ) { _rtB -> CoreSubsys
[ 0 ] . B_16_10_0 [ i ] = _rtP -> CoreSubsys . P_2 * _rtB -> CoreSubsys [ 0 ]
. B_16_9_0 [ i ] ; } ssCallAccelRunBlock ( S , 8 , 0 , SS_CALL_MDL_OUTPUTS )
; ssCallAccelRunBlock ( S , 7 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
CoreSubsys [ 0 ] . ForEach_ivar = 0 ; while ( _rtDW -> CoreSubsys [ 0 ] .
ForEach_ivar < 768 ) { _rtDW -> CoreSubsys [ 0 ] . ForEach_itr = _rtDW ->
CoreSubsys [ 0 ] . ForEach_ivar ; B_107_9_0 = _rtB -> CoreSubsys [ 0 ] .
B_8_0_1 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_itr ] ; B_107_46_0 = _rtB ->
CoreSubsys [ 0 ] . B_7_0_1 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_itr ] ;
B_107_13_0_idx_0 = _rtB -> CoreSubsys [ 0 ] . B_16_9_0 [ 3 * _rtDW ->
CoreSubsys [ 0 ] . ForEach_itr ] ; B_107_13_0_idx = _rtB -> CoreSubsys [ 0 ]
. B_16_9_0 [ 3 * _rtDW -> CoreSubsys [ 0 ] . ForEach_itr + 1 ] ;
B_107_13_0_idx_1 = _rtB -> CoreSubsys [ 0 ] . B_16_9_0 [ 3 * _rtDW ->
CoreSubsys [ 0 ] . ForEach_itr + 2 ] ; rtPrevAction = _rtDW -> CoreSubsys [ 0
] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
If_ActiveSubsystem ; if ( ( _rtB -> CoreSubsys [ 0 ] . B_8_0_1 [ _rtDW ->
CoreSubsys [ 0 ] . ForEach_itr ] == 0.0 ) && ( _rtB -> CoreSubsys [ 0 ] .
B_7_0_1 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_itr ] == 0.0 ) ) { rtAction = 0
; } else if ( ( _rtB -> CoreSubsys [ 0 ] . B_8_0_1 [ _rtDW -> CoreSubsys [ 0
] . ForEach_itr ] != 0.0 ) && ( _rtB -> CoreSubsys [ 0 ] . B_7_0_1 [ _rtDW ->
CoreSubsys [ 0 ] . ForEach_itr ] == 0.0 ) ) { rtAction = 1 ; } else {
rtAction = 2 ; } _rtDW -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW ->
CoreSubsys [ 0 ] . ForEach_ivar + 1 ] . If_ActiveSubsystem = rtAction ; if (
rtPrevAction != rtAction ) { switch ( rtPrevAction ) { case 0 :
ssSetSolverNeedsReset ( S ) ; break ; case 1 : ssSetSolverNeedsReset ( S ) ;
break ; case 2 : ssSetSolverNeedsReset ( S ) ; switch ( _rtDW -> CoreSubsys [
0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
If1_ActiveSubsystem ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1
: ssSetSolverNeedsReset ( S ) ; break ; } _rtDW -> CoreSubsys [ 0 ] .
CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
If1_ActiveSubsystem = - 1 ; break ; } } switch ( rtAction ) { case 0 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 5 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> CoreSubsys [ 0 ] .
CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] . B_14_4_0 [
0 ] = _rtP -> CoreSubsys . CoreSubsys_mn2 . P_1 [ 0 ] ; _rtB -> CoreSubsys [
0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
B_14_4_0 [ 1 ] = _rtP -> CoreSubsys . CoreSubsys_mn2 . P_1 [ 1 ] ; _rtB ->
CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar
+ 1 ] . B_14_4_0 [ 2 ] = _rtP -> CoreSubsys . CoreSubsys_mn2 . P_1 [ 2 ] ;
srUpdateBC ( _rtDW -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys
[ 0 ] . ForEach_ivar + 1 ] . Intersectionis0ifsensorisintheplane_SubsysRanBC
) ; break ; case 1 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S
, 5 ) != ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB ->
CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar
+ 1 ] . B_14_4_0 [ 0 ] = _rtP -> CoreSubsys . CoreSubsys_mn2 . P_3 [ 0 ] ;
_rtB -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] .
ForEach_ivar + 1 ] . B_14_4_0 [ 1 ] = _rtP -> CoreSubsys . CoreSubsys_mn2 .
P_3 [ 1 ] ; _rtB -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [
0 ] . ForEach_ivar + 1 ] . B_14_4_0 [ 2 ] = _rtP -> CoreSubsys .
CoreSubsys_mn2 . P_3 [ 2 ] ; srUpdateBC ( _rtDW -> CoreSubsys [ 0 ] .
CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
Intersectionisinfifplaneandsensorareparalell_SubsysRanBC ) ; break ; case 2 :
if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 5 ) != ssGetTStart
( S ) ) { ssSetSolverNeedsReset ( S ) ; } } B_107_9_0 /= B_107_46_0 ;
rtPrevAction = _rtDW -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW ->
CoreSubsys [ 0 ] . ForEach_ivar + 1 ] . If1_ActiveSubsystem ; if ( B_107_9_0
> 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ; } _rtDW -> CoreSubsys [ 0 ]
. CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
If1_ActiveSubsystem = rtAction ; if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : ssSetSolverNeedsReset ( S ) ; break ; case 1 :
ssSetSolverNeedsReset ( S ) ; break ; } } switch ( rtAction ) { case 0 : if (
rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 5 ) != ssGetTStart ( S
) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> CoreSubsys [ 0 ] .
CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] . B_14_4_0 [
0 ] = B_107_13_0_idx_0 * B_107_9_0 + B_19_1_0 [ 0 ] ; _rtB -> CoreSubsys [ 0
] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
B_14_4_0 [ 1 ] = B_107_13_0_idx * B_107_9_0 + B_19_1_0 [ 1 ] ; _rtB ->
CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar
+ 1 ] . B_14_4_0 [ 2 ] = B_107_13_0_idx_1 * B_107_9_0 + B_19_1_0 [ 2 ] ;
srUpdateBC ( _rtDW -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys
[ 0 ] . ForEach_ivar + 1 ] . IfActionSubsystem_SubsysRanBC ) ; break ; case 1
: if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( S , 5 ) !=
ssGetTStart ( S ) ) { ssSetSolverNeedsReset ( S ) ; } } _rtB -> CoreSubsys [
0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
B_14_4_0 [ 0 ] = _rtP -> CoreSubsys . CoreSubsys_mn2 . P_5 [ 0 ] ; _rtB ->
CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar
+ 1 ] . B_14_4_0 [ 1 ] = _rtP -> CoreSubsys . CoreSubsys_mn2 . P_5 [ 1 ] ;
_rtB -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] .
ForEach_ivar + 1 ] . B_14_4_0 [ 2 ] = _rtP -> CoreSubsys . CoreSubsys_mn2 .
P_5 [ 2 ] ; srUpdateBC ( _rtDW -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW
-> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
Intersectionisinfifintersectionpointisinthewrongdirection_SubsysRanBC ) ;
break ; } srUpdateBC ( _rtDW -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW ->
CoreSubsys [ 0 ] . ForEach_ivar + 1 ] .
Intersectionifbothdeterminatesarenot0_SubsysRanBC ) ; break ; } _rtB ->
CoreSubsys [ 0 ] . B_15_5_0 [ 3 * _rtDW -> CoreSubsys [ 0 ] . ForEach_itr ] =
_rtB -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] .
ForEach_ivar + 1 ] . B_14_4_0 [ 0 ] ; _rtB -> CoreSubsys [ 0 ] . B_15_5_0 [ 1
+ 3 * _rtDW -> CoreSubsys [ 0 ] . ForEach_itr ] = _rtB -> CoreSubsys [ 0 ] .
CoreSubsys_mn2 [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar + 1 ] . B_14_4_0 [
1 ] ; _rtB -> CoreSubsys [ 0 ] . B_15_5_0 [ 2 + 3 * _rtDW -> CoreSubsys [ 0 ]
. ForEach_itr ] = _rtB -> CoreSubsys [ 0 ] . CoreSubsys_mn2 [ _rtDW ->
CoreSubsys [ 0 ] . ForEach_ivar + 1 ] . B_14_4_0 [ 2 ] ; _rtDW -> CoreSubsys
[ 0 ] . ForEach_ivar ++ ; } _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_gi = 0 ;
while ( _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_gi < 768 ) { _rtDW ->
CoreSubsys [ 0 ] . ForEach_itr_i = _rtDW -> CoreSubsys [ 0 ] .
ForEach_ivar_gi ; B_107_13_0_idx_0 = _rtB -> CoreSubsys [ 0 ] . B_15_5_0 [ 3
* _rtDW -> CoreSubsys [ 0 ] . ForEach_itr_i ] - B_16_2_0_idx ; B_107_13_0_idx
= _rtB -> CoreSubsys [ 0 ] . B_15_5_0 [ 3 * _rtDW -> CoreSubsys [ 0 ] .
ForEach_itr_i + 1 ] - B_16_2_0_idx_0 ; B_107_13_0_idx_1 = _rtB -> CoreSubsys
[ 0 ] . B_15_5_0 [ 3 * _rtDW -> CoreSubsys [ 0 ] . ForEach_itr_i + 2 ] -
B_16_2_0_idx_1 ; B_28_0_0 = ( B_107_13_0_idx_0 * B_19_46_0_idx +
B_107_13_0_idx * tmpForInput_idx ) + B_107_13_0_idx_1 * tmpForInput_idx_0 ;
B_19_46_0_idx_1 = ( B_107_13_0_idx_0 * B_16_1_0_idx + B_107_13_0_idx *
B_16_1_0_idx_0 ) + B_107_13_0_idx_1 * B_16_1_0_idx_1 ; B_107_13_0_idx_0 =
_rtB -> CoreSubsys [ 0 ] . B_15_5_0 [ 3 * _rtDW -> CoreSubsys [ 0 ] .
ForEach_itr_i ] - ( ( B_16_2_0_idx + B_19_46_0_idx ) + B_16_1_0_idx ) ;
B_107_13_0_idx = _rtB -> CoreSubsys [ 0 ] . B_15_5_0 [ 3 * _rtDW ->
CoreSubsys [ 0 ] . ForEach_itr_i + 1 ] - ( ( B_16_2_0_idx_0 + tmpForInput_idx
) + B_16_1_0_idx_0 ) ; B_107_13_0_idx_1 = _rtB -> CoreSubsys [ 0 ] . B_15_5_0
[ 3 * _rtDW -> CoreSubsys [ 0 ] . ForEach_itr_i + 2 ] - ( ( B_16_2_0_idx_1 +
tmpForInput_idx_0 ) + B_16_1_0_idx_1 ) ; B_2_3_0 [ _rtDW -> CoreSubsys [ 0 ]
. ForEach_itr_i ] = ( ( B_28_0_0 < model_AllInOne_rtC ( S ) -> CoreSubsys .
CoreSubsys . B_1_2_0 ) || ( B_19_46_0_idx_1 < model_AllInOne_rtC ( S ) ->
CoreSubsys . CoreSubsys . B_1_5_0 ) || ( ( B_107_13_0_idx_0 * B_19_46_0_idx +
B_107_13_0_idx * tmpForInput_idx ) + B_107_13_0_idx_1 * tmpForInput_idx_0 >
model_AllInOne_rtC ( S ) -> CoreSubsys . CoreSubsys . B_1_10_0 ) || ( (
B_107_13_0_idx_0 * B_16_1_0_idx + B_107_13_0_idx * B_16_1_0_idx_0 ) +
B_107_13_0_idx_1 * B_16_1_0_idx_1 > model_AllInOne_rtC ( S ) -> CoreSubsys .
CoreSubsys . B_1_13_0 ) ) ; _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_gi ++ ;
} _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_g = 0 ; while ( _rtDW ->
CoreSubsys [ 0 ] . ForEach_ivar_g < 768 ) { _rtDW -> CoreSubsys [ 0 ] .
ForEach_itr_d = _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_g ; B_107_13_0_idx_0
= _rtB -> CoreSubsys [ 0 ] . B_15_5_0 [ 3 * _rtDW -> CoreSubsys [ 0 ] .
ForEach_itr_d ] - B_19_1_0 [ 0 ] ; B_107_13_0_idx = _rtB -> CoreSubsys [ 0 ]
. B_15_5_0 [ 3 * _rtDW -> CoreSubsys [ 0 ] . ForEach_itr_d + 1 ] - B_19_1_0 [
1 ] ; B_107_13_0_idx_1 = _rtB -> CoreSubsys [ 0 ] . B_15_5_0 [ 3 * _rtDW ->
CoreSubsys [ 0 ] . ForEach_itr_d + 2 ] - B_19_1_0 [ 2 ] ; B_107_9_0 = (
B_107_13_0_idx_0 * B_107_13_0_idx_0 + B_107_13_0_idx * B_107_13_0_idx ) +
B_107_13_0_idx_1 * B_107_13_0_idx_1 ; if ( ssIsMajorTimeStep ( S ) ) { if (
_rtDW -> CoreSubsys [ 0 ] . CoreSubsys_mn [ _rtDW -> CoreSubsys [ 0 ] .
ForEach_ivar_g + 1 ] . Sqrt_DWORK1 != 0 ) { ssSetSolverNeedsReset ( S ) ;
_rtDW -> CoreSubsys [ 0 ] . CoreSubsys_mn [ _rtDW -> CoreSubsys [ 0 ] .
ForEach_ivar_g + 1 ] . Sqrt_DWORK1 = 0 ; } B_107_9_0 = muDoubleScalarSqrt (
B_107_9_0 ) ; } else { if ( B_107_9_0 < 0.0 ) { B_107_9_0 = -
muDoubleScalarSqrt ( muDoubleScalarAbs ( B_107_9_0 ) ) ; } else { B_107_9_0 =
muDoubleScalarSqrt ( B_107_9_0 ) ; } _rtDW -> CoreSubsys [ 0 ] .
CoreSubsys_mn [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_g + 1 ] .
Sqrt_DWORK1 = 1 ; } _rtB -> CoreSubsys [ 0 ] . B_6_3_0 [ _rtDW -> CoreSubsys
[ 0 ] . ForEach_itr_d ] = B_107_9_0 ; _rtDW -> CoreSubsys [ 0 ] .
ForEach_ivar_g ++ ; } _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_h = 0 ; while
( _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_h < 768 ) { _rtDW -> CoreSubsys [
0 ] . ForEach_itr_h = _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_h ; B_107_9_0
= _rtB -> CoreSubsys [ 0 ] . B_6_3_0 [ _rtDW -> CoreSubsys [ 0 ] .
ForEach_itr_h ] ; B_107_46_0 = ( _rtB -> CoreSubsys [ 0 ] . B_16_9_0 [ 3 *
_rtDW -> CoreSubsys [ 0 ] . ForEach_itr_h + 1 ] * _rtB -> CoreSubsys [ 0 ] .
B_16_9_0 [ 3 * _rtDW -> CoreSubsys [ 0 ] . ForEach_itr_h + 1 ] + _rtB ->
CoreSubsys [ 0 ] . B_16_9_0 [ 3 * _rtDW -> CoreSubsys [ 0 ] . ForEach_itr_h ]
* _rtB -> CoreSubsys [ 0 ] . B_16_9_0 [ 3 * _rtDW -> CoreSubsys [ 0 ] .
ForEach_itr_h ] ) + _rtB -> CoreSubsys [ 0 ] . B_16_9_0 [ 3 * _rtDW ->
CoreSubsys [ 0 ] . ForEach_itr_h + 2 ] * _rtB -> CoreSubsys [ 0 ] . B_16_9_0
[ 3 * _rtDW -> CoreSubsys [ 0 ] . ForEach_itr_h + 2 ] ; if (
ssIsMajorTimeStep ( S ) ) { if ( _rtDW -> CoreSubsys [ 0 ] . CoreSubsys_m [
_rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_h + 1 ] . Sqrt_DWORK1 != 0 ) {
ssSetSolverNeedsReset ( S ) ; _rtDW -> CoreSubsys [ 0 ] . CoreSubsys_m [
_rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_h + 1 ] . Sqrt_DWORK1 = 0 ; }
B_107_46_0 = muDoubleScalarSqrt ( B_107_46_0 ) ; } else { if ( B_107_46_0 <
0.0 ) { B_107_46_0 = - muDoubleScalarSqrt ( muDoubleScalarAbs ( B_107_46_0 )
) ; } else { B_107_46_0 = muDoubleScalarSqrt ( B_107_46_0 ) ; } _rtDW ->
CoreSubsys [ 0 ] . CoreSubsys_m [ _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_h
+ 1 ] . Sqrt_DWORK1 = 1 ; } if ( B_107_9_0 > B_107_46_0 + _rtP -> CoreSubsys
. CoreSubsys_m . P_0 ) { _rtB -> CoreSubsys [ 0 ] . B_4_4_0 [ _rtDW ->
CoreSubsys [ 0 ] . ForEach_itr_h ] = _rtP -> CoreSubsys . CoreSubsys_m . P_1
; } else { _rtB -> CoreSubsys [ 0 ] . B_4_4_0 [ _rtDW -> CoreSubsys [ 0 ] .
ForEach_itr_h ] = B_107_9_0 ; } _rtDW -> CoreSubsys [ 0 ] . ForEach_ivar_h ++
; } for ( i = 0 ; i < 768 ; i ++ ) { if ( B_2_3_0 [ i ] ) { _rtB ->
CoreSubsys [ 0 ] . B_17_4_0 [ i ] = _rtP -> CoreSubsys . P_3 ; } else { _rtB
-> CoreSubsys [ 0 ] . B_17_4_0 [ i ] = _rtB -> CoreSubsys [ 0 ] . B_4_4_0 [ i
] ; } } srUpdateBC ( _rtDW -> CoreSubsys [ 0 ] .
CalculateDistances_SubsysRanBC ) ; break ; } i = _rtDW -> ForEach_itr_b * 3 ;
for ( i_0 = 0 ; i_0 < 768 ; i_0 ++ ) { _rtB -> B_18_3_0 [ i + 375 * i_0 ] =
_rtB -> CoreSubsys [ 0 ] . B_15_5_0 [ 3 * i_0 ] ; _rtB -> B_18_3_0 [ ( i +
375 * i_0 ) + 1 ] = _rtB -> CoreSubsys [ 0 ] . B_15_5_0 [ 3 * i_0 + 1 ] ;
_rtB -> B_18_3_0 [ ( i + 375 * i_0 ) + 2 ] = _rtB -> CoreSubsys [ 0 ] .
B_15_5_0 [ 3 * i_0 + 2 ] ; } memcpy ( & _rtB -> B_18_4_0 [ _rtDW ->
ForEach_itr_b * 768 ] , & _rtB -> CoreSubsys [ 0 ] . B_8_0_1 [ 0 ] , 768U *
sizeof ( real_T ) ) ; memcpy ( & _rtB -> B_18_5_0 [ _rtDW -> ForEach_itr_b *
768 ] , & _rtB -> CoreSubsys [ 0 ] . B_7_0_1 [ 0 ] , 768U * sizeof ( real_T )
) ; for ( i = 0 ; i < 768 ; i ++ ) { _rtB -> B_18_6_0 [ _rtDW ->
ForEach_itr_b + 125 * i ] = _rtB -> CoreSubsys [ 0 ] . B_17_4_0 [ i ] ; }
ssCallAccelCopyCacheForIIS ( S , 18 , ( void * ) 0 ) ; _rtDW ->
ForEach_ivar_k ++ ; } _rtB -> B_19_24_0 = _rtB -> B_18_5_0 [ ( int32_T ) _rtP
-> P_2 ] ; ssCallAccelRunBlock ( S , 19 , 9 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 19 , 10 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_19_12_0
[ 0 ] = _rtB -> B_19_10_0 [ ( int32_T ) _rtP -> P_3 [ 0 ] ] ; _rtB ->
B_19_12_0 [ 1 ] = _rtB -> B_19_10_0 [ ( int32_T ) _rtP -> P_3 [ 1 ] ] ;
ssCallAccelRunBlock ( S , 19 , 13 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_19_24_0
= _rtB -> B_18_4_0 [ ( int32_T ) _rtP -> P_4 ] ; ssCallAccelRunBlock ( S , 19
, 16 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_19_18_0 [ 0 ] = _rtB -> B_19_4_0 [ (
int32_T ) _rtP -> P_5 ] ; _rtB -> B_19_18_0 [ 1 ] = _rtB -> B_19_4_0 [ (
int32_T ) _rtP -> P_5 + 768 ] ; _rtB -> B_19_18_0 [ 2 ] = _rtB -> B_19_4_0 [
( int32_T ) _rtP -> P_5 + 1536 ] ; ssCallAccelRunBlock ( S , 19 , 19 ,
SS_CALL_MDL_OUTPUTS ) ; for ( i = 0 ; i < 3 ; i ++ ) { _rtB -> B_19_28_0 [ i
] = 0.0 ; _rtB -> B_19_28_0 [ i ] += _rtB -> B_107_155_0 [ 3 * i ] * _rtB ->
B_19_18_0 [ 0 ] ; _rtB -> B_19_28_0 [ i ] += _rtB -> B_107_155_0 [ 3 * i + 1
] * _rtB -> B_19_18_0 [ 1 ] ; _rtB -> B_19_28_0 [ i ] += _rtB -> B_107_155_0
[ 3 * i + 2 ] * _rtB -> B_19_18_0 [ 2 ] ; } ssCallAccelRunBlock ( S , 19 , 21
, SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_19_24_0 = _rtB -> B_19_4_0 [ 768 * (
int32_T ) _rtP -> P_7 + ( int32_T ) _rtP -> P_6 ] ; ssCallAccelRunBlock ( S ,
19 , 25 , SS_CALL_MDL_OUTPUTS ) ; for ( i = 0 ; i < 768 ; i ++ ) { _rtB ->
B_19_26_0 [ 3 * i ] = _rtB -> B_18_3_0 [ 375 * i ] ; _rtB -> B_19_26_0 [ 1 +
3 * i ] = _rtB -> B_18_3_0 [ 375 * i + 1 ] ; _rtB -> B_19_26_0 [ 2 + 3 * i ]
= _rtB -> B_18_3_0 [ 375 * i + 2 ] ; } _rtB -> B_19_28_0 [ 0 ] = _rtB ->
B_19_26_0 [ 3 * ( int32_T ) _rtP -> P_8 ] ; _rtB -> B_19_28_0 [ 1 ] = _rtB ->
B_19_26_0 [ 3 * ( int32_T ) _rtP -> P_8 + 1 ] ; _rtB -> B_19_28_0 [ 2 ] =
_rtB -> B_19_26_0 [ 3 * ( int32_T ) _rtP -> P_8 + 2 ] ; ssCallAccelRunBlock (
S , 19 , 29 , SS_CALL_MDL_OUTPUTS ) ; B_28_0_0 = ( _rtP -> P_9 [ 0 ] *
B_19_36_0 [ 3 ] + _rtP -> P_9 [ 1 ] * B_19_36_0 [ 4 ] ) + _rtP -> P_9 [ 2 ] *
B_19_36_0 [ 5 ] ; if ( B_28_0_0 >= 1.0 ) { B_28_0_0 = 1.0 ; } else { if (
B_28_0_0 <= - 1.0 ) { B_28_0_0 = - 1.0 ; } } muDoubleScalarSinCos (
muDoubleScalarAcos ( B_28_0_0 ) / _rtP -> P_10 , & B_107_9_0 , &
B_19_46_0_idx_0 ) ; B_107_13_0_idx_0 = _rtP -> P_9 [ 1 ] * B_19_36_0 [ 5 ] -
_rtP -> P_9 [ 2 ] * B_19_36_0 [ 4 ] ; B_107_13_0_idx = _rtP -> P_9 [ 2 ] *
B_19_36_0 [ 3 ] - _rtP -> P_9 [ 0 ] * B_19_36_0 [ 5 ] ; B_107_13_0_idx_1 =
_rtP -> P_9 [ 0 ] * B_19_36_0 [ 4 ] - _rtP -> P_9 [ 1 ] * B_19_36_0 [ 3 ] ;
B_19_59_0 = ( B_107_13_0_idx_0 * B_107_13_0_idx_0 + B_107_13_0_idx *
B_107_13_0_idx ) + B_107_13_0_idx_1 * B_107_13_0_idx_1 ; if ( B_19_59_0 < 0.0
) { B_19_59_0 = - muDoubleScalarSqrt ( muDoubleScalarAbs ( B_19_59_0 ) ) ; }
else { B_19_59_0 = muDoubleScalarSqrt ( B_19_59_0 ) ; } if ( ! ( B_19_59_0 >
_rtP -> P_12 ) ) { B_107_13_0_idx_0 *= 0.0 ; B_107_13_0_idx *= 0.0 ;
B_107_13_0_idx_1 *= 0.0 ; B_19_59_0 = _rtP -> P_11 ; } B_28_0_0 =
B_107_13_0_idx_0 / B_19_59_0 * B_107_9_0 ; B_19_46_0_idx_1 = B_107_13_0_idx /
B_19_59_0 * B_107_9_0 ; B_19_46_0_idx = B_107_13_0_idx_1 / B_19_59_0 *
B_107_9_0 ; B_19_59_0 = ( ( B_19_46_0_idx_0 * B_19_46_0_idx_0 + B_28_0_0 *
B_28_0_0 ) + B_19_46_0_idx_1 * B_19_46_0_idx_1 ) + B_19_46_0_idx *
B_19_46_0_idx ; if ( ssIsMajorTimeStep ( S ) ) { if ( _rtDW -> sqrt_DWORK1 !=
0 ) { ssSetSolverNeedsReset ( S ) ; _rtDW -> sqrt_DWORK1 = 0 ; } B_19_59_0 =
muDoubleScalarSqrt ( B_19_59_0 ) ; } else { if ( B_19_59_0 < 0.0 ) {
B_19_59_0 = - muDoubleScalarSqrt ( muDoubleScalarAbs ( B_19_59_0 ) ) ; } else
{ B_19_59_0 = muDoubleScalarSqrt ( B_19_59_0 ) ; } _rtDW -> sqrt_DWORK1 = 1 ;
} B_107_9_0 = B_19_46_0_idx_0 / B_19_59_0 ; B_107_46_0 = B_28_0_0 / B_19_59_0
; B_28_0_0 = B_19_46_0_idx_1 / B_19_59_0 ; B_19_59_0 = B_19_46_0_idx /
B_19_59_0 ; _rtB -> B_19_96_0 [ 0 ] = ( ( B_107_9_0 * B_107_9_0 + B_107_46_0
* B_107_46_0 ) - B_28_0_0 * B_28_0_0 ) - B_19_59_0 * B_19_59_0 ; _rtB ->
B_19_96_0 [ 1 ] = ( B_107_46_0 * B_28_0_0 - B_19_59_0 * B_107_9_0 ) * _rtP ->
P_13 ; _rtB -> B_19_96_0 [ 2 ] = ( B_107_9_0 * B_28_0_0 + B_107_46_0 *
B_19_59_0 ) * _rtP -> P_14 ; _rtB -> B_19_96_0 [ 3 ] = ( B_19_59_0 *
B_107_9_0 + B_107_46_0 * B_28_0_0 ) * _rtP -> P_15 ; _rtB -> B_19_96_0 [ 4 ]
= ( ( B_107_9_0 * B_107_9_0 - B_107_46_0 * B_107_46_0 ) + B_28_0_0 * B_28_0_0
) - B_19_59_0 * B_19_59_0 ; _rtB -> B_19_96_0 [ 5 ] = ( B_28_0_0 * B_19_59_0
- B_107_9_0 * B_107_46_0 ) * _rtP -> P_16 ; _rtB -> B_19_96_0 [ 6 ] = (
B_107_46_0 * B_19_59_0 - B_107_9_0 * B_28_0_0 ) * _rtP -> P_17 ; _rtB ->
B_19_96_0 [ 7 ] = ( B_107_9_0 * B_107_46_0 + B_28_0_0 * B_19_59_0 ) * _rtP ->
P_18 ; _rtB -> B_19_96_0 [ 8 ] = ( ( B_107_9_0 * B_107_9_0 - B_107_46_0 *
B_107_46_0 ) - B_28_0_0 * B_28_0_0 ) + B_19_59_0 * B_19_59_0 ;
ssCallAccelRunBlock ( S , 19 , 97 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 19 , 98 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 19 , 99 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_107_231_0 = _rtP -> P_202 ; _rtB ->
B_107_232_0 = _rtP -> P_203 ; } rtPrevAction = _rtDW -> If_ActiveSubsystem_p
; if ( ssIsMajorTimeStep ( S ) ) { if ( _rtB -> B_107_231_0 < 0.0 ) {
rtAction = 0 ; } else { rtAction = 1 ; } _rtDW -> If_ActiveSubsystem_p =
rtAction ; } else { rtAction = _rtDW -> If_ActiveSubsystem_p ; } if (
rtPrevAction != rtAction ) { switch ( rtPrevAction ) { case 0 :
model_AllInOne_NoBO_Disable ( S ) ; break ; case 1 :
model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0 :
if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_232_0 , & B_107_246_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_o . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_246_0 , &
_rtB -> BO_g , & _rtDW -> BO_g , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_g )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_g .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_236_0 = _rtP -> P_204 ; _rtB -> B_107_237_0 = _rtP -> P_205 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_bo ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_236_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_bo = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_bo ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_237_0 , & B_107_247_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_g . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_247_0 , &
_rtB -> BO_e , & _rtDW -> BO_e , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_e )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_e .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_241_0 = _rtP -> P_206 ; _rtB -> B_107_242_0 = _rtP -> P_207 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_ik ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_241_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_ik = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_ik ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_242_0 , & B_107_248_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_j . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_248_0 , &
_rtB -> BO_cr , & _rtDW -> BO_cr , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_cr ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_cr .
BO_SubsysRanBC ) ; } break ; } switch ( ( int32_T ) _rtB -> B_107_25_0 ) {
case 1 : _rtB -> B_107_249_0 = B_107_246_0 ; break ; case 2 : _rtB ->
B_107_249_0 = B_107_248_0 ; break ; default : _rtB -> B_107_249_0 =
B_107_247_0 ; break ; } if ( ssIsSampleHit ( S , 5 , 0 ) ) { for ( i = 0 ; i
< 768 ; i ++ ) { _rtB -> B_107_250_0 [ i ] = ( real32_T ) ( _rtB -> B_19_10_0
[ i ] * _rtB -> B_107_249_0 ) ; } } if ( ssIsSampleHit ( S , 2 , 0 ) ) { for
( i = 0 ; i < 768 ; i ++ ) { _rtB -> B_107_252_0 [ i ] = _rtB -> B_107_250_0
[ i ] - _rtP -> P_272 ; } ssCallAccelRunBlock ( S , 107 , 253 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 107 , 254 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 255 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 256 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 257 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 258 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 4 , 0 ) ) { B_107_259_0_idx
= _rtP -> P_208 [ 0 ] ; B_107_259_0_idx_0 = _rtP -> P_208 [ 1 ] ;
B_107_259_0_idx_1 = _rtP -> P_208 [ 2 ] ; _rtB -> B_107_260_0 [ 0 ] = _rtP ->
P_208 [ 0 ] ; _rtB -> B_107_260_0 [ 1 ] = _rtP -> P_208 [ 1 ] ; _rtB ->
B_107_260_0 [ 2 ] = _rtP -> P_208 [ 2 ] ; _rtB -> B_107_260_0 [ 3 ] = _rtB ->
B_107_45_0 [ 1 ] ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_107_261_0
= _rtP -> P_209 ; } _rtB -> B_107_262_0 = _rtB -> B_107_45_0 [ 1 ] + _rtB ->
B_107_261_0 ; if ( ssIsSampleHit ( S , 4 , 0 ) ) { _rtB -> B_107_263_0 [ 0 ]
= B_107_259_0_idx ; _rtB -> B_107_263_0 [ 1 ] = B_107_259_0_idx_0 ; _rtB ->
B_107_263_0 [ 2 ] = B_107_259_0_idx_1 ; _rtB -> B_107_263_0 [ 3 ] = _rtB ->
B_107_262_0 ; ssCallAccelRunBlock ( S , 107 , 264 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 107 , 265 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 6 , 0 ) ) { ssCallAccelRunBlock ( S , 107 , 266 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 5 , 0 ) ) { for ( i = 0 ;
i < 768 ; i ++ ) { _rtB -> B_107_267_0 [ i ] = _rtB -> B_107_250_0 [ i ] ; }
ssCallAccelRunBlock ( S , 107 , 268 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 107 , 269 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 107 , 270 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 107 , 271 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 107 , 272 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 107 , 273 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 107 , 274 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 107 , 275 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 2 , 0 ) ) { ssCallAccelRunBlock ( S , 107 , 283 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 107 , 284 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 285 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 286 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 287 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 288 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 289 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 290 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 291 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_292_0 = _rtP -> P_210 ; } _rtB -> B_107_293_0 = _rtB -> B_107_143_0 [ 1
] - _rtB -> B_107_292_0 ; B_107_294_0 = ( ( X_model_AllInOne_T * )
ssGetContStates ( S ) ) -> Integrator_CSTATE_k ; B_107_295_0 = ( (
X_model_AllInOne_T * ) ssGetContStates ( S ) ) -> Integrator1_CSTATE ;
B_107_296_0 = ( ( X_model_AllInOne_T * ) ssGetContStates ( S ) ) ->
Integrator2_CSTATE ; _rtB -> B_107_297_0 = _rtP -> P_214 * B_107_338_0 ; _rtB
-> B_107_298_0 = _rtP -> P_215 * B_107_339_0 ; _rtB -> B_107_299_0 = _rtP ->
P_216 * _rtB -> B_107_115_0 ; if ( ssIsMajorTimeStep ( S ) ) { if ( _rtB ->
B_107_115_0 > _rtP -> P_218 ) { _rtDW -> DeadZone_MODE = 1 ; } else if ( _rtB
-> B_107_115_0 >= _rtP -> P_217 ) { _rtDW -> DeadZone_MODE = 0 ; } else {
_rtDW -> DeadZone_MODE = - 1 ; } } if ( _rtDW -> DeadZone_MODE == 1 ) { _rtB
-> B_107_300_0 = _rtB -> B_107_115_0 - _rtP -> P_218 ; } else if ( _rtDW ->
DeadZone_MODE == - 1 ) { _rtB -> B_107_300_0 = _rtB -> B_107_115_0 - _rtP ->
P_217 ; } else { _rtB -> B_107_300_0 = 0.0 ; } if ( ssIsSampleHit ( S , 1 , 0
) ) { if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> NotEqual_Mode = ( _rtB ->
B_107_299_0 != _rtB -> B_107_300_0 ) ; } B_107_301_0 = _rtDW -> NotEqual_Mode
; if ( ssIsMajorTimeStep ( S ) ) { if ( _rtB -> B_107_115_0 > 0.0 ) { _rtDW
-> SignPreSat_MODE = 1 ; } else if ( _rtB -> B_107_115_0 < 0.0 ) { _rtDW ->
SignPreSat_MODE = - 1 ; } else { _rtDW -> SignPreSat_MODE = 0 ; } }
B_107_302_0 = _rtDW -> SignPreSat_MODE ; } _rtB -> B_107_303_0 = _rtP ->
P_219 * B_107_337_0 ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { if (
ssIsMajorTimeStep ( S ) ) { if ( _rtB -> B_107_303_0 > 0.0 ) { _rtDW ->
SignPreIntegrator_MODE = 1 ; } else if ( _rtB -> B_107_303_0 < 0.0 ) { _rtDW
-> SignPreIntegrator_MODE = - 1 ; } else { _rtDW -> SignPreIntegrator_MODE =
0 ; } } _rtB -> B_107_306_0 = ( B_107_301_0 && ( B_107_302_0 == _rtDW ->
SignPreIntegrator_MODE ) ) ; _rtB -> B_107_307_0 = _rtDW ->
Memory_PreviousInput ; } if ( _rtB -> B_107_307_0 ) { _rtB -> B_107_309_0 =
model_AllInOne_rtC ( S ) -> B_107_308_0 ; } else { _rtB -> B_107_309_0 = _rtB
-> B_107_303_0 ; } _rtB -> B_107_310_0 = _rtP -> P_221 * B_107_336_0 ; if (
ssIsSampleHit ( S , 3 , 0 ) ) { ssCallAccelRunBlock ( S , 107 , 311 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 312 ,
SS_CALL_MDL_OUTPUTS ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_313_0 = _rtDW -> NextOutput_mt ; } _rtB -> B_107_314_0 = _rtB ->
B_107_313_0 + _rtB -> B_107_4_0 [ 1 ] ; _rtB -> B_107_325_0 = _rtP -> P_225 *
_rtB -> B_107_314_0 ; ssCallAccelRunBlock ( S , 107 , 316 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 317 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 318 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 319 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 107 , 320 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_321_0 = _rtDW -> NextOutput_op ; } ssCallAccelRunBlock ( S , 107 , 322
, SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_107_325_0 = _rtB -> B_107_321_0 + _rtB ->
B_107_4_0 [ 1 ] ; ssCallAccelRunBlock ( S , 107 , 324 , SS_CALL_MDL_OUTPUTS )
; _rtB -> B_107_325_0 *= _rtP -> P_229 ; ssCallAccelRunBlock ( S , 107 , 326
, SS_CALL_MDL_OUTPUTS ) ; muDoubleScalarSinCos ( _rtB -> B_107_45_0 [ 0 ] , &
B_107_9_0 , & B_107_46_0 ) ; B_107_342_0 [ 0 ] = B_107_9_0 ; B_107_334_0 [ 0
] = B_107_46_0 ; muDoubleScalarSinCos ( _rtB -> B_107_45_0 [ 1 ] , &
B_107_9_0 , & B_107_46_0 ) ; B_107_342_0 [ 1 ] = B_107_9_0 ; B_107_334_0 [ 1
] = B_107_46_0 ; muDoubleScalarSinCos ( _rtB -> B_107_45_0 [ 2 ] , &
B_107_9_0 , & B_107_46_0 ) ; B_107_342_0 [ 2 ] = B_107_9_0 ; B_107_334_0 [ 2
] = B_107_46_0 ; _rtB -> B_107_328_0 = ( _rtB -> B_107_15_0 [ 1 ] *
B_107_342_0 [ 0 ] + _rtB -> B_107_15_0 [ 2 ] * B_107_334_0 [ 0 ] ) * (
B_107_342_0 [ 1 ] / B_107_334_0 [ 1 ] ) + _rtB -> B_107_15_0 [ 0 ] ; _rtB ->
B_107_329_0 = ( _rtB -> B_107_15_0 [ 1 ] * B_107_342_0 [ 0 ] + _rtB ->
B_107_15_0 [ 2 ] * B_107_334_0 [ 0 ] ) / B_107_334_0 [ 1 ] ; _rtB ->
B_107_330_0 = _rtB -> B_107_15_0 [ 1 ] * B_107_334_0 [ 0 ] - _rtB ->
B_107_15_0 [ 2 ] * B_107_342_0 [ 0 ] ; if ( ssIsSampleHit ( S , 1 , 0 ) ) {
for ( i = 0 ; i < 3 ; i ++ ) { _rtB -> B_107_331_0 [ 3 * i ] = B_23_2_0 [ 6 *
i ] ; _rtB -> B_107_331_0 [ 1 + 3 * i ] = B_23_2_0 [ 6 * i + 1 ] ; _rtB ->
B_107_331_0 [ 2 + 3 * i ] = B_23_2_0 [ 6 * i + 2 ] ; } } for ( i = 0 ; i < 3
; i ++ ) { B_107_342_0 [ i ] = _rtB -> B_107_331_0 [ i + 6 ] * _rtB ->
B_107_15_0 [ 2 ] + ( _rtB -> B_107_331_0 [ i + 3 ] * _rtB -> B_107_15_0 [ 1 ]
+ _rtB -> B_107_331_0 [ i ] * _rtB -> B_107_15_0 [ 0 ] ) ; } if (
ssIsSampleHit ( S , 1 , 0 ) ) { for ( i = 0 ; i < 3 ; i ++ ) { _rtB ->
B_107_333_0 [ 3 * i ] = B_23_2_0 [ 6 * i + 3 ] ; _rtB -> B_107_333_0 [ 1 + 3
* i ] = B_23_2_0 [ 6 * i + 4 ] ; _rtB -> B_107_333_0 [ 2 + 3 * i ] = B_23_2_0
[ 6 * i + 5 ] ; } } for ( i = 0 ; i < 3 ; i ++ ) { B_107_334_0 [ i ] = _rtB
-> B_107_333_0 [ i + 6 ] * _rtB -> B_107_15_0 [ 2 ] + ( _rtB -> B_107_333_0 [
i + 3 ] * _rtB -> B_107_15_0 [ 1 ] + _rtB -> B_107_333_0 [ i ] * _rtB ->
B_107_15_0 [ 0 ] ) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 3 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay ; tMinusDelay = ( ( _rtP -> P_230 > 0.0 ) ?
_rtP -> P_230 : 0.0 ) ; tMinusDelay = simTime - tMinusDelay ; B_107_343_0 [ 0
] = model_AllInOne_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , _rtDW -> TransportDelay1_IWORK . CircularBufSize [ 0 ] , & _rtDW
-> TransportDelay1_IWORK . Last [ 0 ] , _rtDW -> TransportDelay1_IWORK . Tail
[ 0 ] , _rtDW -> TransportDelay1_IWORK . Head [ 0 ] , _rtP -> P_231 , 1 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; tBuffer ++ ; uBuffer ++ ; tMinusDelay = ( ( _rtP ->
P_230 > 0.0 ) ? _rtP -> P_230 : 0.0 ) ; tMinusDelay = simTime - tMinusDelay ;
B_107_343_0 [ 1 ] = model_AllInOne_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay1_IWORK .
CircularBufSize [ 1 ] , & _rtDW -> TransportDelay1_IWORK . Last [ 1 ] , _rtDW
-> TransportDelay1_IWORK . Tail [ 1 ] , _rtDW -> TransportDelay1_IWORK . Head
[ 1 ] , _rtP -> P_231 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; tBuffer ++ ; uBuffer ++ ;
tMinusDelay = ( ( _rtP -> P_230 > 0.0 ) ? _rtP -> P_230 : 0.0 ) ; tMinusDelay
= simTime - tMinusDelay ; B_107_343_0 [ 2 ] =
model_AllInOne_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , *
uBuffer , _rtDW -> TransportDelay1_IWORK . CircularBufSize [ 2 ] , & _rtDW ->
TransportDelay1_IWORK . Last [ 2 ] , _rtDW -> TransportDelay1_IWORK . Tail [
2 ] , _rtDW -> TransportDelay1_IWORK . Head [ 2 ] , _rtP -> P_231 , 1 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) ==
ssGetT ( S ) ) ) ) ; } B_107_338_0 = _rtB -> B_107_15_0 [ 0 ] * B_107_342_0 [
1 ] ; B_107_339_0 = _rtB -> B_107_15_0 [ 2 ] * B_107_342_0 [ 1 ] ;
B_107_340_0 = _rtB -> B_107_15_0 [ 0 ] * B_107_342_0 [ 2 ] ; B_107_341_0 =
_rtB -> B_107_15_0 [ 1 ] * B_107_342_0 [ 0 ] ; B_107_343_0 [ 0 ] = (
B_107_343_0 [ 0 ] - B_107_334_0 [ 0 ] ) - ( _rtB -> B_107_15_0 [ 1 ] *
B_107_342_0 [ 2 ] - B_107_339_0 ) ; B_107_343_0 [ 1 ] = ( B_107_343_0 [ 1 ] -
B_107_334_0 [ 1 ] ) - ( _rtB -> B_107_15_0 [ 2 ] * B_107_342_0 [ 0 ] -
B_107_340_0 ) ; B_107_343_0 [ 2 ] = ( B_107_343_0 [ 2 ] - B_107_334_0 [ 2 ] )
- ( B_107_338_0 - B_107_341_0 ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { for (
i = 0 ; i < 3 ; i ++ ) { _rtB -> B_107_344_0 [ 3 * i ] = B_23_2_0 [ 6 * i ] ;
_rtB -> B_107_344_0 [ 1 + 3 * i ] = B_23_2_0 [ 6 * i + 1 ] ; _rtB ->
B_107_344_0 [ 2 + 3 * i ] = B_23_2_0 [ 6 * i + 2 ] ; } }
rt_mrdivide_U1d1x3_U2d3x3_Yd1x3_snf ( B_107_343_0 , _rtB -> B_107_344_0 ,
_rtB -> B_107_345_0 ) ; ssCallAccelRunBlock ( S , 107 , 346 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 2 , 0 ) ) {
ssCallAccelRunBlock ( S , 107 , 347 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 107 , 348 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> B_107_349_0 = _rtP -> P_232 * _rtB ->
B_107_253_3 ; } _rtB -> B_107_350_0 = _rtB -> B_107_349_0 - _rtB ->
B_107_159_0 [ 0 ] ; if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtB -> B_107_351_0
= _rtP -> P_233 * _rtB -> B_107_253_4 ; } _rtB -> B_107_352_0 = _rtB ->
B_107_351_0 - _rtB -> B_107_159_0 [ 2 ] ; if ( ssIsSampleHit ( S , 2 , 0 ) )
{ _rtB -> B_107_353_0 = _rtP -> P_234 * _rtB -> B_107_253_2 ; } _rtB ->
B_107_354_0 = _rtB -> B_107_353_0 - _rtB -> B_107_15_0 [ 1 ] ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_107_355_0 = _rtP -> P_235 ; _rtB ->
B_107_356_0 = _rtP -> P_236 ; _rtB -> B_107_357_0 = _rtP -> P_237 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_pt ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_356_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_pt = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_pt ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_357_0 , & B_107_361_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_g4 . NoBO_SubsysRanBC
) ; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_361_0 , &
_rtB -> BO_m , & _rtDW -> BO_m , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_m )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_m .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_362_0 = _rtP -> P_238 ; _rtB -> B_107_363_0 = _rtP -> P_239 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_e ; if ( ssIsMajorTimeStep ( S ) )
{ if ( _rtB -> B_107_362_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ; }
_rtDW -> If_ActiveSubsystem_e = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_e ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_363_0 , & B_107_367_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_c . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_367_0 , &
_rtB -> BO_eh , & _rtDW -> BO_eh , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_eh ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_eh .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_368_0 = _rtP -> P_240 ; _rtB -> B_107_369_0 = _rtP -> P_241 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_f ; if ( ssIsMajorTimeStep ( S ) )
{ if ( _rtB -> B_107_368_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ; }
_rtDW -> If_ActiveSubsystem_f = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_f ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_369_0 , & B_107_373_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_a . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_373_0 , &
_rtB -> BO_mz , & _rtDW -> BO_mz , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_mz ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_mz .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_374_0 = _rtP -> P_242 ; _rtB -> B_107_375_0 = _rtP -> P_243 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_jy ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_374_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_jy = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_jy ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_375_0 , & B_107_379_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_n . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_379_0 , &
_rtB -> BO_p , & _rtDW -> BO_p , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_p )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_p .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_380_0 = _rtP -> P_244 ; _rtB -> B_107_381_0 = _rtP -> P_245 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_e4 ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_380_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_e4 = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_e4 ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_381_0 , & B_107_385_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_e . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_385_0 , &
_rtB -> BO_o , & _rtDW -> BO_o , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_o )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_o .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_386_0 = _rtP -> P_246 ; _rtB -> B_107_387_0 = _rtP -> P_247 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_pw ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_386_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_pw = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_pw ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_387_0 , & B_107_391_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_le . NoBO_SubsysRanBC
) ; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_391_0 , &
_rtB -> BO_n , & _rtDW -> BO_n , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_n )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_n .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_392_0 = _rtP -> P_248 ; _rtB -> B_107_393_0 = _rtP -> P_249 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_ju ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_392_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_ju = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_ju ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_393_0 , & B_107_397_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_m . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_397_0 , &
_rtB -> BO_i , & _rtDW -> BO_i , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_i )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_i .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_398_0 = _rtP -> P_250 ; _rtB -> B_107_399_0 = _rtP -> P_251 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_ed ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_398_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_ed = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_ed ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_399_0 , & B_107_403_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_ek . NoBO_SubsysRanBC
) ; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_403_0 , &
_rtB -> BO_af , & _rtDW -> BO_af , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_af ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_af .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_404_0 = _rtP -> P_252 ; _rtB -> B_107_405_0 = _rtP -> P_253 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_a ; if ( ssIsMajorTimeStep ( S ) )
{ if ( _rtB -> B_107_404_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ; }
_rtDW -> If_ActiveSubsystem_a = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_a ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_405_0 , & B_107_409_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_ma . NoBO_SubsysRanBC
) ; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_409_0 , &
_rtB -> BO_iu , & _rtDW -> BO_iu , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_iu ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_iu .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_410_0 = _rtP -> P_254 ; _rtB -> B_107_411_0 = _rtP -> P_255 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_h ; if ( ssIsMajorTimeStep ( S ) )
{ if ( _rtB -> B_107_410_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ; }
_rtDW -> If_ActiveSubsystem_h = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_h ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_411_0 , & B_107_415_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_b . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_415_0 , &
_rtB -> BO_h , & _rtDW -> BO_h , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_h )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_h .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_416_0 = _rtP -> P_256 ; _rtB -> B_107_417_0 = _rtP -> P_257 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_k ; if ( ssIsMajorTimeStep ( S ) )
{ if ( _rtB -> B_107_416_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ; }
_rtDW -> If_ActiveSubsystem_k = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_k ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_417_0 , & B_107_421_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_h . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_421_0 , &
_rtB -> BO_j , & _rtDW -> BO_j , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_j )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_j .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_422_0 = _rtP -> P_258 ; _rtB -> B_107_423_0 = _rtP -> P_259 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_ko ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_422_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_ko = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_ko ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_423_0 , & B_107_427_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_nj . NoBO_SubsysRanBC
) ; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_427_0 , &
_rtB -> BO_d , & _rtDW -> BO_d , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_d )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_d .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_428_0 = _rtP -> P_260 ; _rtB -> B_107_429_0 = _rtP -> P_261 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_o ; if ( ssIsMajorTimeStep ( S ) )
{ if ( _rtB -> B_107_428_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ; }
_rtDW -> If_ActiveSubsystem_o = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_o ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_429_0 , & B_107_433_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_k . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_433_0 , &
_rtB -> BO_l , & _rtDW -> BO_l , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_l )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_l .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_434_0 = _rtP -> P_262 ; _rtB -> B_107_435_0 = _rtP -> P_263 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_mi ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_434_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_mi = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_mi ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_435_0 , & B_107_439_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_f . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_439_0 , &
_rtB -> BO_nh , & _rtDW -> BO_nh , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_nh ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_nh .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_440_0 = _rtP -> P_264 ; _rtB -> B_107_441_0 = _rtP -> P_265 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_d ; if ( ssIsMajorTimeStep ( S ) )
{ if ( _rtB -> B_107_440_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ; }
_rtDW -> If_ActiveSubsystem_d = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_d ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_441_0 , & B_107_445_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_d . NoBO_SubsysRanBC )
; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_445_0 , &
_rtB -> BO_db , & _rtDW -> BO_db , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_db ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_db .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_446_0 = _rtP -> P_266 ; _rtB -> B_107_447_0 = _rtP -> P_267 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_ap ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_446_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_ap = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_ap ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_447_0 , & B_107_451_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_jb . NoBO_SubsysRanBC
) ; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_451_0 , &
_rtB -> BO_k , & _rtDW -> BO_k , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_k )
; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_k .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_452_0 = _rtP -> P_268 ; _rtB -> B_107_453_0 = _rtP -> P_269 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_gj ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_452_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_gj = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_gj ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_453_0 , & B_107_457_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_jp . NoBO_SubsysRanBC
) ; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_457_0 , &
_rtB -> BO_no , & _rtDW -> BO_no , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_no ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_no .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_107_458_0 = _rtP -> P_270 ; _rtB -> B_107_459_0 = _rtP -> P_271 ; }
rtPrevAction = _rtDW -> If_ActiveSubsystem_kp ; if ( ssIsMajorTimeStep ( S )
) { if ( _rtB -> B_107_458_0 < 0.0 ) { rtAction = 0 ; } else { rtAction = 1 ;
} _rtDW -> If_ActiveSubsystem_kp = rtAction ; } else { rtAction = _rtDW ->
If_ActiveSubsystem_kp ; } if ( rtPrevAction != rtAction ) { switch (
rtPrevAction ) { case 0 : model_AllInOne_NoBO_Disable ( S ) ; break ; case 1
: model_AllInOne_BO_Disable ( S ) ; break ; } } switch ( rtAction ) { case 0
: if ( rtAction != rtPrevAction ) { model_AllInOne_NoBO_Enable ( S ) ; }
model_AllInOne_NoBO ( _rtB -> B_107_459_0 , & B_107_463_0 ) ; if (
ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> NoBO_eh . NoBO_SubsysRanBC
) ; } break ; case 1 : if ( rtAction != rtPrevAction ) {
model_AllInOne_BO_Enable ( S ) ; } model_AllInOne_BO ( S , & B_107_463_0 , &
_rtB -> BO_ku , & _rtDW -> BO_ku , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_ku ) ; if ( ssIsMajorTimeStep ( S ) ) { srUpdateBC ( _rtDW -> BO_ku .
BO_SubsysRanBC ) ; } break ; } if ( ssIsSampleHit ( S , 3 , 0 ) ) {
ssCallAccelRunBlock ( S , 107 , 464 , SS_CALL_MDL_OUTPUTS ) ; }
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { B_model_AllInOne_T *
_rtB ; P_model_AllInOne_T * _rtP ; DW_model_AllInOne_T * _rtDW ; _rtDW = ( (
DW_model_AllInOne_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ; _rtB = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) ; { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 3
] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head [ 0
] = ( ( _rtDW -> TransportDelay_IWORK . Head [ 0 ] < ( _rtDW ->
TransportDelay_IWORK . CircularBufSize [ 0 ] - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head [ 0 ] + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK . Head [ 0 ] == _rtDW -> TransportDelay_IWORK . Tail [ 0
] ) { if ( ! model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize [ 0 ] , & _rtDW ->
TransportDelay_IWORK . Tail [ 0 ] , & _rtDW -> TransportDelay_IWORK . Head [
0 ] , & _rtDW -> TransportDelay_IWORK . Last [ 0 ] , simTime - _rtP -> P_34 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , FALSE , & _rtDW ->
TransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ++ ) [ _rtDW ->
TransportDelay_IWORK . Head [ 0 ] ] = simTime ; ( * uBuffer ++ ) [ _rtDW ->
TransportDelay_IWORK . Head [ 0 ] ] = ( ( B_model_AllInOne_T * )
_ssGetBlockIO ( S ) ) -> B_107_350_0 ; _rtDW -> TransportDelay_IWORK . Head [
1 ] = ( ( _rtDW -> TransportDelay_IWORK . Head [ 1 ] < ( _rtDW ->
TransportDelay_IWORK . CircularBufSize [ 1 ] - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head [ 1 ] + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK . Head [ 1 ] == _rtDW -> TransportDelay_IWORK . Tail [ 1
] ) { if ( ! model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize [ 1 ] , & _rtDW ->
TransportDelay_IWORK . Tail [ 1 ] , & _rtDW -> TransportDelay_IWORK . Head [
1 ] , & _rtDW -> TransportDelay_IWORK . Last [ 1 ] , simTime - _rtP -> P_34 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , FALSE , & _rtDW ->
TransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ++ ) [ _rtDW ->
TransportDelay_IWORK . Head [ 1 ] ] = simTime ; ( * uBuffer ++ ) [ _rtDW ->
TransportDelay_IWORK . Head [ 1 ] ] = ( ( B_model_AllInOne_T * )
_ssGetBlockIO ( S ) ) -> B_107_347_0 ; _rtDW -> TransportDelay_IWORK . Head [
2 ] = ( ( _rtDW -> TransportDelay_IWORK . Head [ 2 ] < ( _rtDW ->
TransportDelay_IWORK . CircularBufSize [ 2 ] - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head [ 2 ] + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK . Head [ 2 ] == _rtDW -> TransportDelay_IWORK . Tail [ 2
] ) { if ( ! model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize [ 2 ] , & _rtDW ->
TransportDelay_IWORK . Tail [ 2 ] , & _rtDW -> TransportDelay_IWORK . Head [
2 ] , & _rtDW -> TransportDelay_IWORK . Last [ 2 ] , simTime - _rtP -> P_34 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , FALSE , & _rtDW ->
TransportDelay_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head [ 2 ] ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head [ 2 ] ] = ( ( B_model_AllInOne_T * )
_ssGetBlockIO ( S ) ) -> B_107_352_0 ; } if ( ssIsSampleHit ( S , 2 , 0 ) ) {
_rtDW -> UnitDelay1_DSTATE = _rtB -> B_107_253_7 ; } if ( _rtDW ->
If_ActiveSubsystem_b == 1 ) { model_AllInOne_BO_Update ( S , & _rtB -> BO , &
_rtDW -> BO , ( P_BO_model_AllInOne_T * ) & _rtP -> BO ) ; } if ( _rtDW ->
If_ActiveSubsystem_m == 1 ) { model_AllInOne_BO_Update ( S , & _rtB -> BO_a ,
& _rtDW -> BO_a , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_a ) ; } if ( _rtDW
-> If_ActiveSubsystem_i == 1 ) { model_AllInOne_BO_Update ( S , & _rtB ->
BO_c , & _rtDW -> BO_c , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_c ) ; } if
( ssIsSampleHit ( S , 2 , 0 ) ) { _rtDW -> NextOutput =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed ) * _rtP -> P_53 + _rtP ->
P_52 ; _rtDW -> NextOutput_a = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_f ) * _rtP -> P_57 + _rtP -> P_56 ; _rtDW -> NextOutput_g =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_c ) * _rtP -> P_61 + _rtP ->
P_60 ; _rtDW -> NextOutput_f = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_i ) * _rtP -> P_65 + _rtP -> P_64 ; _rtDW -> NextOutput_i =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_o ) * _rtP -> P_69 + _rtP ->
P_68 ; _rtDW -> NextOutput_iq = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_n ) * _rtP -> P_73 + _rtP -> P_72 ; _rtDW -> NextOutput_e =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_k ) * _rtP -> P_77 + _rtP ->
P_76 ; _rtDW -> NextOutput_k = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_b ) * _rtP -> P_81 + _rtP -> P_80 ; _rtDW -> NextOutput_ka =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_cr ) * _rtP -> P_85 + _rtP
-> P_84 ; _rtDW -> NextOutput_a1 = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_g ) * _rtP -> P_89 + _rtP -> P_88 ; _rtDW -> NextOutput_kr =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_h ) * _rtP -> P_93 + _rtP ->
P_92 ; _rtDW -> NextOutput_c = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_nr ) * _rtP -> P_97 + _rtP -> P_96 ; _rtDW -> NextOutput_o =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_l ) * _rtP -> P_101 + _rtP
-> P_100 ; _rtDW -> NextOutput_b = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_fb ) * _rtP -> P_105 + _rtP -> P_104 ; _rtDW -> NextOutput_l =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_p ) * _rtP -> P_109 + _rtP
-> P_108 ; _rtDW -> NextOutput_e0 = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_cm ) * _rtP -> P_113 + _rtP -> P_112 ; _rtDW -> NextOutput_b5 =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_og ) * _rtP -> P_117 + _rtP
-> P_116 ; _rtDW -> NextOutput_ld = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_lr ) * _rtP -> P_121 + _rtP -> P_120 ; _rtDW -> NextOutput_p =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_ct ) * _rtP -> P_125 + _rtP
-> P_124 ; _rtDW -> NextOutput_aj = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_hl ) * _rtP -> P_129 + _rtP -> P_128 ; _rtDW -> NextOutput_bv =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_n1 ) * _rtP -> P_133 + _rtP
-> P_132 ; _rtDW -> NextOutput_m = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_in ) * _rtP -> P_137 + _rtP -> P_136 ; _rtDW -> NextOutput_c0 =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_of ) * _rtP -> P_141 + _rtP
-> P_140 ; _rtDW -> NextOutput_gm = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_d ) * _rtP -> P_145 + _rtP -> P_144 ; } if ( ssIsSampleHit ( S , 2 ,
0 ) ) { _rtDW -> UnitDelay3_DSTATE = _rtB -> B_107_253_8 ; } if (
ssIsSampleHit ( S , 2 , 0 ) ) { _rtDW -> UnitDelay2_DSTATE = _rtB ->
B_107_253_9 ; } if ( _rtDW -> If_ActiveSubsystem_m5 == 0 ) { { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_o . TUbufferPtrs [ 0
] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_o .
TUbufferPtrs [ 6 ] ; real_T simTime = ssGetT ( S ) ; { int_T i1 ; const
real_T * u0 = ( ( B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_29_2_0 ;
int_T * iw_Tail = & _rtDW -> TransportDelay_IWORK_e . Tail [ 0 ] ; int_T *
iw_Head = & _rtDW -> TransportDelay_IWORK_e . Head [ 0 ] ; int_T * iw_Last =
& _rtDW -> TransportDelay_IWORK_e . Last [ 0 ] ; int_T * iw_CircularBufSize =
& _rtDW -> TransportDelay_IWORK_e . CircularBufSize [ 0 ] ; for ( i1 = 0 ; i1
< 6 ; i1 ++ ) { iw_Head [ i1 ] = ( ( iw_Head [ i1 ] < ( iw_CircularBufSize [
i1 ] - 1 ) ) ? ( iw_Head [ i1 ] + 1 ) : 0 ) ; if ( iw_Head [ i1 ] == iw_Tail
[ i1 ] ) { if ( ! model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( &
iw_CircularBufSize [ i1 ] , & iw_Tail [ i1 ] , & iw_Head [ i1 ] , & iw_Last [
i1 ] , simTime - _rtP -> P_25 , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , FALSE , & _rtDW -> TransportDelay_IWORK_e . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ++ ) [ iw_Head [ i1 ] ] = simTime ; ( * uBuffer ++ ) [ iw_Head [ i1 ]
] = u0 [ i1 ] ; } } } } if ( _rtDW -> If_ActiveSubsystem_j == 0 ) { { real_T
* * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_n . TUbufferPtrs
[ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_n
. TUbufferPtrs [ 6 ] ; real_T simTime = ssGetT ( S ) ; { int_T i1 ; const
real_T * u0 = ( ( B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_31_2_0 ;
int_T * iw_Tail = & _rtDW -> TransportDelay_IWORK_a . Tail [ 0 ] ; int_T *
iw_Head = & _rtDW -> TransportDelay_IWORK_a . Head [ 0 ] ; int_T * iw_Last =
& _rtDW -> TransportDelay_IWORK_a . Last [ 0 ] ; int_T * iw_CircularBufSize =
& _rtDW -> TransportDelay_IWORK_a . CircularBufSize [ 0 ] ; for ( i1 = 0 ; i1
< 6 ; i1 ++ ) { iw_Head [ i1 ] = ( ( iw_Head [ i1 ] < ( iw_CircularBufSize [
i1 ] - 1 ) ) ? ( iw_Head [ i1 ] + 1 ) : 0 ) ; if ( iw_Head [ i1 ] == iw_Tail
[ i1 ] ) { if ( ! model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( &
iw_CircularBufSize [ i1 ] , & iw_Tail [ i1 ] , & iw_Head [ i1 ] , & iw_Last [
i1 ] , simTime - _rtP -> P_28 , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , FALSE , & _rtDW -> TransportDelay_IWORK_a . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ++ ) [ iw_Head [ i1 ] ] = simTime ; ( * uBuffer ++ ) [ iw_Head [ i1 ]
] = u0 [ i1 ] ; } } } } if ( _rtDW -> If_ActiveSubsystem_g == 0 ) { { real_T
* * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_p . TUbufferPtrs
[ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_p
. TUbufferPtrs [ 6 ] ; real_T simTime = ssGetT ( S ) ; { int_T i1 ; const
real_T * u0 = ( ( B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_33_2_0 ;
int_T * iw_Tail = & _rtDW -> TransportDelay_IWORK_j . Tail [ 0 ] ; int_T *
iw_Head = & _rtDW -> TransportDelay_IWORK_j . Head [ 0 ] ; int_T * iw_Last =
& _rtDW -> TransportDelay_IWORK_j . Last [ 0 ] ; int_T * iw_CircularBufSize =
& _rtDW -> TransportDelay_IWORK_j . CircularBufSize [ 0 ] ; for ( i1 = 0 ; i1
< 6 ; i1 ++ ) { iw_Head [ i1 ] = ( ( iw_Head [ i1 ] < ( iw_CircularBufSize [
i1 ] - 1 ) ) ? ( iw_Head [ i1 ] + 1 ) : 0 ) ; if ( iw_Head [ i1 ] == iw_Tail
[ i1 ] ) { if ( ! model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( &
iw_CircularBufSize [ i1 ] , & iw_Tail [ i1 ] , & iw_Head [ i1 ] , & iw_Last [
i1 ] , simTime - _rtP -> P_31 , tBuffer , uBuffer , ( NULL ) , ( boolean_T )
0 , FALSE , & _rtDW -> TransportDelay_IWORK_j . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ++ ) [ iw_Head [ i1 ] ] = simTime ; ( * uBuffer ++ ) [ iw_Head [ i1 ]
] = u0 [ i1 ] ; } } } } if ( ssIsSampleHit ( S , 2 , 0 ) ) { _rtDW ->
UnitDelay_DSTATE = _rtB -> B_107_253_6 ; } if ( _rtDW -> If_ActiveSubsystem_p
== 1 ) { model_AllInOne_BO_Update ( S , & _rtB -> BO_g , & _rtDW -> BO_g , (
P_BO_model_AllInOne_T * ) & _rtP -> BO_g ) ; } if ( _rtDW ->
If_ActiveSubsystem_bo == 1 ) { model_AllInOne_BO_Update ( S , & _rtB -> BO_e
, & _rtDW -> BO_e , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_e ) ; } if (
_rtDW -> If_ActiveSubsystem_ik == 1 ) { model_AllInOne_BO_Update ( S , & _rtB
-> BO_cr , & _rtDW -> BO_cr , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_cr ) ;
} if ( ssIsSampleHit ( S , 2 , 0 ) ) { ssCallAccelRunBlock ( S , 107 , 253 ,
SS_CALL_MDL_UPDATE ) ; } if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtDW ->
Memory_PreviousInput = _rtB -> B_107_306_0 ; _rtDW -> NextOutput_mt =
rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW -> RandSeed_o1 ) * _rtP -> P_223 + _rtP
-> P_222 ; _rtDW -> NextOutput_op = rt_nrand_Upu32_Yd_f_pw_snf ( & _rtDW ->
RandSeed_bi ) * _rtP -> P_227 + _rtP -> P_226 ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T *
* tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [
3 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK . Head [
0 ] = ( ( _rtDW -> TransportDelay1_IWORK . Head [ 0 ] < ( _rtDW ->
TransportDelay1_IWORK . CircularBufSize [ 0 ] - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK . Head [ 0 ] + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK . Head [ 0 ] == _rtDW -> TransportDelay1_IWORK . Tail [
0 ] ) { if ( ! model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK . CircularBufSize [ 0 ] , & _rtDW ->
TransportDelay1_IWORK . Tail [ 0 ] , & _rtDW -> TransportDelay1_IWORK . Head
[ 0 ] , & _rtDW -> TransportDelay1_IWORK . Last [ 0 ] , simTime - _rtP ->
P_230 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , FALSE , & _rtDW ->
TransportDelay1_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ++ ) [ _rtDW ->
TransportDelay1_IWORK . Head [ 0 ] ] = simTime ; ( * uBuffer ++ ) [ _rtDW ->
TransportDelay1_IWORK . Head [ 0 ] ] = ( ( B_model_AllInOne_T * )
_ssGetBlockIO ( S ) ) -> B_107_355_0 ; _rtDW -> TransportDelay1_IWORK . Head
[ 1 ] = ( ( _rtDW -> TransportDelay1_IWORK . Head [ 1 ] < ( _rtDW ->
TransportDelay1_IWORK . CircularBufSize [ 1 ] - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK . Head [ 1 ] + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK . Head [ 1 ] == _rtDW -> TransportDelay1_IWORK . Tail [
1 ] ) { if ( ! model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK . CircularBufSize [ 1 ] , & _rtDW ->
TransportDelay1_IWORK . Tail [ 1 ] , & _rtDW -> TransportDelay1_IWORK . Head
[ 1 ] , & _rtDW -> TransportDelay1_IWORK . Last [ 1 ] , simTime - _rtP ->
P_230 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , FALSE , & _rtDW ->
TransportDelay1_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ++ ) [ _rtDW ->
TransportDelay1_IWORK . Head [ 1 ] ] = simTime ; ( * uBuffer ++ ) [ _rtDW ->
TransportDelay1_IWORK . Head [ 1 ] ] = ( ( B_model_AllInOne_T * )
_ssGetBlockIO ( S ) ) -> B_107_354_0 ; _rtDW -> TransportDelay1_IWORK . Head
[ 2 ] = ( ( _rtDW -> TransportDelay1_IWORK . Head [ 2 ] < ( _rtDW ->
TransportDelay1_IWORK . CircularBufSize [ 2 ] - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK . Head [ 2 ] + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK . Head [ 2 ] == _rtDW -> TransportDelay1_IWORK . Tail [
2 ] ) { if ( ! model_AllInOne_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK . CircularBufSize [ 2 ] , & _rtDW ->
TransportDelay1_IWORK . Tail [ 2 ] , & _rtDW -> TransportDelay1_IWORK . Head
[ 2 ] , & _rtDW -> TransportDelay1_IWORK . Last [ 2 ] , simTime - _rtP ->
P_230 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , FALSE , & _rtDW ->
TransportDelay1_IWORK . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ _rtDW ->
TransportDelay1_IWORK . Head [ 2 ] ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK . Head [ 2 ] ] = ( ( B_model_AllInOne_T * )
_ssGetBlockIO ( S ) ) -> B_107_355_0 ; } if ( _rtDW -> If_ActiveSubsystem_pt
== 1 ) { model_AllInOne_BO_Update ( S , & _rtB -> BO_m , & _rtDW -> BO_m , (
P_BO_model_AllInOne_T * ) & _rtP -> BO_m ) ; } if ( _rtDW ->
If_ActiveSubsystem_e == 1 ) { model_AllInOne_BO_Update ( S , & _rtB -> BO_eh
, & _rtDW -> BO_eh , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_eh ) ; } if (
_rtDW -> If_ActiveSubsystem_f == 1 ) { model_AllInOne_BO_Update ( S , & _rtB
-> BO_mz , & _rtDW -> BO_mz , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_mz ) ;
} if ( _rtDW -> If_ActiveSubsystem_jy == 1 ) { model_AllInOne_BO_Update ( S ,
& _rtB -> BO_p , & _rtDW -> BO_p , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_p
) ; } if ( _rtDW -> If_ActiveSubsystem_e4 == 1 ) { model_AllInOne_BO_Update (
S , & _rtB -> BO_o , & _rtDW -> BO_o , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_o ) ; } if ( _rtDW -> If_ActiveSubsystem_pw == 1 ) {
model_AllInOne_BO_Update ( S , & _rtB -> BO_n , & _rtDW -> BO_n , (
P_BO_model_AllInOne_T * ) & _rtP -> BO_n ) ; } if ( _rtDW ->
If_ActiveSubsystem_ju == 1 ) { model_AllInOne_BO_Update ( S , & _rtB -> BO_i
, & _rtDW -> BO_i , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_i ) ; } if (
_rtDW -> If_ActiveSubsystem_ed == 1 ) { model_AllInOne_BO_Update ( S , & _rtB
-> BO_af , & _rtDW -> BO_af , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_af ) ;
} if ( _rtDW -> If_ActiveSubsystem_a == 1 ) { model_AllInOne_BO_Update ( S ,
& _rtB -> BO_iu , & _rtDW -> BO_iu , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_iu ) ; } if ( _rtDW -> If_ActiveSubsystem_h == 1 ) {
model_AllInOne_BO_Update ( S , & _rtB -> BO_h , & _rtDW -> BO_h , (
P_BO_model_AllInOne_T * ) & _rtP -> BO_h ) ; } if ( _rtDW ->
If_ActiveSubsystem_k == 1 ) { model_AllInOne_BO_Update ( S , & _rtB -> BO_j ,
& _rtDW -> BO_j , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_j ) ; } if ( _rtDW
-> If_ActiveSubsystem_ko == 1 ) { model_AllInOne_BO_Update ( S , & _rtB ->
BO_d , & _rtDW -> BO_d , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_d ) ; } if
( _rtDW -> If_ActiveSubsystem_o == 1 ) { model_AllInOne_BO_Update ( S , &
_rtB -> BO_l , & _rtDW -> BO_l , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_l )
; } if ( _rtDW -> If_ActiveSubsystem_mi == 1 ) { model_AllInOne_BO_Update ( S
, & _rtB -> BO_nh , & _rtDW -> BO_nh , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_nh ) ; } if ( _rtDW -> If_ActiveSubsystem_d == 1 ) {
model_AllInOne_BO_Update ( S , & _rtB -> BO_db , & _rtDW -> BO_db , (
P_BO_model_AllInOne_T * ) & _rtP -> BO_db ) ; } if ( _rtDW ->
If_ActiveSubsystem_ap == 1 ) { model_AllInOne_BO_Update ( S , & _rtB -> BO_k
, & _rtDW -> BO_k , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_k ) ; } if (
_rtDW -> If_ActiveSubsystem_gj == 1 ) { model_AllInOne_BO_Update ( S , & _rtB
-> BO_no , & _rtDW -> BO_no , ( P_BO_model_AllInOne_T * ) & _rtP -> BO_no ) ;
} if ( _rtDW -> If_ActiveSubsystem_kp == 1 ) { model_AllInOne_BO_Update ( S ,
& _rtB -> BO_ku , & _rtDW -> BO_ku , ( P_BO_model_AllInOne_T * ) & _rtP ->
BO_ku ) ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_model_AllInOne_T * _rtB ;
P_model_AllInOne_T * _rtP ; _rtP = ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) ; _rtB = ( ( B_model_AllInOne_T * ) _ssGetBlockIO (
S ) ) ; { ( ( XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> xeyeze_CSTATE [ 0
] = ( ( B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_157_0 [ 0 ] ; (
( XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> xeyeze_CSTATE [ 1 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_157_0 [ 1 ] ; ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> xeyeze_CSTATE [ 2 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_157_0 [ 2 ] ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> ubvbwb_CSTATE [ 0 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_23_0 [ 0 ] ; ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> ubvbwb_CSTATE [ 1 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_23_0 [ 1 ] ; ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> ubvbwb_CSTATE [ 2 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_23_0 [ 2 ] ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> pqr_CSTATE [ 0 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_345_0 [ 0 ] ; ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> pqr_CSTATE [ 1 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_345_0 [ 1 ] ; ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> pqr_CSTATE [ 2 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_345_0 [ 2 ] ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> phithetapsi_CSTATE [ 0 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_328_0 ; ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> phithetapsi_CSTATE [ 1 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_330_0 ; ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> phithetapsi_CSTATE [ 2 ] = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_329_0 ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Integrator_CSTATE = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_309_0 ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Filter_CSTATE = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_114_0 ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Integrator_CSTATE_j = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_297_0 ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Filter_CSTATE_k = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_125_0 ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Integrator_CSTATE_a = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_298_0 ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Filter_CSTATE_e = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_135_0 ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Integrator_CSTATE_h = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_310_0 ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Filter_CSTATE_n = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_226_0 ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Integrator_CSTATE_k = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_143_0 [ 0 ] ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Integrator1_CSTATE = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_293_0 ; } { ( (
XDot_model_AllInOne_T * ) ssGetdX ( S ) ) -> Integrator2_CSTATE = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) -> B_107_143_0 [ 2 ] ; } }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_model_AllInOne_T * _rtB ;
P_model_AllInOne_T * _rtP ; ZCV_model_AllInOne_T * _rtZCSV ; _rtZCSV = ( (
ZCV_model_AllInOne_T * ) ssGetSolverZcSignalVector ( S ) ) ; _rtP = ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ; _rtB = ( (
B_model_AllInOne_T * ) _ssGetBlockIO ( S ) ) ; _rtZCSV -> If_IfInput_ZC = 0.0
; if ( _rtB -> B_107_4_0 [ 1 ] > 0.12 ) { _rtZCSV -> If_IfInput_ZC = 1.0 ; }
{ ( ( ZCV_model_AllInOne_T * ) ssGetSolverZcSignalVector ( S ) ) ->
If2_IfInput_ZC = 0.0 ; } if ( ( ( DW_model_AllInOne_T * ) ssGetRootDWork ( S
) ) -> If_ActiveSubsystem == 1 ) { _rtZCSV -> If2_IfInput_ZC = 0.0 ; if (
_rtB -> B_27_4_0 > 0.0 ) { _rtZCSV -> If2_IfInput_ZC = 1.0 ; } } _rtZCSV ->
Saturation_UprLim_ZC = _rtB -> B_107_115_0 - _rtP -> P_157 ; _rtZCSV ->
Saturation_LwrLim_ZC = _rtB -> B_107_115_0 - _rtP -> P_158 ; _rtZCSV ->
Saturation_UprLim_ZC_j = _rtB -> B_107_126_0 - _rtP -> P_166 ; _rtZCSV ->
Saturation_LwrLim_ZC_n = _rtB -> B_107_126_0 - _rtP -> P_167 ; _rtZCSV ->
Saturation_UprLim_ZC_f = _rtB -> B_107_136_0 - _rtP -> P_174 ; _rtZCSV ->
Saturation_LwrLim_ZC_d = _rtB -> B_107_136_0 - _rtP -> P_175 ; _rtZCSV ->
DeadZone_LwrReg_ZC = _rtB -> B_107_115_0 - _rtP -> P_217 ; _rtZCSV ->
DeadZone_UprReg_ZC = _rtB -> B_107_115_0 - _rtP -> P_218 ; _rtZCSV ->
NotEqual_RelopInput_ZC = _rtB -> B_107_299_0 - _rtB -> B_107_300_0 ; _rtZCSV
-> SignPreSat_Input_ZC = _rtB -> B_107_115_0 ; _rtZCSV ->
SignPreIntegrator_Input_ZC = _rtB -> B_107_303_0 ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 837777582U
) ; ssSetChecksumVal ( S , 1 , 3052918977U ) ; ssSetChecksumVal ( S , 2 ,
1724807755U ) ; ssSetChecksumVal ( S , 3 , 2853961938U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "8.1" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_model_AllInOne_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_model_AllInOne_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_model_AllInOne_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & model_AllInOne_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
model_AllInOne_rtInvariant ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys_n . CoreSubsys
. CoreSubsys . P_3 [ 0 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys_n . CoreSubsys . CoreSubsys . P_3 [ 1
] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys_n . CoreSubsys . CoreSubsys . P_3 [ 2 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys_n . CoreSubsys
. CoreSubsys . P_5 [ 0 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys_n . CoreSubsys . CoreSubsys . P_5 [ 1
] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys_n . CoreSubsys . CoreSubsys . P_5 [ 2 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 0 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 1 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 2 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam
( S ) ) -> CoreSubsys . P_1 [ 3 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 4 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 5 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 6 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 7 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam
( S ) ) -> CoreSubsys . P_1 [ 8 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 9 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 10 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 11 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 12 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 13 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 14 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 15 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 16 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 17 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 18 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 19 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 20 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 21 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 22 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 23 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 24 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 25 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 26 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 27 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 28 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 29 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 30 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 31 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 32 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 33 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 34 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 35 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 36 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 37 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 38 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 39 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 40 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 41 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 42 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 43 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 44 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 45 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 46 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 47 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 48 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 49 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 50 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 51 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 52 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 53 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 54 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 55 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 56 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 57 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 58 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 59 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 60 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 61 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 62 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 63 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 64 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 65 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 66 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 67 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 68 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 69 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 70 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 71 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 72 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 73 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 74 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 75 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 76 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 77 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 78 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 79 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 80 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 81 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 82 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 83 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 84 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 85 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 86 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 87 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 88 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 89 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 90 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 91 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 92 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 93 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 94 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 95 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 96 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 97 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 98 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
P_1 [ 99 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) ->
CoreSubsys . P_1 [ 100 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 101 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 102 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 103 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 104 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 105 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 106 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 107 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 108 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 109 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 110 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 111 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 112 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 113 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 114 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 115 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 116 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 117 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 118 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 119 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 120 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 121 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 122 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 123 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 124 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 125 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 126 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 127 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 128 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 129 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 130 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 131 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 132 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 133 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 134 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 135 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 136 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 137 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 138 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 139 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 140 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 141 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 142 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 143 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 144 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 145 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 146 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 147 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 148 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 149 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 150 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 151 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 152 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 153 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 154 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 155 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 156 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 157 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 158 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 159 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 160 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 161 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 162 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 163 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 164 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 165 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 166 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 167 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 168 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 169 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 170 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 171 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 172 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 173 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 174 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 175 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 176 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 177 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 178 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 179 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 180 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 181 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 182 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 183 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 184 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 185 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 186 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 187 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 188 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 189 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 190 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 191 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 192 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 193 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 194 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 195 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 196 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 197 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 198 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 199 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 200 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 201 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 202 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 203 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 204 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 205 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 206 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 207 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 208 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 209 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 210 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 211 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 212 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 213 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 214 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 215 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 216 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 217 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 218 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 219 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 220 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 221 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 222 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 223 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 224 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 225 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 226 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 227 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 228 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 229 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 230 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 231 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 232 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 233 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 234 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 235 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 236 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 237 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 238 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 239 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 240 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 241 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 242 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 243 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 244 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 245 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 246 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 247 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 248 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 249 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 250 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 251 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 252 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 253 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 254 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 255 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 256 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 257 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 258 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 259 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 260 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 261 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 262 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 263 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 264 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 265 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 266 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 267 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 268 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 269 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 270 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 271 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 272 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 273 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 274 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 275 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 276 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 277 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 278 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 279 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 280 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 281 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 282 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 283 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 284 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 285 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 286 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 287 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 288 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 289 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 290 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 291 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 292 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 293 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 294 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 295 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 296 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 297 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 298 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 299 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 300 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 301 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 302 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 303 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 304 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 305 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 306 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 307 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 308 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 309 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 310 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 311 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 312 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 313 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 314 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 315 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 316 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 317 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 318 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 319 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 320 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 321 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 322 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 323 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 324 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 325 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 326 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 327 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 328 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 329 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 330 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 331 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 332 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 333 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 334 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 335 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 336 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 337 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 338 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 339 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 340 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 341 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 342 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 343 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 344 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 345 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 346 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 347 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 348 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 349 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 350 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 351 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 352 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 353 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 354 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 355 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 356 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 357 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 358 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 359 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 360 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 361 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 362 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 363 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 364 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 365 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 366 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 367 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 368 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 369 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 370 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 371 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 372 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 373 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 374 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 375 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 376 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 377 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 378 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 379 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 380 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 381 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 382 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 383 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 384 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 385 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 386 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 387 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 388 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 389 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 390 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 391 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 392 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 393 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 394 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 395 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 396 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 397 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 398 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 399 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 400 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 401 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 402 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 403 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 404 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 405 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 406 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 407 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 408 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 409 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 410 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 411 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 412 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 413 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 414 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 415 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 416 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 417 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 418 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 419 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 420 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 421 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 422 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 423 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 424 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 425 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 426 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 427 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 428 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 429 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 430 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 431 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 432 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 433 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 434 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 435 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 436 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 437 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 438 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 439 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 440 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 441 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 442 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 443 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 444 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 445 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 446 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 447 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 448 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 449 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 450 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 451 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 452 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 453 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 454 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 455 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 456 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 457 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 458 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 459 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 460 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 461 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 462 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 463 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 464 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 465 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 466 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 467 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 468 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 469 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 470 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 471 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 472 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 473 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 474 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 475 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 476 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 477 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 478 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 479 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 480 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 481 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 482 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 483 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 484 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 485 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 486 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 487 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 488 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 489 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 490 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 491 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 492 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 493 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 494 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 495 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 496 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 497 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 498 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 499 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 500 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 501 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 502 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 503 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 504 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 505 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 506 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 507 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 508 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 509 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 510 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 511 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 512 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 513 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 514 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 515 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 516 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 517 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 518 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 519 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 520 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 521 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 522 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 523 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 524 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 525 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 526 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 527 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 528 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 529 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 530 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 531 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 532 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 533 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 534 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 535 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 536 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 537 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 538 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 539 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 540 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 541 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 542 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 543 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 544 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 545 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 546 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 547 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 548 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 549 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 550 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 551 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 552 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 553 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 554 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 555 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 556 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 557 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 558 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 559 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 560 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 561 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 562 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 563 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 564 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 565 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 566 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 567 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 568 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 569 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 570 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 571 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 572 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 573 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 574 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 575 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 576 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 577 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 578 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 579 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 580 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 581 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 582 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 583 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 584 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 585 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 586 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 587 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 588 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 589 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 590 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 591 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 592 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 593 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 594 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 595 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 596 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 597 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 598 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 599 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 600 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 601 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 602 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 603 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 604 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 605 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 606 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 607 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 608 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 609 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 610 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 611 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 612 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 613 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 614 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 615 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 616 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 617 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 618 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 619 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 620 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 621 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 622 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 623 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 624 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 625 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 626 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 627 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 628 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 629 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 630 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 631 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 632 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 633 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 634 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 635 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 636 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 637 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 638 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 639 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 640 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 641 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 642 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 643 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 644 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 645 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 646 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 647 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 648 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 649 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 650 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 651 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 652 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 653 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 654 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 655 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 656 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 657 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 658 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 659 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 660 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 661 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 662 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 663 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 664 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 665 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 666 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 667 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 668 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 669 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 670 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 671 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 672 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 673 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 674 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 675 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 676 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 677 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 678 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 679 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 680 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 681 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 682 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 683 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 684 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 685 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 686 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 687 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 688 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 689 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 690 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 691 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 692 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 693 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 694 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 695 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 696 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 697 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 698 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 699 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 700 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 701 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 702 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 703 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 704 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 705 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 706 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 707 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 708 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 709 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 710 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 711 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 712 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 713 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 714 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 715 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 716 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 717 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 718 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 719 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 720 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 721 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 722 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 723 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 724 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 725 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 726 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 727 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 728 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 729 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 730 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 731 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 732 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 733 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 734 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 735 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 736 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 737 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 738 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 739 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 740 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 741 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 742 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 743 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 744 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 745 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 746 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 747 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 748 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 749 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 750 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 751 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 752 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 753 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 754 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 755 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 756 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 757 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 758 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 759 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 760 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 761 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 762 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 763 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . P_1 [ 764 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 765 ] = rtInf ; ( (
P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys . P_1 [ 766 ]
= rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys
. P_1 [ 767 ] = rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) )
-> CoreSubsys . CoreSubsys_mn2 . P_3 [ 0 ] = rtInf ; ( ( P_model_AllInOne_T *
) ssGetDefaultParam ( S ) ) -> CoreSubsys . CoreSubsys_mn2 . P_3 [ 1 ] =
rtInf ; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
CoreSubsys_mn2 . P_3 [ 2 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . CoreSubsys_mn2 . P_5 [ 0 ] = rtInf
; ( ( P_model_AllInOne_T * ) ssGetDefaultParam ( S ) ) -> CoreSubsys .
CoreSubsys_mn2 . P_5 [ 1 ] = rtInf ; ( ( P_model_AllInOne_T * )
ssGetDefaultParam ( S ) ) -> CoreSubsys . CoreSubsys_mn2 . P_5 [ 2 ] = rtInf
; } static void mdlInitializeSampleTimes ( SimStruct * S ) { { SimStruct *
childS ; SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S , 0 ) ;
callSysFcns = ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ]
= ( SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 1 ) ; callSysFcns
= ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 3 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 4 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; } } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
