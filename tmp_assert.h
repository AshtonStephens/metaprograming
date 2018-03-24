/* 
 * tmp_assert.h
 * 
 * Error checking code
 */

#ifndef TMP_ASSERT_H
#define TMP_ASSERT_H

//  TMP_Error <typename>
// 
//  Will create a compile error if the result value within a 
//  struct gets set to this value
//
template <typename T>
struct TMP_Error {
    // Do not set this value - it is for terminating
    // faulty code that does not meet the function 
    // contracts for the following TMP functions~
    static const T result; 
};

//  TMP_Assert...
// 
//  Each of the following will check an assertion
//  and make a compile error something is wrong.
// 
//  the following are examples of their use:
//
//  // returns 1 because 1 <= 2
//  TMP_AssertLessThanOrEqualTo <unsigned int, 1, 2>::result;
//
//  // returns creates an error during compile because -4 
//  // is not greater than 7
//  TMP_AssertGreater <int, -4, 7>::result; 
//
template <typename T, T N, T Compare>
struct TMP_AssertEqualTo
{
    static const T result = 
        N == Compare ? N : TMP_Error<T>::result; 
};

template <typename T, T N, T Compare>
struct TMP_AssertNotEqualTo
{
    static const T result = 
        N != Compare ? N : TMP_Error<T>::result; 
};

template <typename T, T N, T Compare>
struct TMP_AssertLessThan 
{
    static const T result = 
        N < Compare ? N : TMP_Error<T>::result; 
};

template <typename T, T N, T Compare>
struct TMP_AssertLessThanOrEqualTo
{
    static const T result = 
        N <= Compare ? N : TMP_Error<T>::result; 
};

template <typename T, T N, T Compare>
struct TMP_AssertGreater 
{
    static const T result = 
        N > Compare ? N : TMP_Error<T>::result; 
};

template <typename T, T N, T Compare>
struct TMP_AssertGreaterOrEqualTo
{
    static const T result = 
        N > Compare ? N : TMP_Error<T>::result; 
};

#endif
