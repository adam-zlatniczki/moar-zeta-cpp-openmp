/**
 * @brief Main function, calculates the zeta test statistics and their corresponding (harmonic mean) p-values.
 *
 * @param x The X sample points, vectorized.
 * @param y The Y sample points, vectorized.
 * @param d_x The algebraic dimension of the X sample points.
 * @param d_y The algebraic dimension of the Y sample points.
 * @param n The number of points.
 * @param hmp_x Reference where the HMP of Zeta_X will be exported.
 * @param avg_zeta_x Reference where the test statistic Zeta_X will be exported.
 * @param hmp_y Reference where the HMP of Zeta_Y will be exported.
 * @param avg_zeta_y Reference where the test statistic Zeta_Y will be exported.
 * @param n_tests Number of tests to do (number of random subsamples, or L in the HMP terminology).
 * @param k Number of nearest neighbors (excluding self) to calculate. If not set, ceil(sqrt(n)).
 */
void hmp_value(const double* x, const double* y, const unsigned int d_x, const unsigned int d_y, const unsigned int n, double& hmp_x, double& avg_zeta_x, double& hmp_y, double& avg_zeta_y, const unsigned int n_tests=50, unsigned int k=0);