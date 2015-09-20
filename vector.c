#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

struct vector* vector_new(int length) {
    struct vector* new_vector = malloc(sizeof(struct vector));
    new_vector->length = length;
    new_vector->data = malloc((sizeof(double))*length);
    return new_vector;
}

void vector_free(struct vector* v) {
    free(v->data);
    free(v);
}

struct vector* vector_zeros(int length) {
    struct vector* v = vector_new(length);
    for(int i = 0; i < v->length; i++) {
        v->data[i] = 0;
    }
    return v;
}

struct vector* vector_linspace(int length, double min, double max) {
    struct vector* v = vector_new(length);
    double step = (max - min) / (length - 1);
    for(int i = 0; i < v->length; i++) {
        v->data[i] = min + step*i;
    }
    return v;
}

struct vector* vector_from_array(int length, double *data) {
    struct vector* v = vector_new(length);
    for(int i = 0; i < v->length; i++) {
        v->data[i] = data[i];
    }
    return v;
}

struct vector* vector_subtract(struct vector* v1, struct vector* v2) {
    // TODO: Check vector lengths.
    struct vector* v = vector_new(v1->length);
    for(int i = 0; i < v->length; i++) {
        v->data[i] = v1->data[i] - v2->data[i];
    }
    return v;
}

struct vector* vector_add(struct vector* v1, struct vector* v2) {
    // TODO: Check vector lengths.
    struct vector* v = vector_new(v1->length);
    for(int i = 0; i < v->length; i++) {
        v->data[i] = v1->data[i] + v2->data[i];
    }
    return v;
}

double vector_dot_product(struct vector* v1, struct vector* v2) {
    // TODO: Check vector lengths.
    double dp = 0;
    for(int i = 0; i < v1->length; i++) {
        dp += v1->data[i] * v2->data[i];
    }
    return dp;
}

void vector_print(struct vector* v) {
    double* v_data = v->data;
    printf("[%.2f", v_data[0]);
    for(int i = 1; i < v->length - 1; i++) {
        printf(", ");
        printf("%.2f", v_data[i]);
    }
    printf(", %.2f]\n", v_data[v->length - 1]);
}
