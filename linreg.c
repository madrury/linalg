#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"
#include "vector.h"
#include "linsolve.h"
#include "linreg.h"

/* Linear Regression.

  Fit and score a linear regression to a design matrix X and a response vector y.
  The regression is fit by solving the following linear equation for b:

      Xt X b = Xt y
*/

struct linreg* linreg_new(void) {
    struct linreg* lr = malloc(sizeof(struct linreg));
    return lr;
}

void linreg_free(struct linreg* lr) {
    vector_free(lr->beta);
    vector_free(lr->y_hat);
    free(lr);
}

/* Solve a linear regression problem using the qr decomposition of the matrix X.

  The idea here is that if X = QR, then the linear regression equations reduce
  to R b = Q^t y.
*/
struct linreg* linreg_fit(struct matrix* X, struct vector* y) {
    assert(X->n_row == y->length);
    struct linreg* lr = linreg_new();
    lr->n = X->n_row;
    lr->p = X->n_col;

    // Solve linear equation for the regression coefficients.
    struct qr_decomp* qr = matrix_qr_decomposition(X);
    struct vector* qtv = matrix_vector_multiply_Mtv(qr->q, y);
    lr->beta = linsolve_upper_triangular(qr->r, qtv);

    // Calculate the residual standard deviation.
    struct vector* y_hat = linreg_predict(lr, X);
    double sigma_resid_sq = 0; double resid = 0;
    for(int i = 0; i < y->length; i++) {
        resid = VECTOR_IDX_INTO(y, i) - VECTOR_IDX_INTO(y_hat, i);
        sigma_resid_sq += resid * resid;
    }
    double norm_factor = 1 / (lr->n - lr->p - 1);
    double sigma_resid = sqrt(norm_factor * sigma_resid_sq);
    lr->y_hat = y_hat;
    lr->sigma_resid = sigma_resid;

    qr_decomp_free(qr);
    vector_free(qtv);

    return lr;
}

struct vector* linreg_predict(struct linreg* lr, struct matrix* X) {
    assert(lr->n == X->n_row);
    assert(lr->p == X->n_col);
    struct vector* preds = matrix_vector_multiply(X, lr->beta);
    return preds;
}
