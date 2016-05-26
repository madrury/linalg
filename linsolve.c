#include <assert.h>
#include "vector.h"
#include "matrix.h"
#include "linsolve.h"

/* Solve a general linear equation Mx = v using the QR decomposition of M.

   If QR is the decomposion of M, then using the fact that Q is orthogonal

     QRx = v => Rx = transpose(Q)v

   The matrix product transpose(Q)v is easy to compute, so the docomposition
   reduces the problem to solving a linear equation Rx = y for an upper
   triangular matrix R.
  
*/
struct vector* linsolve_qr(struct matrix* M, struct vector* v) {
    assert(M->n_row == v->length);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    struct vector* rhs = matrix_vector_multiply_Mtv(qr->q, v);
    struct vector* solution = solve_upper_triangular(qr->r, rhs);
    vector_free(rhs);
    qr_decomp_free(qr);
    return solution;
}

/* Solve a linear equation Rx = v, where R is an upper triangular matrix.

   This type of equation is easy to solve by back substitution.  We work *up*
   the rows of R solving for the components of x backwards.  For example, the
   final row in R gives the equation

     r_{l,l} x_l = v_l

   whose solution is simply x_l = v_l / r_{l,l}.  The second to final row gives
   the equation

     r_(l-1,l-1} x_{l-1} + r_{l-1,l} x_{l} = v_l

   which can be solved by substituting in the value of x_l already found, and
   then solving the resulting equation for x_{l-1}.  Continuing in this way
   solves the entire system.
*/ 
struct vector* solve_upper_triangular(struct matrix* R, struct vector* v) {
    assert(R->n_col == v->length);
    assert(R->n_row = R->n_col);
    // TODO: Check upper triangular.
    int n_eq = v->length;
    struct vector* solution = vector_new(n_eq);
    /* back_substitute:
       Tracks the part of the current equation (row) that reduces to a constant
       after substituting in the values for the already solved for varaiables.
    */
    float back_substitute;

    for(int i = n_eq - 1; i >= 0; i--) {
        back_substitute = 0;
        for(int j = i+1; j <= n_eq - 1; j++) {
            back_substitute += VECTOR_IDX_INTO(solution, j) * MATRIX_IDX_INTO(R, i, j);
        }
        VECTOR_IDX_INTO(solution, i) =
            (VECTOR_IDX_INTO(v, i) - back_substitute) / MATRIX_IDX_INTO(R, i, i);
    }
    return solution;
}

