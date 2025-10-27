#!/bin/bash
##source compile.sh
##if you run this a second time just run 
##bash compile.sh

#run in bandlimit directory 

rm -rf venv/lib/python3.12/site-packages/bandlimit*
rm -rf build
rm -rf dist
rm -rf bandlimit.egg*
rm bandlimit/*.so
rm Object/*.so
rm -rf bandlimit/__py*
rm bandlimit/gaussian.c
python -m build
pip install .

##compile first
#cd Object
#make libgaussianSinc.so
#export LDFLAGS=-L`pwd`
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`
#cd ..

#cp Object/libgaussianSinc.so bandlimit
#cd bandlimit
#export PYTHONPATH=$PYTHONPATH:`pwd`
#cd ..
#python3 setup.py build_ext
