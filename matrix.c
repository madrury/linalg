#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "matrix.h"
#include "vector.h"
#include "errors.h"
#include "util.h"


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

struct matrix* matrix_zeros(int n_row, int n_col) {
    struct matrix* M = matrix_new(n_row, n_col);
    for(int i = 0; i < n_row * n_col; i++) {
        DATA(M)[i] = 0;
    }
    return M;
}

struct matrix* matrix_identity(int size) {
    struct matrix* M = matrix_new(size, size);
    int row, col;
    for(int i = 0; i < size * size; i++) {
        row = i / size;
        col = i % size;
        if(row == col) {
            DATA(M)[i] = 1;
        } else {
            DATA(M)[i] = 0;
        }
    }
    return M;
}

struct vector* matrix_row_view(struct matrix* M, int row) {
    double* row_p = DATA(M) + (row * M->n_col);
    struct vector* r = vector_new_view((struct linalg_obj*) M, row_p, M->n_col);
    return r;
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
