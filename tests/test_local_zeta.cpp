#define CATCH_CONFIG_CONSOLE_WIDTH 300
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "matcher.hpp"

#include "local_zeta.h"


const double x[20] = {0.51642652, 0.35691608, 0.52854316, 0.9211829 , 0.85101179,
                      1.        , 0.74558555, 0.73573654, 0.79648562, 0.24007225,
                      0.40903107, 0.3785465 , 0.27126856, 0.95131285, 0.49178367,
                      0.38362497, 0.65527292, 0.2006384 , 0.        , 0.01702792};

const double y[20] = {0.32323993, 0.17935829, 0.33577808, 0.86501706, 0.75292886,
                      1.        , 0.59884666, 0.58533046, 0.67109096, 0.09894196,
                      0.22203739, 0.19656223, 0.11834551, 0.91548311, 0.29844056,
                      0.20070637, 0.48052839, 0.0765694 , 0.        , 0.00407974};

const double j[40] = {
    0.51642652, 0.32323993,
    0.35691608, 0.17935829,
    0.52854316, 0.33577808,
    0.9211829 , 0.86501706,
    0.85101179, 0.75292886,
    1.        , 1.        ,
    0.74558555, 0.59884666,
    0.73573654, 0.58533046,
    0.79648562, 0.67109096,
    0.24007225, 0.09894196,
    0.40903107, 0.22203739,
    0.3785465 , 0.19656223,
    0.27126856, 0.11834551,
    0.95131285, 0.91548311,
    0.49178367, 0.29844056,
    0.38362497, 0.20070637,
    0.65527292, 0.48052839,
    0.2006384 , 0.0765694 ,
    0.        , 0.        ,
    0.01702792, 0.00407974
};


TEST_CASE( "1D nearest neighbor indices calculated", "[local_zeta]" ) {
    unsigned int expected_indices[20*5] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9,
        0, 14, 10, 16, 15,
        13,  4,  5,  8,  6,
        8,  3, 13,  6,  7,
        13,  3,  4,  8,  6,
        7,  8, 16,  4,  3,
        6,  8, 16,  4,  3,
        6,  4,  7,  3, 16,
        12, 17,  1, 11, 15,
        15, 11,  1, 14,  0,
        15,  1, 10, 12, 14,
        9, 17,  1, 11, 15,
        3,  5,  4,  8,  6,
        0,  2, 10, 15, 11,
        11, 10,  1, 14, 12,
        7,  6,  2,  0,  8,
        9, 12,  1, 11, 15,
        19, 17,  9, 12,  1,
        18, 17,  9, 12,  1
    };

    // calculate NN indices
    unsigned int* calculated_indices = new unsigned int[20*5];
    get_nn_indices(x, 20, 1, 5, calculated_indices);

    // test expectations
    REQUIRE( arrays_match<unsigned int>(expected_indices, calculated_indices, 20*5) );

    // cleanup
    delete[] calculated_indices;
}

TEST_CASE( "2D nearest neighbor indices calculated", "[local_zeta]" ) {
    unsigned int expected_indices[20*5] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9,
        0, 14, 10, 16, 15,
        13,  4,  5,  8,  6,
        8,  3,  6, 13,  7,
        13,  3,  4,  8,  6,
        7,  8, 16,  4,  2,
        6,  8, 16,  4,  2,
        6,  4,  7, 16,  3,
        12, 17,  1, 11, 15,
        15, 11,  1, 14,  0,
        15,  1, 10, 12, 14,
        9, 17,  1, 11, 15,
        3,  5,  4,  8,  6,
        0,  2, 10, 15, 11,
        11, 10,  1, 14, 12,
        7,  6,  2,  0, 14,
        9, 12,  1, 11, 15,
        19, 17,  9, 12,  1,
        18, 17,  9, 12,  1
    };

    // calculate NN indices
    unsigned int* calculated_indices = new unsigned int[20*5];
    get_nn_indices(j, 20, 2, 5, calculated_indices);

    REQUIRE( arrays_match<unsigned int>(expected_indices, calculated_indices, 20*5) );

    // cleanup
    delete[] calculated_indices;
}

TEST_CASE( "All nearest neighbor indices are calculated", "[local_zeta]" ) {
    unsigned int expected_indices_x[20*5] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9,
        0, 14, 10, 16, 15,
        13,  4,  5,  8,  6,
        8,  3, 13,  6,  7,
        13,  3,  4,  8,  6,
        7,  8, 16,  4,  3,
        6,  8, 16,  4,  3,
        6,  4,  7,  3, 16,
        12, 17,  1, 11, 15,
        15, 11,  1, 14,  0,
        15,  1, 10, 12, 14,
        9, 17,  1, 11, 15,
        3,  5,  4,  8,  6,
        0,  2, 10, 15, 11,
        11, 10,  1, 14, 12,
        7,  6,  2,  0,  8,
        9, 12,  1, 11, 15,
        19, 17,  9, 12,  1,
        18, 17,  9, 12,  1
    };

    unsigned int expected_indices_y[20*5] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9,
        0, 14, 10, 15, 11,
        13,  4,  5,  8,  6,
        8,  3,  6, 13,  7,
        13,  3,  4,  8,  6,
        7,  8, 16,  4,  2,
        6,  8, 16,  4,  2,
        6,  4,  7, 16,  3,
        12, 17,  1, 19, 11,
        15, 11,  1, 14,  0,
        15,  1, 10, 12,  9,
        9, 17,  1, 11, 15,
        3,  5,  4,  8,  6,
        0,  2, 10, 15, 11,
        11, 10,  1, 12, 14,
        7,  6,  2,  0, 14,
        9, 12, 19, 18,  1,
        19, 17,  9, 12,  1,
        18, 17,  9, 12,  1
    };

    unsigned int expected_indices_j[20*5] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9,
        0, 14, 10, 16, 15,
        13,  4,  5,  8,  6,
        8,  3,  6, 13,  7,
        13,  3,  4,  8,  6,
        7,  8, 16,  4,  2,
        6,  8, 16,  4,  2,
        6,  4,  7, 16,  3,
        12, 17,  1, 11, 15,
        15, 11,  1, 14,  0,
        15,  1, 10, 12, 14,
        9, 17,  1, 11, 15,
        3,  5,  4,  8,  6,
        0,  2, 10, 15, 11,
        11, 10,  1, 14, 12,
        7,  6,  2,  0, 14,
        9, 12,  1, 11, 15,
        19, 17,  9, 12,  1,
        18, 17,  9, 12,  1
    };

    // calculate NN indices
    unsigned int* calculated_indices_x = new unsigned int[20*5];
    unsigned int* calculated_indices_y = new unsigned int[20*5];
    unsigned int* calculated_indices_j = new unsigned int[20*5];

    get_all_nn_indices(x, y, 20, 5, calculated_indices_x, calculated_indices_y, calculated_indices_j);

    // test
    REQUIRE( arrays_match<unsigned int>(expected_indices_x, calculated_indices_x, 20) );
    REQUIRE( arrays_match<unsigned int>(expected_indices_y, calculated_indices_y, 20) );
    REQUIRE( arrays_match<unsigned int>(expected_indices_j, calculated_indices_j, 20) );

    // cleanup
    delete[] calculated_indices_x;
    delete[] calculated_indices_y;
    delete[] calculated_indices_j;
}

TEST_CASE( "Local zetas calculated from matching neighbor indices", "[local_zeta]" ) {
    unsigned int nn_x[10] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9
    };

    unsigned int nn_j[10] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9
    };

    double expected_zeta[2] = {1.0, 1.0};

    double calculated_zeta[2] = {-1, -1};
    get_local_zeta(nn_x, nn_j, 2, 5, calculated_zeta);

    REQUIRE( arrays_match<double>(expected_zeta, calculated_zeta, 2) );
}

TEST_CASE( "Local zetas calculated from differring neighbor indices", "[local_zeta]" ) {
    unsigned int nn_x[10] = {
        2, 14, 10, 15, 100,
        11, 15, 10, 12,  9
    };

    unsigned int nn_j[10] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9
    };

    double expected_zeta[2] = {0.8, 1.0};

    double calculated_zeta[2] = {-1, -1};
    get_local_zeta(nn_x, nn_j, 2, 5, calculated_zeta);

    REQUIRE( arrays_match<double>(expected_zeta, calculated_zeta, 2) );
}

TEST_CASE( "All local zetas calculated from neighbor indices", "[local_zeta]" ) {
    unsigned int nn_x[5*5] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9,
        0, 14, 10, 16, 15,
        13,  4,  5,  8,  6,
        8,  3, 13,  6,  7
    };

    unsigned int nn_y[5*5] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9,
        0, 14, 10, 15, 11,
        13,  4,  5,  8,  6,
        8,  3,  6, 13,  7
    };

    unsigned int nn_j[5*5] = {
        2, 14, 10, 15, 11,
        11, 15, 10, 12,  9,
        0, 14, 10, 16, 15,
        13,  4,  5,  8,  6,
        8,  3,  6, 13,  7
    };

    double expected_zeta_x[5] = {1.0, 1.0, 1.0, 1.0, 1.0};
    double expected_zeta_y[5] = {1.0, 1.0, 0.8, 1.0, 1.0};

    double calculated_zeta_x[5] = {-1, -1, -1, -1, -1};
    double calculated_zeta_y[5] = {-1, -1, -1, -1, -1};

    get_local_zeta(nn_x, nn_j, 5, 5, calculated_zeta_x);
    get_local_zeta(nn_y, nn_j, 5, 5, calculated_zeta_y);

    REQUIRE( arrays_match<double>(expected_zeta_x, calculated_zeta_x, 5) );
    REQUIRE( arrays_match<double>(expected_zeta_y, calculated_zeta_y, 5) );
}

