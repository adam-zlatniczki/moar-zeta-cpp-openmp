/**
 * @brief Calculate kNN indices of each point and put them into @nn_indices in a vectorized fashion.
 *
 * @param data A pointer to the data. Data is accepted in a vectorized fashion.
 * @param n The number of data points.
 * @param d The number of dimension of the datapoints.
 * @param k The number of neighbors (excluding self) per point.
 * @param nn_indices The pointer where results should be put.
 */
void get_nn_indices(const double* data, const unsigned int n, const unsigned int d, const unsigned int k, unsigned int* nn_indices);

/**
 * @brief Calculate the nearest neighbor indices of each point in both X, Y & J.
 *
 * @param x The X sample points, vectorized.
 * @param y The Y sample points, vectorized.
 * @param d_x The algebraic dimension of the X sample points.
 * @param d_y The algebraic dimension of the Y sample points.
 * @param n Number of sample points.
 * @param k Number of neighbors (excluding self) to find.
 * @param nn_x Pointer where the nearest neighbor indices in X should be stored.
 * @param nn_y Pointer where the nearest neighbor indices in Y should be stored.
 * @param nn_j Pointer where the nearest neighbor indices in J should be stored.
 */
void get_all_nn_indices(const double* x, const double* y, const unsigned int d_x, const unsigned int d_y, unsigned int n, unsigned int k, unsigned int* nn_x, unsigned int* nn_y, unsigned int* nn_j);

/**
 * @brief Calculate the local zeta metrics in a specific direction.
 *
 * @param nn_x Nearest neighbor indices in X, vectorized. If Y is supplied, then the direction is reversed.
 * @param nn_j Nearest neighbor indices in J, vectorized.
 * @param n Number of data points.
 * @param k Number of neighbors (excluding self) per point.
 * @param local_zeta Pointer where the local zetas should be stored.
 */
void get_local_zeta(unsigned int* nn_x, unsigned int* nn_j, unsigned int n, unsigned int k, double* local_zeta);

/**
 * @brief Calculate local zetas in both directions.
 *
 * @param nn_x Nearest neighbor indices in X, vectorized.
 * @param nn_y Nearest neighbor indices in Y, vectorized.
 * @param nn_j Nearest neighbor indices in J, vectorized.
 * @param n Number of points.
 * @param k Number of neighbors (excluding self).
 * @param local_zeta_x Pointer where local zetas of X should be stored.
 * @param local_zeta_y Pointer where local zetas of Y should be stored.
 */
void get_all_local_zeta(unsigned int* nn_x, unsigned int* nn_y, unsigned int* nn_j, unsigned int n, unsigned int k, double* local_zeta_x, double* local_zeta_y);