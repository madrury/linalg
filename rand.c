#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "vector.h"
#include "matrix.h"

void init_random() {
    srand(time(NULL));
}

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
