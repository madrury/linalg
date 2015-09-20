#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "vector.h"
#include "errors.c"
#include "util.c"

struct vector* vector_new(int length) {
    struct vector* new_vector = malloc(sizeof(struct vector));
    check_memory((void*)new_vector);

    new_vector->data = malloc((sizeof(double))*length);
    check_memory((void*)new_vector->data);

    new_vector->length = length;
    new_vector->owns_memory = true;
    new_vector->memory_owner = NULL;
    new_vector->ref_count = 0;
    return new_vector;
}

struct vector* vector_new_view(int length, struct vector* parent, double* view) {
    struct vector* new_vector = malloc(sizeof(struct vector));
    check_memory((void*)new_vector);

    new_vector->data = view;
    new_vector->length = length;
    new_vector->owns_memory = false;
    new_vector->memory_owner = parent;
    new_vector->ref_count = 0;

    parent->ref_count += 1;

    return new_vector;
}

void vector_free(struct vector* v) {
    if(v->owns_memory) {
        if(v->ref_count == 0) {
            free(v->data);
            free(v);
        } else {
            raise_non_zero_reference_free_error();
        }
    } else {
        if(v->ref_count == 0) {
            v->memory_owner->ref_count -= 1;
            free(v);
        } else {
            raise_non_zero_reference_free_error();
        }
    }
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
    _vector_check_lengths(v1, v2);
    struct vector* v = vector_new(v1->length);
    for(int i = 0; i < v->length; i++) {
        v->data[i] = v1->data[i] - v2->data[i];
    }
    return v;
}

struct vector* vector_add(struct vector* v1, struct vector* v2) {
    _vector_check_lengths(v1, v2);
    struct vector* v = vector_new(v1->length);
    for(int i = 0; i < v->length; i++) {
        v->data[i] = v1->data[i] + v2->data[i];
    }
    return v;
}

double vector_dot_product(struct vector* v1, struct vector* v2) {
    _vector_check_lengths(v1, v2);
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

void _vector_check_lengths(struct vector* v1, struct vector* v2) {
    if(v1->length != v2->length) {
        raise_non_commensurate_vector_error();
    }
}
