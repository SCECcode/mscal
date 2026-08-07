> [!CAUTION]
> **THIS REPOSITORY IS FOR NetCDF VERSION**
>
> Active development on MUSCALNC model has transition to the TileDB version.
>
> Please **do not submit new pull requests or issues** to this legacy repository. Any changes pushed here will not be maintained or integrated into future releases.

# The Multi-scale Statewide CALifornia Velocity Model (muscalnc)

<a href="https://github.com/sceccode/muscalnc.git"><img src="https://github.com/sceccode/muscalnc/wiki/images/muscalnc_logo.png"></a>

[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
![GitHub repo size](https://img.shields.io/github/repo-size/sceccode/muscalnc)
[![muscalnc-ucvm-ci Actions Status](https://github.com/SCECcode/muscalnc/workflows/muscalnc-ucvm-ci/badge.svg)](https://github.com/SCECcode/muscalnc/actions)

The Multi-Scale CALifornia (MUSCALNC) statewide Vp and Vs velocity models provide 
high-quality integrated description of seismic structures across the state. 
Starting with the CANVAS base model (Doody et al., 2023), MUSCALNC incorporates 
multiple regional and local velocity datasets into a unified structure, capturing 
features ranging from broad crustal-mantle structures to fine-scale local 
anomalies such as sedimentary basins.
 
To ensure quality, the merged multi-scale models underwent a data-informed refinement
process guided by simulations of small validation events. A key feature of MUSCALNC is 
the inclusion of a locally optimized near-surface low-velocity taper (LVT), specifically 
designed to better represent under-resolved shallow structures and improve the accuracy 
of ground-motion predictions.

## Installation

This package is intended to be installed as part of the UCVM framework,
version 25.7 or higher. 

## Contact the authors

If you would like to contact the authors regarding this software,
please e-mail software@scec.org. Note this e-mail address should
be used for questions regarding the software itself (e.g. how
do I link the library properly?). Questions regarding the model's
science (e.g. on what paper is the MUSCALNC based?) should be directed
to the model's authors, located in the AUTHORS file.

## To build in standalone mode

To install this package on your computer, please run the following commands:

<pre>
  libtoolize --copy --force
  aclocal -I m4
  autoconf
  automake --add-missing --force-missing
  ./configure --prefix=/dir/to/install
  make
  make install
</pre>

<pre>
example:

./configure --prefix=$UCVM_INSTALL_PATH --enable-shared CPPFLAGS='-I$UCVM_INSTALL_PATH/lib/hdf5/include -I$UCVM_INSTALL_PATH/lib/netcdf/include' LDFLAGS='-L$UCVM_INSTALL_PATH/lib/hdf5/lib -L$UCVM_INSTALL_PATH/lib/netcdf/lib -Wl,-rpath,$UCVM_INSTALL_PATH/lib/hdf5/lib -Wl,-rpath,$UCVM_INSTALL_PATH/lib/netcdf/lib' LIBS='-lhdf5 -lnetcdf'
</pre>

## Note

Optional 1d background base on model's surface/boundary datapoints 

Preprocessing : 
   Extract all surface points from the MUSCALNC file layer by layer and create binary surface_945765.in 

Model initialization :
   Load surface points and create KDtree of surface points with 3 axis (lon/lat/depth) 

Query access
   Fill in background with nearest neighboring surface point from surface KDtree 

### muscalnc_query

### muscalnc_surface

### query_kdtree

### build_kdtree
