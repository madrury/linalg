#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

struct vector* vector_new(int length) {
    struct vector* new_vector = malloc(sizeof(struct vector));
    new_vector->length = length;
    new_vector->data = malloc((sizeof(float))*length);
    return new_vector;
}

void vector_free(struct vector* v) {
    free(v->data);
    free(v);
}

struct vector* vector_zeros(int length) {
    struct vector* v = vector_new(length);
    double* v_data = v->data;
    for(int i = 0; i < v->length; i++) {
        v_data[i] = 0;
    }
    return v;
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
