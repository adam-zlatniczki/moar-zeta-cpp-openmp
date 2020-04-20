#define CATCH_CONFIG_CONSOLE_WIDTH 300
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "matcher.hpp"
#include <ctime>

#include "moar_zeta/moar_zeta.h"

TEST_CASE( "Test statistic and HMP of multiple testing calculated", "[multiple testing]" ) {
    const double x[20] = {0.51642652, 0.35691608, 0.52854316, 0.9211829 , 0.85101179,
                          1.        , 0.74558555, 0.73573654, 0.79648562, 0.24007225,
                          0.40903107, 0.3785465 , 0.27126856, 0.95131285, 0.49178367,
                          0.38362497, 0.65527292, 0.2006384 , 0.        , 0.01702792};

    const double y[20] = {0.32323993, 0.17935829, 0.33577808, 0.86501706, 0.75292886,
                          1.        , 0.59884666, 0.58533046, 0.67109096, 0.09894196,
                          0.22203739, 0.19656223, 0.11834551, 0.91548311, 0.29844056,
                          0.20070637, 0.48052839, 0.0765694 , 0.        , 0.00407974};

    std::srand(0);

    double hmp_x, avg_zeta_x, hmp_y, avg_zeta_y;

    hmp_value(x, y, 1, 1, 20, hmp_x, avg_zeta_x, hmp_y, avg_zeta_y);

    REQUIRE( hmp_x == Approx(0.65).margin(0.06) );
    REQUIRE( avg_zeta_x == Approx(0.95).margin(0.03) );
    REQUIRE( hmp_y == Approx(0.45).margin(0.06) );
    REQUIRE( avg_zeta_y == Approx(0.95).margin(0.03) );
}