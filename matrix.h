#pragma once
#include <stdarg.h>
#include "linalg_obj.h"
#include "vector.h"

struct matrix {
    struct linalg_obj la_obj;
    int n_row;
    int n_col;
};


#ifndef _MATRIX_MACROS
#define _MATRIX_MACROS
#define MATRIX_ROW(M, i) ((i) / (M->n_row))
#define MATRIX_COL(M, i) ((i) % (M->n_row))
#define MATRIX_IDX(M, r, c) (((r) * (M->n_col)) + (c))
#define MATRIX_IDX_INTO(M, r, c) (DATA(M)[MATRIX_IDX(M, r, c)])
#endif


struct matrix* matrix_new(int n_row, int n_col);
struct matrix* matrix_from_array(double* data, int n_row, int n_col);
void           matrix_free(struct matrix* M);
void           matrix_free_many(int n_to_free, ...);

struct matrix* matrix_copy(struct matrix* M);

struct vector* matrix_row_view(struct matrix* M, int row);
struct vector* matrix_row_copy(struct matrix* M, int row);
/* No column view, columns are not contiguous memory */
struct vector* matrix_column_copy(struct matrix* M, int col);

struct vector* matrix_diagonal(struct matrix* M);

void           matrix_copy_vector_into_row(struct matrix* M, struct vector* v, int row);
void           matrix_copy_vector_into_column(struct matrix* M, struct vector* v, int col);

struct matrix* matrix_zeros(int n_row, int n_col);
struct matrix* matrix_identity(int size);

struct matrix* matrix_transpose(struct matrix* M);
struct matrix* matrix_multiply_cache(struct matrix* Mleft, struct matrix* Mright, int cache);
struct matrix* matrix_multiply(struct matrix* Mleft, struct matrix* Mright);
void           matrix_multiply_into(struct matrix* reciever,
                                    struct matrix* Mleft, struct matrix* Mright);
struct matrix* matrix_multiply_MtN(struct matrix* Mleft, struct matrix* Mright);
struct vector* matrix_vector_multiply(struct matrix* M, struct vector* v);
struct vector* matrix_vector_multiply_Mtv(struct matrix* M, struct vector* v);

struct matrix* matrix_M_minus_lambda_I(struct matrix* M, double lambda);

bool           matrix_equal(struct matrix* M1, struct matrix* M2, double tol);
bool           matrix_is_upper_triangular(struct matrix* M, double tol);

void           matrix_print(struct matrix*);


/* Matrix decomposition: QR decomposition. */
struct qr_decomp {
    struct matrix* q;
    struct matrix* r;
};

struct qr_decomp* qr_decomp_new(struct matrix* M);
void              qr_decomp_free(struct qr_decomp* qr);

struct qr_decomp* matrix_qr_decomposition(struct matrix* M);
