#!/bin/bash
##source compile.sh
##if you run this a second time just run 
##bash compile.sh

#run in Andromeda directory 

##compile first
cd Object
make libgaussianSinc.so
export LDFLAGS=-L`pwd`
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`
cd ..

cd GaussianSinc
export PYTHONPATH=$PYTHONPATH:`pwd`
python3 setup.py build_ext -i
cd ..
