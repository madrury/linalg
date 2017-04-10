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

/* Compute the eigenvalues and eigenvectors of a matrix M.

  The eigenvalues are computed using the QR algorithm, then the eigenvectors
  are computed by inverse iteration.
*/
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

/* Compute the eigenvalues of a matrix using the QR algorithm.

  This is a renormalized version of power iteration that converges to a full
  set of eigenvalues.  Starting with the matrix M = M0, we iterate:

    M0 = Q0 R0, M1 = R0 Q0;
    M1 = Q1 R1, M2 = R1 Q1;
    M2 = Q2 R2, M3 = R2 Q2;
    ...

  For a general matrix with a full set of eigenvalues, this sequence will
  converge to an upper diagonal matrix:

    Mi -> upper diagonal matrix

  The diagonal entries of this matrix are the eigenvalues of M.
*/
struct vector* eigen_solve_eigenvalues(struct matrix* M,
                                       double tol,
                                       int max_iter) {

    assert(M->n_row == M->n_col);

    struct matrix* X = matrix_copy(M);
    int i = 0;
    // QR algorithm iterations.
    do {
        struct qr_decomp* qr = matrix_qr_decomposition(X);
        matrix_multiply_into(X, qr->r, qr->q);
        qr_decomp_free(qr);
        i++;
    } while(!matrix_is_upper_triangular(X, tol) && (i < max_iter));

    return matrix_diagonal(X);
}

/* Solve for the eigenvectors of a matrix M once the eigenvalues are known
   using inverse iteration.
*/
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

/* Solve for the eigenvector associated with an eigenvalue using the inverse
   iteration algorithm.

  Given an approximate eigenvalue lambda, the inverse iteration algorithm
  computes the matrix:

    M' = M - lambda I

  And then solves the following sequence of linear equations:

    v0 = solve(M', random_vector), v0' = normalize(v0);
    v1 = solve(M', v0'), v1' = normalize(v1);
    v2 = solve(<', v1'), v2' = normalize(v2);
    ...

  This algorithm will converge to the eigenvector associated with the eigenvalue
  closest to lambda.
*/
struct vector* eigen_backsolve(
                   struct matrix* M, double eigenvalue, double tol, int max_iter) {

    struct vector* current = vector_constant(M->n_row, 1);
    struct vector* previous;
    // Preturb the eigenvalue a litle to prevent our right hand side matrix
    // from becoming singular.
    double lambda = eigenvalue + ((double) rand() / (double) RAND_MAX) * 0.000001; 
    
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
