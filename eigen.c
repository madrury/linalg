#include <assert.h>
#include <stdlib.h>
#include "vector.h"
#include "matrix.h"
#include "eigen.h"
#include "linsolve.h"

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
    assert(M->n_row == M->n_col);

    struct vector* eigenvalues = eigen_solve_eigenvalues(M, tol, max_iter);
    struct matrix* eigenvectors = eigen_solve_eigenvectors(
                                      M, eigenvalues, tol, max_iter);

    struct eigen* e = eigen_new();
    e->n = M->n_row;
    e->eigenvalues = eigenvalues;
    e->eigenvectors = eigenvectors;

    return e;
}

struct vector* eigen_solve_eigenvalues(struct matrix* M,
                                       double tol,
                                       int max_iter) {

    assert(M->n_row == M->n_col);

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

struct matrix* eigen_solve_eigenvectors(struct matrix* M,
                                        struct vector* eigenvalues,
                                        double tol,
                                        int max_iter) {

    assert(eigenvalues->length = M->n_row);
    assert(eigenvalues->length = M->n_col);

    double eigenvalue;
    int n_eigenvalues = M->n_col;
    struct matrix* eigenvectors = matrix_new(n_eigenvalues, n_eigenvalues); 
    
    for(int i = 0; i < n_eigenvalues; i++) {
        eigenvalue = VECTOR_IDX_INTO(eigenvalues, i);
        struct vector* eigenvector = eigen_backsolve(M, eigenvalue, tol, max_iter); 
        matrix_copy_vector_into_column(eigenvectors, eigenvector, i);
        vector_free(eigenvector);
    }

    return eigenvectors;
}

struct vector* eigen_backsolve(
                   struct matrix* M, double eigenvalue, double tol, int max_iter) {

    struct vector* current = vector_constant(M->n_row, 1);
    struct vector* previous;
    // Preturb the eigenvalue a litle to prevent our right hand side matrix
    // from becoming singular.
    double lambda = eigenvalue + ((double) rand() / (double) RAND_MAX) * 0.001; 
    
    struct matrix* M_minus_lambda_I = matrix_M_minus_lambda_I(M, lambda);

    double i = 0;
    do {
        if(i > 0) {
            vector_free(previous);
        }
        previous = current;
        current = linsolve_qr(M_minus_lambda_I, previous);
        // We reverse the sign of the vector if the first entry is not positive.
        // Often the algorithm will oscilate between a vector and its negative
        // after convergence.
        if(VECTOR_IDX_INTO(current, 0) < 0) {
            for(int j = 0; j < current->length; j++) {
                VECTOR_IDX_INTO(current, j) = -VECTOR_IDX_INTO(current, j);
            }
        }
        vector_normalize_into(current, current);
        // vector_print(current);
        i++;
    } while(!vector_equal(current, previous, tol) && (i < max_iter));

    vector_free(previous);
    return current;
}
