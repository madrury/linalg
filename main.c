#include "tests.h"
#include "vector.h"
#include "matrix.h"
#include "rand.h"


void time_matrix_multiply() {
    struct matrix* M = matrix_random_uniform(5, 5, 0, 1);
    struct matrix* N = matrix_random_uniform(5, 5, 0, 1);
    struct matrix* P = matrix_multiply(M, N); 
    matrix_print(P);
}

int main(int argc, char** argv) {
    init_random();

    // run_all();
    time_matrix_multiply();

    return 0;
}
