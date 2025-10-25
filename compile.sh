#!/bin/bash
##source compile.sh
##if you run this a second time just run 
##bash compile.sh

#run in bandlimit directory 

##compile first
cd Object
make libgaussianSinc.so
export LDFLAGS=-L`pwd`
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`
cd ..

cd bandlimit
export PYTHONPATH=$PYTHONPATH:`pwd`
cd ..
python3 setup.py build_ext -i
