#include <assert.h>
#include "vector.h"
#include "matrix.h"
#include "eigen.h"

struct eigen* eigen_new() {
    struct eigen* e = malloc(sizeof(struct eigen));
    return e;
}

struct eigen_free(eigen* e) {
    vector_free(e->eigenvalues);
    // matrix_free(e->eigenvectors);
    free(e); 
}

/* Solve for the eigendecomposition of a square matrix using the QR algorithm. */
struct eigen* eigen_solve(matrix* M, double tol, int max_iter) {
    struct vector* eigenvalues = eigen_solve_eigenvalues(M, tol, max_iter);
    // struct matrix* eigenvectors = eigen_solve_eigenvectors(M, eigenvalues);

    struct eigen* e = eigen_new();
    e->n = M->n_row;
    e->eigenvalues = eigenvalues;
    // e->eigenvectors = eigenvectors;

    return e;
}

struct vector* eigen_solve_eigenvalues(matrix* M, double tol, int max_iter);
    //TODO: This can be made more efficient by mutiplying *into* already
    //allocated memory.
    struct matrix* X = matrix_zeros(M->n_row, M->n_col);
    do {
        struct qr_decomp* qr = matrix_qr_decomposition(M);
        matrix_multiply_into(X, qr->r, qr->q);
        qr_decomp_free(qr);
    } while(!matrix_is_upper_triangular(X));

    return matrix_diagonal(X);
}
