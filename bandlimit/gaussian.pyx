###-------------###
#GaussianSinc.pyx##
###-------------###

 #*  Copywrite 2018, 2019, 2020, 2021, 2022, 2023, 2024, 2025  Quantum Galaxies Corporation,
 #*   and methods patented by Texas Tech University.
 #*  We acknowledge the generous support of Texas Tech University,
 #*  The Robert A. Welch Foundation, and the Army Research Office.

# MIT license


import numpy as np

include "system.pxi"

from constants cimport inta
from constants cimport floata

from coreMath cimport GaussianInSinc

cpdef double compute(floata lattice, int n, floata alpha,floata y,floata X ):
        """
        * GTOs in plane waves
        * GaussianInSinc = < normalized_angular_gaussian(n) @ y | Sinc@ X in lattice >
        """
        return GaussianInSinc(pi/lattice, n, 0.5*alpha, y, X)
