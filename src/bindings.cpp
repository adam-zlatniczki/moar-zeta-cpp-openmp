#include "moar_zeta/moar_zeta.h"
#include "moar_zeta/bindings.h" //this is required for the function implementation to "know" that it's extern C


void hmp_value_py(const double* x, const double* y, const unsigned int d_x, const unsigned int d_y, const unsigned int n, double& hmp_x, double& avg_zeta_x, double& hmp_y, double& avg_zeta_y, const unsigned int n_tests, unsigned int k) {
    hmp_value(x, y, d_x, d_y, n, hmp_x, avg_zeta_x, hmp_y, avg_zeta_y, n_tests, k);
};

void hmp_value_r(const double* x, const double* y, const unsigned int* d_x, const unsigned int* d_y, const unsigned int* n, double* hmp_x, double* avg_zeta_x, double* hmp_y, double* avg_zeta_y, const unsigned int* n_tests, const unsigned int* k) {
    // R passes all parameters as a pointer, so the binding must take care of this
    hmp_value(x, y, *d_x, *d_y, *n, *hmp_x, *avg_zeta_x, *hmp_y, *avg_zeta_y, *n_tests, *k);
};