#pragma once

struct vector {
    double* data;
    int length;
};

struct vector* vector_new(int length);
void           vector_free(struct vector*);
struct vector* vector_zeros(int length);
struct vector* vector_from_array(int length, double* data);
void           vector_print(struct vector*);
