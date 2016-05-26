#include <time.h>
#include <stdio.h>
#include "tests.h"
#include "vector.h"
#include "matrix.h"
#include "rand.h"

/*
void time_matrix_multiply() {
    struct matrix* P;
    struct matrix* M = matrix_random_uniform(1000, 1000, 0, 1);
    struct matrix* N = matrix_random_uniform(1000, 1000, 0, 1);
    for(int cache = 0; cache < 1000; cache += 50) {
        clock_t start = clock(), diff;
        if(cache > 0) {
            P = matrix_multiply_cache(M, N, cache); 
        } else {
            P = matrix_multiply(M, N); 
        }
        diff = clock() - start;

        int msec = diff * 1000 / CLOCKS_PER_SEC;
        printf("With cache size %d took %d seconds and %d milliseconds.\n",
               cache, msec / 1000, msec % 1000
        );
    }
    matrix_free(M); matrix_free(N); matrix_free(P);
}
*/

void time_qr_decomp() {
    clock_t start = clock(), diff;
    struct matrix* M = matrix_random_uniform(100000, 200, 0, 1);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    matrix_free(M); qr_decomp_free(qr);
    diff = clock() - start;

    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Qr decomp took  %d seconds and %d milliseconds.\n",
            msec / 1000, msec % 1000
    );
}

int main(int argc, char** argv) {

    init_random();
    run_all();

    return 0;
}
