#!/bin/bash

tmp=`uname -s`

if [ $tmp == 'Darwin' ]; then
##for macOS, make sure have automake/aclocal
  brew install automake
  brew reinstall gcc
  brew install libtool
  export PATH="/opt/homebrew/opt/libtool/libexec/gnubin:$PATH"
fi

## need to grab some python libs
python3 -m pip install scipy h5py numpy pandas pybind11 netCDF4


libtoolize
aclocal -I m4
autoconf
automake --add-missing --force-missing
./configure --prefix=$UCVM_INSTALL_PATH/model/muscalnc

./configure --prefix=/home/runner/work/muscalnc/muscalnc/target/model/muscalnc --enable-shared --with-hdf5-libdir=$UCVM_INSTALL_PATH/lib/hdf5/lib --with-hdf5-incdir=$UCVM_INSTALL_PATH/lib/hdf5/include --with-netcdf-libdir=$UCVM_INSTALL_PATH/lib/netcdf/lib --with-netcdf-incdir=$UCVM_INSTALL_PATH/lib/netcdf/include

make
make install

