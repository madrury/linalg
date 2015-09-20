#pragma once

struct vector {
    double* data;
    int length;
};

struct vector* vector_new(int length);
void           vector_free(struct vector*);

struct vector* vector_zeros(int length);
struct vector* vector_linspace(int length, double min, double max);
struct vector* vector_from_array(int length, double* data);

struct vector* vector_subtract(struct vector* v1, struct vector* v2);
struct vector* vector_add(struct vector* v1, struct vector* v2);

double         vector_dot_product(struct vector* v1, struct vector* v2);

void           vector_print(struct vector*);

