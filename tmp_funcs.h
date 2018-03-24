/* 
 * tmp_funcs.h
 *
 * template meta programming compile time scripts to 
 * generate fast code
 */
#include "tmp_assert.h"

#ifndef TMP_FUNCS_H
#define TMP_FUNCS_H

/* 
 *  TMP_Power
 *      Performs a power operation during compile time.
 *
 *  Example:
 *      TMP_Power <2, 5>::result = 5;
 */
/* -------------------------------------------------------- */
template <unsigned int power, unsigned int powers_left>
struct TMP_Power {
    static const unsigned int result = 
        power * TMP_Power <power, powers_left-1>::result;
};

template <unsigned int power>
struct TMP_Power <power, 0> 
{
    static const unsigned int result = 1;
};

/*
 *  TMP_LogBase 
 *      Performs a log operation during compile time
 *  
 *  Example:
 *      TMP_LogBase <2,32> = 5    
 * 
 *  Secial Cases:
 *      TMP_LogBase <1,1> = 0 
 *      TMP_LogBase <0,1> = Error 
 */
/* -------------------------------------------------------- */
template <unsigned int Base, unsigned int A>
struct TMP_LogBase_HIDDEN
{
    static const unsigned int result = 
        1 + TMP_LogBase_HIDDEN<Base, A / Base>::result;
};

template <unsigned int Base>
struct TMP_LogBase_HIDDEN <Base, 1>
{
    static const unsigned int result = 0;
};

//  Rejects bad inputs without infinite recursion to prevent
//  crazy and untraceable errors - especially if you're abusing 
//  templates elsewhere.
//
template <unsigned int Base, unsigned int A>
struct TMP_LogBase
{
    static const unsigned int result =
        TMP_LogBase_HIDDEN <
            TMP_AssertGreater<unsigned int,Base, 1>::result, 
            TMP_AssertGreater<unsigned int,A, 0>::result
        >::result;
};

//
//  TMP_LogBase <Base, 1>
//
//  Handles special cases
//      TMP_LogBase<1, 1> = 0;
//      TMP_LogBase<0, 1> = Compile Error;
//
template <unsigned int Base>
struct TMP_LogBase <Base, 1> 
{
    static const unsigned int result = TMP_LogBase_HIDDEN<
        TMP_AssertGreater<unsigned int, Base, 0>::result, 1>::result;
};

#ifdef  TMP_LogBase_HIDDEN
#undef  TMP_LogBase_HIDDEN
#endif
#define TMP_LogBase_HIDDEN @invalid_struct

/*
 *  TMP_NextPowOf2
 *      Returns the next power of 2
 *
 *  Example:
 *      TMP_NextPowOf2 <11> = 16;
 *  
 *  Special Cases(?):
 *      TMP_NextPowOf2 <1> = 1;
 *      TMP_NextPowOf2 <0> = 0;
 */
/* -------------------------------------------------------- */
template <unsigned int A>
struct TMP_NextPowOf2 
{
    static const unsigned int result 
        = TMP_Power<2,(TMP_LogBase<2,A-1>::result)>::result*2;
};

template <>
struct TMP_NextPowOf2 <1> 
{
    static const unsigned int result = 0;
};

template <>
struct TMP_NextPowOf2 <0> 
{
    static const unsigned int result = 1;
};

template <int A, int B>
struct TMP_LargerOf 
{
    static const unsigned int result = A > B ? A : B;   
};

#endif

