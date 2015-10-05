#pragma once
#include "vector.h"

struct matrix {
    struct linalg_obj la_obj;
    int n_row;
    int n_col;
};

struct matrix* matrix_new(int n_row, int n_col);
struct matrix* matrix_from_array(double* data, int n_row, int n_col);
struct vector* matrix_row_view(struct matrix* M, int row);
void           matrix_free(struct matrix* M);

struct matrix* matrix_zeros(int n_row, int n_col);
struct matrix* matrix_identity(int size);

struct matrix* matrix_transpose(struct matrix* M);

void           matrix_print(struct matrix*);
