#include <assert.h>
#include <stdlib.h>
#include "vector.h"
#include "matrix.h"
#include "eigen.h"

struct eigen* eigen_new() {
    struct eigen* e = malloc(sizeof(struct eigen));
    return e;
}

void eigen_free(struct eigen* e) {
    vector_free(e->eigenvalues);
    // matrix_free(e->eigenvectors);
    free(e); 
}

/* Solve for the eigendecomposition of a square matrix using the QR algorithm. */
struct eigen* eigen_solve(struct matrix* M, double tol, int max_iter) {
    struct vector* eigenvalues = eigen_solve_eigenvalues(M, tol, max_iter);
    // struct matrix* eigenvectors = eigen_solve_eigenvectors(M, eigenvalues);

    struct eigen* e = eigen_new();
    e->n = M->n_row;
    e->eigenvalues = eigenvalues;
    // e->eigenvectors = eigenvectors;

    return e;
}

struct vector* eigen_solve_eigenvalues(struct matrix* M, double tol, int max_iter) {
    //TODO: This can be made more efficient by mutiplying *into* already
    //allocated memory.
    struct matrix* X = matrix_copy(M);
    int i = 0;
    // QR algorithm for eigenvalues.
    do {
        struct qr_decomp* qr = matrix_qr_decomposition(X);
        matrix_multiply_into(X, qr->r, qr->q);
        qr_decomp_free(qr);
        i++;
    } while(!matrix_is_upper_triangular(X, tol) && (i < max_iter));

    return matrix_diagonal(X);
}
