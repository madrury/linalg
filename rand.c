#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "matrix.h"


void init_random() {
    srand(time(NULL));
}


/***********************
 * Uniform Distribution
 ***********************/

double _random_uniform(double low, double high) {
    assert(low < high);
    return (low + high) * ((double) rand() / (double) RAND_MAX) - low;
}

struct vector* vector_random_uniform(int length, double low, double high) {
    assert(length > 0);
    struct vector* v = vector_new(length);
    for(int i = 0; i < length; i++) {
        VECTOR_IDX_INTO(v, i) = _random_uniform(low, high);
    }
    return v;
}

struct matrix* matrix_random_uniform(int n_row, int n_col, double low, double high) {
    assert(n_row > 0);
    assert(n_col >0);
    struct matrix* M = matrix_new(n_row, n_col);
    for(int i = 0; i < n_row; i++) {
        for(int j = 0; j < n_col; j++) {
            MATRIX_IDX_INTO(M, i, j) = _random_uniform(low, high);
        }
    }
    return M;
}


/*************************
 * Gaussian Dristribution
 *************************/

/* Generate a number distributed as random gaussian noise using the Box-Muller
 * method. 
   The trick of using the static keyword to remember pairs of values is taken
   from wikipedia.
*/
double _random_gaussian(double mu, double sigma) {
    const double two_pi = 2.0 * 3.14159265358979323846;

    static double z0, z1;
    double u0, u1;

    // Since the strategy employed generates pairs of random values, we can,
    // on each other call, simply remember the leftover value and return it.
    static bool generate_new_values = false;
    generate_new_values = !generate_new_values;
    if (!generate_new_values) {
        return z1 * sigma + mu;
    }

    u0 = _random_uniform(0, 1);
    u1 = _random_uniform(0, 1);
    z0 = sqrt(-2.0 * log(u0)) * cos(two_pi * u1);
    z1 = sqrt(-2.0 * log(u0)) * sin(two_pi * u1);

    return z0 * sigma + mu;
}

struct vector* vector_random_gaussian(int length, double mu, double sigma) {
    assert(length > 0);
    struct vector* v = vector_new(length);
    for(int i = 0; i < length; i++) {
        VECTOR_IDX_INTO(v, i) = _random_gaussian(mu, sigma);
    }
    return v;
}
