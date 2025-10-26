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
double GaussianInSinc( double K, int n, double alpha, double y, double X ){
    double sspi = sqrt(sqrt(pi/2./alpha));
    double spi = sqrt(pi);
    double sa   = sqrt(alpha);
    X -= y;
    double erfBase = sa * ( expErf(( K - 2. * I * X * alpha )/(2.*sa))+expErf(( K + 2. * I * X * alpha )/(2.*sa)) );
    if ( n == 0 )
        ///S
        return (erfBase)*sspi/sqrt(2.*K);
    else if ( n == 1 ){
        ///P
        double func = (
                                -sin(K*X)
                                );
        return (4.*exp(-K*K/alpha/4.)*func/spi + erfBase * 2. * X * sa)*sspi /sqrt(2.*K);
    }
    else if ( n == 2 ){
        ///D
        double func = (
                                      cos(K*X) * K
                               - 2. * sin(K*X) * X * alpha
                               )/sqrt(3.*alpha);
        return (4.*exp(-K*K/alpha/4.)*func/spi + erfBase * 4. * X * X * alpha / sqrt(3.))*sspi/sqrt(2.*K);
    }
    else if ( n == 3 ){
        ///F
        double func = (
                                 sin(K*X) * K * K
                            + 2.*cos(K*X) * K * X *alpha
                            - 2.*sin(K*X) * alpha* (1. + 2. * X*X*alpha)
                               )/sqrt(15.*alpha*alpha);
        return (4.*exp(-K*K/alpha/4.)*func/spi + erfBase * 8. * X * X * X * alpha * sa/ sqrt(15.))*sspi/sqrt(2.*K);
    }
    else if ( n == 4 ){
        ///G
        double func = (
                               -    cos(K*X) * K * K * K
                               + 2.*sin(K*X) * K * K * X * alpha
                               + 2.*cos(K*X) * K * alpha * (3.+2.*X*X*alpha)
                               - 4.*sin(K*X) * X * alpha * alpha *(1.+2.*X*X*alpha)
                          )/sqrt(105.*alpha*alpha*alpha);
        return (4.*exp(-K*K/alpha/4.)*func/spi + erfBase * 16. * X * X * X * X * alpha * alpha / sqrt(105.))*sspi/sqrt(2.*K);
    }
    else if ( n == 5 ){
        ///H
        double func = (
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
        double func = (
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


/*
* Momentum integral in tensor train form
* momentumIntegralInTrain2 ( beta, kl , d, diagonal_flag )
* diagonal_flag = 1 for diagonal piece
* diagonal_flag = 0 for off diagonal piece
*/
double momentumIntegralInTrain2 ( double beta, double kl , double d, int diagonal_flag ){
    DCOMPLEX base0a,base0b,base1a,base1b,base2aa,base2ab, stage1,stage2,stage3;
    
    //correct//
    beta = beta * d;
    
    switch(diagonal_flag){
        case 1:
            base0a = exp(-pi*pi/beta/beta)*cexp( 2*pi*I*kl );
            base0b = conj(base0a);
            base1a = expErf(-I * kl * beta);
            base1b = conj(base1a);
            base2aa = expErf(pi/beta-I * kl * beta);
            base2ab = conj(base2aa);

            stage1 = 0.5*(base2aa+base2ab);
            stage2 = 0.5*beta/sqrt(pi*pi*pi)*(kl*beta *sqrt(pi)*I*(2*base1a-base2aa+base2ab)-2+base0a+base0b);
    
            return creal(stage1+stage2);
                
        case 0:
            base1a = expErf(-I * kl * beta);
            base1b = conj(base1a);
            base2aa = expErf(pi/beta-I * kl * beta);
            base2ab = conj(base2aa);

            stage1 = (-I)/(4.*pi)*(base2aa - base2ab - 2*base1a );
            return creal(stage1);
        default:
            break;

    }
    return 0.;
}
