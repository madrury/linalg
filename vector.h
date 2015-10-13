#pragma once
#include <stdbool.h>
#include "linalg_obj.h"

#ifndef _VECTOR_MACROS
#define _VECTOR_MACROS
#define VECTOR_IDX_INTO(v, i) (DATA(v)[i])
#endif


struct vector {
    struct linalg_obj la_obj;
    int length;
};

struct vector* vector_new(int length);
struct vector* vector_new_view(struct linalg_obj* parent, double* view, int length);
struct vector* vector_from_array(double* data, int length);
void           vector_free(struct vector*);

struct vector* vector_zeros(int length);
struct vector* vector_linspace(int length, double min, double max);
struct vector* vector_slice(struct vector* v, int begin_idx, int end_idx);
struct vector* vector_copy(struct vector* v);

struct vector* vector_subtract(struct vector* v1, struct vector* v2);
void           vector_subtract_into(struct vector* v1, struct vector* v2);
struct vector* vector_add(struct vector* v1, struct vector* v2);
void           vector_add_into(struct vector* v1, struct vector* v2);
struct vector* vector_normalize(struct vector* v);
void           vector_normalize_into(struct vector* v);
struct vector* vector_scalar_multiply(struct vector* v, double s);
void           vector_scalar_multiply_into(struct vector* v, double s);

bool           vector_equal(struct vector* v1, struct vector* v2, double tol);

double         vector_dot_product(struct vector* v1, struct vector* v2);
double         vector_norm(struct vector* v);

void           vector_print(struct vector*);

void _vector_check_lengths(struct vector* v1, struct vector* v2);
