#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "matrix.h"
#include "vector.h"
#include "errors.h"
#include "util.h"


#define MATRIX_ROW(M, i) ((i) / (M->n_row))
#define MATRIX_COL(M, i) ((i) % (M->n_row))
#define MATRIX_IDX(M, r, c) (((r) * (M->n_col)) + (c))
#define MATRIX_IDX_INTO(M, r, c) (DATA(M)[MATRIX_IDX(M, r, c)])


struct matrix* matrix_new(int n_row, int n_col) {
    // TODO: Check that n_row and n_col are reasonable.
    struct matrix* new_matrix = malloc(sizeof(struct matrix));
    check_memory((void*)new_matrix);

    DATA(new_matrix) = malloc((sizeof(double)) * n_row * n_col);
    check_memory((void*) DATA(new_matrix));

    new_matrix->n_row = n_row;
    new_matrix->n_col = n_col;
    OWNS_MEMORY(new_matrix) = true;
    MEMORY_OWNER(new_matrix) = NULL;
    REF_COUNT(new_matrix) = 0;

    return new_matrix;
}

struct matrix* matrix_from_array(double* data, int n_row, int n_col) {
    struct matrix* M = matrix_new(n_row, n_col);
    for(int i = 0; i < n_row * n_col; i++) {
        DATA(M)[i] = data[i];
    }
    return M;
}

void matrix_free(struct matrix* M) {
    struct linalg_obj* mem_owner;
    if(OWNS_MEMORY(M)) {
        if(REF_COUNT(M) == 0) {
            free(DATA(M));
            free(M);
        } else {
            raise_non_zero_reference_free_error();
        }
    } else {
        if(REF_COUNT(M) == 0) {
            mem_owner = MEMORY_OWNER(M);
            REF_COUNT(mem_owner) -= 1;
            free(M);
        } else {
            raise_non_zero_reference_free_error();
        }
    }
}

struct vector* matrix_row_view(struct matrix* M, int row) {
    //TODO: Check that row is in bounds.
    double* row_p = DATA(M) + (row * M->n_col);
    struct vector* r = vector_new_view((struct linalg_obj*) M, row_p, M->n_col);
    return r;
}

struct vector* matrix_row_copy(struct matrix* M, int row) {
    //TODO: Check that row is in bounds.
    struct vector* r = vector_new(M->n_col);
    for(int i = 0; i < M->n_col; i++) {
        DATA(r)[i] = MATRIX_IDX_INTO(M, row, i);
    }
    return r;
}

struct matrix* matrix_zeros(int n_row, int n_col) {
    struct matrix* M = matrix_new(n_row, n_col);
    for(int i = 0; i < n_row * n_col; i++) {
        DATA(M)[i] = 0;
    }
    return M;
}

struct matrix* matrix_identity(int size) {
    struct matrix* M = matrix_new(size, size);
    for(int i = 0; i < size * size; i++) {
        if(MATRIX_ROW(M, i) == MATRIX_COL(M, i)) {
            DATA(M)[i] = 1;
        } else {
            DATA(M)[i] = 0;
        }
    }
    return M;
}

struct matrix* matrix_transpose(struct matrix* M) {
    struct matrix* Mt = matrix_new(M->n_col, M->n_row);
    for(int i = 0; i < M->n_row * M->n_col; i++) {
         DATA(Mt)[i] = DATA(M)[MATRIX_IDX(M, MATRIX_COL(Mt, i), MATRIX_ROW(Mt, i))];
    }
    return Mt;
}

struct matrix* matrix_multiply(struct matrix* Mleft, struct matrix* Mright) {
    //TODO: Check that dimenstions are commensurate.
    struct matrix* Mprod = matrix_new(Mleft->n_row, Mright->n_col);
    double sum;
    for(int i = 0; i < Mprod->n_row; i++) {
        for(int j = 0; j < Mprod->n_col; j++) {
            sum = 0;
            for(int k = 0; k < Mleft->n_col; k++) {
                sum += MATRIX_IDX_INTO(Mleft, i, k) * MATRIX_IDX_INTO(Mright, k, j);
            }
            MATRIX_IDX_INTO(Mprod, i, j) = sum;
        }
    }
    return Mprod;
}

void matrix_print(struct matrix* M) {
    struct vector* current_row;
    printf("[\n");
    for(int i = 0; i < M->n_row; i++) {
        printf("  ");
        current_row = matrix_row_view(M, i);
        vector_print(current_row);
        vector_free(current_row);
    }
    printf("]\n");
}


//struct qr_decomp* qr_decomp_new(struct matrix* M) {
//    struct qr_decomp*  qr = malloc(sizeof(struct qr_decomp));
//    return qr;
//}
//
//void qr_decomp_free(struct qr_decomp* qr) {
//    matrix_free(qr->q);
//    matrix_free(qr->r);
//    free(qr);
//}
//
//struct qr_decomp* matrix_qr_decomposition(struct matrix* M) {
//    //TODO: Check that M is a square matrix.
//    struct qr_decomp* qr = qr_decomp_new(struct matrix* M);
//    struct matrix* q = matrix_new(M->n_row, M->n_row);
//    struct matrix* r = matrix_new(M->n_row, M->n_row);
//    struct matrix* Mtr = matrix_transpose(M);
//    struct matrix* qtr = matrix_new(M->n_row, M->n_row);
//    struct vector* current_projection;
//    struct vector* current_unit_vector;
//
//
//}
