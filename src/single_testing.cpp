#include <algorithm>
#include <math.h>

# define M_PI   3.14159265358979323846  /* pi */

void get_rnd_independent_indices(unsigned int* nn_x, unsigned int* nn_y, unsigned int* nn_j, unsigned int n, unsigned int k, char* mask) {
    int* shuffled_indices = new int[n];
    for (unsigned int i=0; i<n; i++) {
        shuffled_indices[i] = i;
    }

    // shuffle indices (in linear time)
    std::random_shuffle(shuffled_indices, shuffled_indices + n);

    // Fill a mask that keeps track of the random sample (in linear time).
    // (0: not visited yet; shouldn't be any in the final mask)
    //  1: selected into sample
    // -1: rejected from sample
    for (unsigned int i=0; i<n; i++) mask[i] = 0;

    unsigned int rnd_point = 0;

    // this FOR shouldn't be parallelized due to dependence of successive steps
    for (unsigned int i=0; i<n; i++) {
        rnd_point = shuffled_indices[i];

        if (mask[rnd_point] == 0) {
            // reject neighbors of the point from the sample
            for (unsigned int j=0; j<k; j++) {
                if (mask[ nn_x[rnd_point*k + j] ] == 0) mask[ nn_x[rnd_point*k + j] ] = -1;
                if (mask[ nn_y[rnd_point*k + j] ] == 0) mask[ nn_y[rnd_point*k + j] ] = -1;
                if (mask[ nn_j[rnd_point*k + j] ] == 0) mask[ nn_j[rnd_point*k + j] ] = -1;
            }

            // add point to the sample
            mask[rnd_point] = 1;
        }
    }

    delete[] shuffled_indices;
}

void get_p_value(double* local_zeta, char* mask, unsigned int n, unsigned int k, double& p_value, double& avg_zeta, double& var_zeta) {
    unsigned int n_subsample = 0;
    avg_zeta = 0.0;
    var_zeta = 0.0;

    for (unsigned int i=0; i<n; i++) {
        if (mask[i] == 1) {
            avg_zeta = avg_zeta + local_zeta[i];
            var_zeta = var_zeta + local_zeta[i] * (1.0 - local_zeta[i]);
            n_subsample++;
        }
    }

    // calculate average of zeta
    avg_zeta = avg_zeta / n_subsample;

    // calculate sample variance of average of zeta (variance of half-normal dist.)
    var_zeta = var_zeta / (n_subsample*n_subsample * k);

    // calculate variance of underlying normal (the sigma^2 parameter of the half-normal)
    var_zeta = var_zeta / (1.0 - 2.0 / M_PI);

    // calculate p-value
    if (var_zeta == 0.0) {
        if (avg_zeta == 1.0) {
            p_value = 1.0;
        } else {
            p_value = 0.0;
        }
    } else {
        p_value = 1.0 - erf( (1 - avg_zeta) / sqrt(2 * var_zeta) );
    }
}