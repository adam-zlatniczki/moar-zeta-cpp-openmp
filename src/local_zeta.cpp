#include "stdafx.h"
#include "alglibmisc.h"
#include <parallel/algorithm>


void get_nn_indices(const double* data, const unsigned int n, const unsigned int d, const unsigned int k, unsigned int* nn_indices) {

    // create
    alglib::real_2d_array a;
    a.setcontent(n, d, data);

    // create tags that can identify the points
    alglib::ae_int_t* indices = new alglib::ae_int_t[n];
    for (unsigned int i=0; i<n; i++) {
        indices[i] = i;
    }

    alglib::integer_1d_array tags;
    tags.setcontent(n, indices);

    delete[] indices;

    // at low k values this is important to not bias zeta upward
    // at high k values it doesn't really matter
    bool self_match = false;

    // build kd-tree
    alglib::kdtree kdt;
    alglib::kdtreebuildtagged(a, tags, d, 0, 0, kdt);

    // populate nearest neighbor indices
    #pragma omp parallel for
    for (unsigned int i=0; i<n; i++) {
        alglib::real_1d_array query_point;
        alglib::integer_1d_array result;

        query_point.setcontent(d, &data[i*d]);

        alglib::kdtreerequestbuffer buf;
        alglib::kdtreecreaterequestbuffer(kdt, buf);
        alglib::kdtreetsqueryknn(kdt, buf, query_point, k, self_match);
        alglib::kdtreetsqueryresultstags(kdt, buf, result);

        for (unsigned int j=0; j<k; j++) {
            nn_indices[i*k + j] = result[j];
        }
    }
}

void get_all_nn_indices(const double* x, const double* y,const unsigned int d_x, const unsigned int d_y, unsigned int n, unsigned int k, unsigned int* nn_x, unsigned int* nn_y, unsigned int* nn_j) {
    double* j;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            get_nn_indices(x, n, d_x, k, nn_x);
        }

        #pragma omp section
        {
            get_nn_indices(y, n, d_y, k, nn_y);
        }

        #pragma omp section
        {
            unsigned int d = d_x + d_y;
            j = new double[n*d];
            for (unsigned int i=0; i<n; i++) {
                for (unsigned int l=0; l<d_x; l++) {
                    j[i*d + l] = x[i*d_x + l];
                }
                for (unsigned int l=0; l<d_y; l++){
                    j[i*d + d_x + l] = y[i*d_y + l];
                }
            }

            get_nn_indices(j, n, d, k, nn_j);
        }
    }

    delete[] j;
}

void get_local_zeta(unsigned int* nn_x, unsigned int* nn_j, unsigned int n, unsigned int k, double* local_zeta) {
    const int max_pos = k - 1;
    const int max_pos_sum = 2 * max_pos;

    #pragma omp parallel for
    for (unsigned int i=0; i<n; i++) {
        int point_index = i * k;

        // find intersection of neighborhoods by a merge-sort-like idea
        #pragma omp parallel sections
        {
            #pragma omp section
            __gnu_parallel::sort(nn_x + point_index, nn_x + point_index + k);

            #pragma omp section
            __gnu_parallel::sort(nn_j + point_index, nn_j + point_index + k);
        }

        double num_matches = 0;

        unsigned int pos_x = 0;
        unsigned int pos_j = 0;

        bool merge = true;
        while ( merge ) {
            // check if counting should stop at the end of this cycle
            if ( (pos_x + pos_j) == max_pos_sum ) {
                merge = false;
            } else {
                if ( (pos_x == max_pos) && (nn_x[point_index + pos_x] < nn_j[point_index + pos_j]) ) merge = false;
                if ( (pos_j == max_pos) && (nn_x[point_index + pos_x] > nn_j[point_index + pos_j]) ) merge = false;
            }

            // increment the number of matches if necessary
            // increment the position iterators
            if (nn_x[point_index + pos_x] == nn_j[point_index + pos_j]) {
                num_matches++;
                if (pos_x < max_pos) pos_x++;
                if (pos_j < max_pos) pos_j++;
            } else {
                if (nn_x[point_index + pos_x] < nn_j[point_index + pos_j]) {
                    if (pos_x < max_pos) pos_x++;
                } else {
                    if (pos_j < max_pos) pos_j++;
                }
            }

        }

        local_zeta[i] = num_matches / k;
    }
}

void get_all_local_zeta(unsigned int* nn_x, unsigned int* nn_y, unsigned int* nn_j, unsigned int n, unsigned int k, double* local_zeta_x, double* local_zeta_y) {

    #pragma omp parallel sections
    {
        #pragma omp section
        get_local_zeta(nn_x, nn_j, n, k, local_zeta_x);

        #pragma omp section
        get_local_zeta(nn_y, nn_j, n, k, local_zeta_y);
    }

}