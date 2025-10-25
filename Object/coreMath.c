/**
 *  coreMath.c
 *
 *
 *  Copywrite 2018, 2019, 2020, 2021, 2022, 2023, 2024, 2025  Quantum Galaxies Corporation,
 *   and methods patented by Texas Tech University.
 *  We acknowledge the generous support of Texas Tech University,
 *  The Robert A. Welch Foundation, and the Army Research Office.
 *
 
 *  MIT License
*/

#include "coreMath.h"
///have not bothered to put this in a better spot because its double loading
#undef __cplusplus
#ifndef FADDEEVA
#include "../Faddeeva/Faddeeva.cc"
#endif

/**
 * Center of the magic, Faddeeva routines
 */
DCOMPLEX expErf ( DCOMPLEX z ){
    DCOMPLEX w;
    w = Faddeeva_w(z*I,1e-15);
    return cexp(-(cimag(z)*cimag(z))) - cexp(-(creal(z)*creal(z))-2.*I*creal(z)*cimag(z)) *w;
};

/*
 *Old fashion made new
 * GTOs
 * GaussianInSinc = < (x-y)^n Exp[-alpha (x-y)^2] *normalization | X > < X | Sinc >
 *
 */
floata GaussianInSinc( floata K, inta n, floata alpha, floata y, floata X ){
    floata sspi = sqrt(sqrt(pi/2./alpha));
    floata spi = sqrt(pi);
    floata sa   = sqrt(alpha);
    X -= y;
    floata erfBase = sa * ( expErf(( K - 2. * I * X * alpha )/(2.*sa))+expErf(( K + 2. * I * X * alpha )/(2.*sa)) );
    if ( n == 0 )
        ///S
        return (erfBase)*sspi/sqrt(2.*K);
    else if ( n == 1 ){
        ///P
        floata func = (
                                -sin(K*X)
                                );
        return (4.*exp(-K*K/alpha/4.)*func/spi + erfBase * 2. * X * sa)*sspi /sqrt(2.*K);
    }
    else if ( n == 2 ){
        ///D
        floata func = (
                                      cos(K*X) * K
                               - 2. * sin(K*X) * X * alpha
                               )/sqrt(3.*alpha);
        return (4.*exp(-K*K/alpha/4.)*func/spi + erfBase * 4. * X * X * alpha / sqrt(3.))*sspi/sqrt(2.*K);
    }
    else if ( n == 3 ){
        ///F
        floata func = (
                                 sin(K*X) * K * K
                            + 2.*cos(K*X) * K * X *alpha
                            - 2.*sin(K*X) * alpha* (1. + 2. * X*X*alpha)
                               )/sqrt(15.*alpha*alpha);
        return (4.*exp(-K*K/alpha/4.)*func/spi + erfBase * 8. * X * X * X * alpha * sa/ sqrt(15.))*sspi/sqrt(2.*K);
    }
    else if ( n == 4 ){
        ///G
        floata func = (
                               -    cos(K*X) * K * K * K
                               + 2.*sin(K*X) * K * K * X * alpha
                               + 2.*cos(K*X) * K * alpha * (3.+2.*X*X*alpha)
                               - 4.*sin(K*X) * X * alpha * alpha *(1.+2.*X*X*alpha)
                          )/sqrt(105.*alpha*alpha*alpha);
        return (4.*exp(-K*K/alpha/4.)*func/spi + erfBase * 16. * X * X * X * X * alpha * alpha / sqrt(105.))*sspi/sqrt(2.*K);
    }
    else if ( n == 5 ){
        ///H
        floata func = (
                                -    sin(K*X) * K * K * K * K
                                - 2.*cos(K*X) * K * K * K * X * alpha
                                + 4.*sin(K*X) * K * K * alpha * (3.+X*X*alpha)
                                + 4.*cos(K*X) * K * X * alpha * alpha*(3.+2.*X*X*alpha)
                                - 4.*sin(K*X) * alpha * alpha * (3.+2*X*X*alpha+4.*alpha*alpha*X*X*X*X)
                               )/3./sqrt(105.*alpha*alpha*alpha*alpha);
        return (4.*exp(-K*K/alpha/4.)*func/spi + erfBase * 32. * X * X * X * X * X * alpha*alpha * sa /3./ sqrt(105.))*sspi /sqrt(2.*K);
    }
    else if ( n == 6 ){
        ///I
        floata func = (
                                    cos(K*X) * K * K * K * K * K
                               - 2.*sin(K*X) * K * K * K * K * X * alpha
                               - 4.*cos(K*X) * K * K * K * alpha * alpha *(5.+X*X*alpha)
                               + 8.*sin(K*X) * K * K * X * alpha * alpha *(3.+X*X*alpha)
                               + 4.*cos(K*X) * K * alpha * alpha * alpha *(15.+6.*X*X*alpha+4.*X*X*alpha*alpha)
                               - 8.*sin(K*X) * X * alpha * alpha * alpha * alpha*(3.+2*X*X*alpha+4.*alpha*alpha*X*X*X*X)
                          )/3./sqrt(1155.*alpha*alpha*alpha*alpha*alpha);
        return (4.*exp(-K*K/alpha/4.)*func/spi + erfBase * 64. * X * X * X * X * X * X * alpha * alpha * alpha /3./ sqrt(1155.))*sspi/sqrt(2.*K);
    }

    return 0;
}
