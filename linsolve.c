#include <assert.h>
#include "vector.h"
#include "matrix.h"

struct vector* solve_upper_triangular(struct matrix* M, struct vector* v) {
    assert(M->n_col == v->length);
    assert(M->n_row = M->n_col);
    // TODO: Check upper triangular.
    int n_eq = v->length;
    struct vector* solution = vector_new(n_eq);
    float back_substitute;

    // Loop over equations
    for(int i = n_eq - 1; i >= 0; i--) {
        // Back substitute already solved for coordiantes into the current
        // equation.
        back_substitute = 0;
        for(int j = i+1; j <= n_eq - 1; j++) {
                back_substitute += VECTOR_IDX_INTO(solution, j) * MATRIX_IDX_INTO(M, i, j);
        }
        VECTOR_IDX_INTO(solution, i) =
            (VECTOR_IDX_INTO(v, i) - back_substitute) / MATRIX_IDX_INTO(M, i, i);
    }
    return solution;
}

struct vector* linsolve_qr(struct matrix* M, struct vector* v) {
    assert(M->n_row == v->length);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    struct vector* rhs = matrix_vector_multiply_Mtv(qr->q, v);
    struct vector* solution = solve_upper_triangular(qr->r, rhs);
    vector_free(rhs);
    qr_decomp_free(qr);
    return solution;
}
