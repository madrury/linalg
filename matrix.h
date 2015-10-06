#pragma once
#include "vector.h"

struct matrix {
    struct linalg_obj la_obj;
    int n_row;
    int n_col;
};

struct matrix* matrix_new(int n_row, int n_col);
struct matrix* matrix_from_array(double* data, int n_row, int n_col);
void           matrix_free(struct matrix* M);

struct vector* matrix_row_view(struct matrix* M, int row);
struct vector* matrix_row_copy(struct matrix* M, int row);
/* No column view, columns are not contiguous memory */
struct vector* matrix_column_copy(struct matrix* M, int col);

void           matrix_copy_vector_into_row(struct matrix* M, struct vector* v, int row);
void           matrix_copy_vector_into_column(struct matrix* M, struct vector* v, int col);

struct matrix* matrix_zeros(int n_row, int n_col);
struct matrix* matrix_identity(int size);

struct matrix* matrix_transpose(struct matrix* M);
struct matrix* matrix_multiply(struct matrix* Mleft, struct matrix* Mright);

void           matrix_print(struct matrix*);


struct qr_decomp {
    struct matrix* q;
    struct matrix* r;
};

struct qr_decomp* qr_decomp_new(struct matrix* M);
void              qr_decomp_free(struct qr_decomp* qr);

struct qr_decomp* matrix_qr_decomposition(struct matrix* M);
