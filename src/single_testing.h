/**
 * @brief Generates a mask of {-1,1} entries that indicate whether a given point is selected into a random subsample.
 *
 * @param nn_x Nearest neighbor indices (excluding self) in X.
 * @param nn_y Nearest neighbor indices (excluding self) in Y.
 * @param nn_j Nearest neighbor indices (excluding self) in J.
 * @param n Number of points.
 * @param k Number of neighbors (excluding self) per point.
 * @param mask Pointer in which the populated mask should be stored (size ).
 */
void get_rnd_independent_indices(unsigned int* nn_x, unsigned int* nn_y, unsigned int* nn_j, unsigned int n, unsigned int k, char* mask);

/**
 * @brief Calculate the test statistic, its variance and the corresponding p-value.
 *
 * @param local_zeta Array of the local zeta estimates.
 * @param mask A mask that identifies which elements were selected into a random subsample.
 * @param n Number of points.
 * @param k Number of neighbors (excluding self) per point.
 * @param p_value Reference through which the p-value is exported.
 * @param avg_zeta Reference through which the test statistic (average zeta) is exported.
 * @param var_zeta Reference through which the variance of the test statistic is exported.
 */
void get_p_value(double* local_zeta, char* mask, unsigned int n, unsigned int k, double& p_value, double& avg_zeta, double& var_zeta);
