/**
 *  constants.h
 *
 *
 *  Copywrite 2018, 2019, 2020, 2021, 2022, 2023, 2024, 2025  Quantum Galaxies Corporation,
 *   and methods patented by Texas Tech University.
 *  We acknowledge the generous support of Texas Tech University,
 *  The Robert A. Welch Foundation, and the Army Research Office.
 *
 
 *  MIT License
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include "system.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

#ifdef APPLE
#include "Accelerate/Accelerate.h"
#include "complex.h"
typedef double __complex__ DCOMPLEX;
typedef __CLPK_integer  inta;
typedef __CLPK_doublereal floata;
typedef unsigned long ADDRESS_TYPE;
#else

typedef double floata;

#ifdef  OMP
#include "omp.h"
#endif

#ifdef GSL_LIB
///May not need all of these,
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_sum.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_vegas.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_sf_zeta.h>
#include <gsl/gsl_sf_hyperg.h>
#include <gsl/gsl_sf_gamma.h>
#endif

#ifdef MKL
#include "mkl.h"
#include "mkl_lapacke.h"
#include "mkl_types.h"
typedef MKL_INT inta;
typedef MKL_INT ADDRESS_TYPE;
typedef double __complex__ DCOMPLEX;
typedef MKL_Complex16 DCOMPLEX_PRIME;
#endif

// #ifdef ATLAS
// #include "cblas-atlas.h"
// #define LAPACK_COL_MAJOR 102
// #else
// #include "cblas.h"
// #endif

// #ifdef LAPACKE
// #include "lapacke.h"
// //#include "lapacke_utils.h"
// #endif

#ifdef GSL_CBLAS
#include "gsl/gsl_blas.h"
#endif

#ifdef BIT_INT
typedef long long int ADDRESS_TYPE;
typedef int inta;
typedef double __complex__ DCOMPLEX;
typedef double __complex__ DCOMPLEX_PRIME;
#endif

#endif

#include "complex.h"

#ifdef BIT_LONG
typedef long long int ADDRESS_TYPE;
#define lapack_int long int
typedef lapack_int inta;
typedef double __complex__ DCOMPLEX;
typedef double __complex__ DCOMPLEX_PRIME;
#endif

#ifdef COMPLEX_ME
typedef DCOMPLEX mea;
#else
typedef double mea;
#endif

typedef char* stringa;
#endif




