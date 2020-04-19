# [moar-zeta-cpp-openmp](https://github.com/adam-zlatniczki/moar-zeta-cpp-openmp) {#mainpage}

## The Zeta Metric Of Asymmetric Relationship.
Efficient, parallel implementation of the *zeta metric of asymmetric relationship* in C++ using OpenMP. For the corresponding Python package see [moar-zeta-python-cpu](https://github.com/adam-zlatniczki/moar-zeta-python-cpu) and for the R package see [moar-zeta-r-cpu](https://github.com/adam-zlatniczki/moar-zeta-r-cpu).

## Usage
The C++ codebase is not really meant to be used as-is - the original goal was to provide a fast and efficient implementation that has Python and R bindings, mostly focusing on needs of researchers/statisticians. However, the project can be used as a 3rd party library in different C++ projects, with **moar_zeta.h** being the public header.