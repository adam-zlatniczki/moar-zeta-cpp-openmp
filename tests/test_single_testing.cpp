#define CATCH_CONFIG_CONSOLE_WIDTH 300
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "matcher.hpp"
#include <iostream>

#include "single_testing.h"

TEST_CASE( "Generate random sample mask", "[single_testing]" ) {
    int nn_x[5*2] = {
        1, 3,
        1, 4,
        1, 0,
        0, 4,
        3, 2
    };

    int nn_y[5*2] = {
        1, 2,
        1, 4,
        1, 0,
        0, 4,
        3, 2
    };

    int nn_j[5*2] = {
        1, 3,
        1, 3,
        1, 0,
        0, 4,
        3, 2
    };

    std::srand(0); // shuffling [0, 1, 2, 3, 4] should become [2, 0, 4, 1, 3]
    char expected_mask[5] = {-1, -1, 1, -1, 1};

    char* calculated_mask = new char[5];
    get_rnd_independent_indices(nn_x, nn_y, nn_j, 5, 2, calculated_mask);

    REQUIRE( arrays_match<char>(expected_mask, calculated_mask, 5) );

    delete[] calculated_mask;

}

TEST_CASE( "Calculate p-value for single test", "[single_testing]" ) {
    double local_zeta[7] = {0.8, 0.6, 0.5, 0.9, 0.8, 0.7, 0.8};
    char   mask[7]       = {  1,   1,  -1,   1,  -1,   1,   1};

    double p_value, avg_zeta, var_zeta;

    get_p_value(local_zeta, mask, 7, 3, p_value, avg_zeta, var_zeta);

    REQUIRE( avg_zeta == 0.76 );
    REQUIRE( var_zeta == Approx(0.0315).margin(0.0001) );
    REQUIRE( p_value == Approx(0.176).margin(0.001) );
}