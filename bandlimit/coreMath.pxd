###-------------###
####coreMath.pxd##
###-------------###

 #*  Copywrite 2018, 2019, 2020, 2021, 2022, 2023, 2024, 2025  Quantum Galaxies Corporation,
 #*   and methods patented by Texas Tech University.
 #*  We acknowledge the generous support of Texas Tech University,
 #*  The Robert A. Welch Foundation, and the Army Research Office.

# MIT license

include "system.pxi"

from constants cimport inta
from constants cimport floata

cdef extern from "../Object/coreMath.h":
    floata GaussianInSinc( floata K, inta n, floata alpha, floata y, floata X )