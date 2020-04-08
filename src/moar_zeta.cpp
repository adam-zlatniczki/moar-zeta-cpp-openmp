#include <math.h>

#include "local_zeta.h"
#include "single_testing.h"


void hmp_value(const double* x, const double* y, const unsigned int n, double& hmp_x, double& avg_zeta_x, double& hmp_y, double& avg_zeta_y, const unsigned int n_tests=50, unsigned int k=0) {
    // if k is not specified set it
    if (k == 0) {
        k = (unsigned int) ceil(sqrt(n));
    }

    // calculate nearest neighbor indices
    unsigned int *nn_x, *nn_y, *nn_j;
    nn_x = new unsigned int[n*k];
    nn_y = new unsigned int[n*k];
    nn_j = new unsigned int[n*k];

    get_all_nn_indices(x, y, n, k, nn_x, nn_y, nn_j);

    // calculate local zetas
    double *local_zeta_x, *local_zeta_y;
    local_zeta_x = new double[n];
    local_zeta_y =new double[n];

    get_all_local_zeta(nn_x, nn_y, nn_j, n, k, local_zeta_x, local_zeta_y);

    // run multiple tests on random subsets of data
    double* p_values_x  = new double[n_tests];
    double* avg_zetas_x = new double[n_tests];
    double* var_zetas_x = new double[n_tests];

    double* p_values_y  = new double[n_tests];
    double* avg_zetas_y = new double[n_tests];
    double* var_zetas_y = new double[n_tests];

    for (unsigned int i=0; i<n_tests; i++) {
        char* mask = new char[n];
        get_rnd_independent_indices(nn_x, nn_y, nn_j, n, k, mask);

        get_p_value(local_zeta_x, mask, n, k, p_values_x[i], avg_zetas_x[i], var_zetas_x[i]);
        get_p_value(local_zeta_y, mask, n, k, p_values_y[i], avg_zetas_y[i], var_zetas_y[i]);

        delete[] mask;
    }

    // calculate final results (test statistic and harmonic p-value in both directions)
    hmp_x = 0.0;
    avg_zeta_x = 0.0;

    hmp_y = 0.0;
    avg_zeta_y = 0.0;

    for (unsigned int i=0; i<n_tests; i++) {
        hmp_x = hmp_x + 1.0 / p_values_x[i];
        avg_zeta_x = avg_zeta_x + avg_zetas_x[i];

        hmp_y = hmp_y + 1.0 / p_values_y[i];
        avg_zeta_y = avg_zeta_y + avg_zetas_y[i];
    }

    hmp_x = n_tests / hmp_x;
    avg_zeta_x = avg_zeta_x / n_tests;

    hmp_y = n_tests / hmp_y;
    avg_zeta_y = avg_zeta_y / n_tests;

    // cleanup
    delete[] p_values_x;
    delete[] avg_zetas_x;
    delete[] var_zetas_x;

    delete[] p_values_y;
    delete[] avg_zetas_y;
    delete[] var_zetas_y;

    delete[] local_zeta_x;
    delete[] local_zeta_y;

    delete[] nn_x;
    delete[] nn_y;
    delete[] nn_j;
}