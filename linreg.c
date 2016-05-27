#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"
#include "vector.h"
#include "linsolve.h"
#include "linreg.h"

struct linreg* linreg_new(void) {
    struct linreg* lr = malloc(sizeof(struct linreg));
    return lr;
}

void linreg_free(struct linreg* lr) {
    vector_free(lr->beta);
    vector_free(lr->y_hat);
    free(lr);
}

struct linreg* linreg_fit(struct matrix* X, struct vector* y) {
    // TODO: Check dimensionality.
    struct linreg* lr = linreg_new();
    lr->n = X->n_row;
    lr->p = X->n_col;

    // Solve the linear equation Xt * X = Xt y for the linear regression coefficients.
    struct vector* Xty = matrix_vector_multiply_Mtv(X, y);
    struct matrix* XtX = matrix_multiply_MtN(X, X);
    struct qr_decomp* qr = matrix_qr_decomposition(XtX);
    struct vector* beta = linsolve_from_qr(qr, Xty);
    lr->beta = beta;

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
    vector_free(Xty);
    matrix_free(XtX);

    return lr;
}

struct vector* linreg_predict(struct linreg* lr, struct matrix* X) {
    // TODO: Check dimensionality.
    struct vector* preds = matrix_vector_multiply(X, lr->beta);
    return preds;
}
