#pragma once
#include <stdbool.h>
#include "linalg_obj.h"

struct vector {
    struct linalg_obj la_obj;
    int length;
};

struct vector* vector_new(int length);
struct vector* vector_new_view(int length, double* view, struct vector* parent);
void           vector_free(struct vector*);

struct vector* vector_zeros(int length);
struct vector* vector_linspace(int length, double min, double max);
struct vector* vector_from_array(int length, double* data);
struct vector* vector_slice(int begin_idx, int end_idx, struct vector* v);

struct vector* vector_subtract(struct vector* v1, struct vector* v2);
void           vector_subtract_into(struct vector* v1, struct vector* v2);
struct vector* vector_add(struct vector* v1, struct vector* v2);
void           vector_add_into(struct vector* v1, struct vector* v2);

double         vector_dot_product(struct vector* v1, struct vector* v2);

void           vector_print(struct vector*);

void           _vector_check_lengths(struct vector* v1, struct vector* v2);
