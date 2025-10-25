### from ubuntu
#apt-get update && apt-get install -y apt-utils build-essential &&
#apt-get install -y make git nano &&
#apt-get install -y libatlas-base-dev liblapack-dev liblapacke-dev gfortran libhdf5-serial-dev &&
#git clone https://github.com/JonathanJerke/Andromeda
###
#

cc   = gcc

LAPACKlib          = /usr/lib/x86_64-linux-gnu
LAPACKinc       = /usr/include/x86_64-linux-gnu

flags           =-I${LAPACKinc}   -L${LAPACKlib}
lib             = -lm
libgaussianSinc.so: system.h constants.h  coreMath.c coreMath.h
	$(cc) $(flags) coreMath.c $(lib) -shared -Wall -fPIC -fvisibility=default -o libgaussianSinc.so

