#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include "linalg_obj.h"
#include "vector.h"
#include "errors.h"
#include "util.h"

struct vector* vector_new(int length) {
    assert(length >= 0);

    struct vector* new_vector = malloc(sizeof(struct vector));
    check_memory((void*)new_vector);

    DATA(new_vector) = malloc((sizeof(double))*length);
    check_memory((void*) DATA(new_vector));

    new_vector->length = length;
    OWNS_MEMORY(new_vector)= true;
    MEMORY_OWNER(new_vector) = NULL;
    REF_COUNT(new_vector) = 0;

    return new_vector;
}

struct vector* vector_new_view(struct linalg_obj* parent, double* view, int length) {
    assert(length >= 0);
    /* Check that pointers to the beginning and end of view vector live
       within the data segment of the parent object.

       This doesn't work because matricies have no length.  This could be
       a property of linalg_obj, but then a macro would be needed to
       make the lookup type generic.
       
    assert(DATA(parent) <= view && view < DATA(parent) + parent->length);
    assert(view + length <= DATA(parent) + parent->length);
    */

    struct vector* new_vector = malloc(sizeof(struct vector));
    check_memory((void*)new_vector);

    DATA(new_vector) = view;
    new_vector->length = length;
    OWNS_MEMORY(new_vector) = false;
    MEMORY_OWNER(new_vector) = parent;
    REF_COUNT(new_vector) = 0;
    REF_COUNT(parent) += 1;

    return new_vector;
}

struct vector* vector_from_array(double* data, int length) {
    assert(length != 0);
    struct vector* v = vector_new(length);
    for(int i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(v, i) = data[i];
    }
    return v;
}

void vector_free(struct vector* v) {
    struct linalg_obj* mem_owner;
    if(OWNS_MEMORY(v)) {
        if(REF_COUNT(v)== 0) {
            free(DATA(v));
            free(v);
        } else {
            raise_non_zero_reference_free_error();
        }
    } else {
        if(REF_COUNT(v) == 0) {
            mem_owner = MEMORY_OWNER(v);
            REF_COUNT(mem_owner) -= 1;
            free(v);
        } else {
            raise_non_zero_reference_free_error();
        }
    }
}

void vector_free_many(int n_to_free, ...) {
    struct vector* v;
    va_list argp;
    va_start(argp, n_to_free);
    for(int i = 0; i < n_to_free; i++) {
        v = va_arg(argp, struct vector*);
        vector_free(v);
    }
}

struct vector* vector_zeros(int length) {
    struct vector* v = vector_new(length);
    for(int i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(v, i) = 0;
    }
    return v;
}

/* Construct a vector of equally spaced points within the closed
   interval [min, max].
*/
struct vector* vector_linspace(int length, double min, double max) {
    assert(min <= max);
    assert(length > 1);
    struct vector* v = vector_new(length);
    double step = (max - min) / (length - 1);
    for(int i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(v, i) = min + step*i;
    }
    return v;
}

/* Construct a view into a segement of a vector.  The returned vector is
   a reference to a segment of data contained in the vector v, with left
   index begin_idx and right index (excluded) end_idx.
*/
struct vector* vector_slice(struct vector* v, int begin_idx, int end_idx) {
    assert(begin_idx <= end_idx);
    int new_vector_length = end_idx - begin_idx;
    double* begin_ptr = DATA(v) + begin_idx;
    struct vector* w = vector_new_view((struct linalg_obj*) v, begin_ptr, new_vector_length);
    return w;
}

struct vector* vector_copy(struct vector* v) {
    struct vector* w = vector_new(v->length);
    for(int i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(w, i) = VECTOR_IDX_INTO(v, i);
    }
    return w;
}

struct vector* vector_subtract(struct vector* v1, struct vector* v2) {
    assert(vector_lengths_equal(v1, v2));
    struct vector* v = vector_new(v1->length);
    for(int i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(v, i) = VECTOR_IDX_INTO(v1, i) - VECTOR_IDX_INTO(v2, i);
    }
    return v;
}

void vector_subtract_into(struct vector* v1, struct vector* v2) {
    assert(vector_lengths_equal(v1, v2));
    for(int i = 0; i < v1->length; i++) {
        VECTOR_IDX_INTO(v1, i) = VECTOR_IDX_INTO(v1, i) - VECTOR_IDX_INTO(v2, i);
    }
}

struct vector* vector_add(struct vector* v1, struct vector* v2) {
    assert(vector_lengths_equal(v1, v2));
    struct vector* v = vector_new(v1->length);
    for(int i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(v, i) = VECTOR_IDX_INTO(v1, i) + VECTOR_IDX_INTO(v2, i);
    }
    return v;
}

void vector_add_into(struct vector* v1, struct vector* v2) {
    assert(vector_lengths_equal(v1, v2));
    for(int i = 0; i < v1->length; i++) {
        VECTOR_IDX_INTO(v1, i) = VECTOR_IDX_INTO(v1, i) + VECTOR_IDX_INTO(v2, i);
    }
}

struct vector* vector_normalize(struct vector* v) {
    struct vector* vnorm = vector_new(v->length);
    double norm = vector_norm(v);
    assert(norm != 0);
    for(int i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(vnorm, i) = VECTOR_IDX_INTO(v, i) / norm;
    }
    return vnorm;
}

void vector_normalize_into(struct vector* v) {
    double norm = vector_norm(v);
    assert(norm != 0);
    for(int i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(v, i) = VECTOR_IDX_INTO(v, i) / norm;
    }
}

struct vector* vector_scalar_multiply(struct vector* v, double s) {
    struct vector* w = vector_new(v->length);
    for(int i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(w, i) = VECTOR_IDX_INTO(v, i) * s;
    }
    return w;
}

bool vector_equal(struct vector* v1, struct vector* v2, double tol) {
    if(v1->length != v2->length) {
        return false;
    }
    for(int i = 0; i < v1->length; i++) {
        if(fabs(VECTOR_IDX_INTO(v1, i) - VECTOR_IDX_INTO(v2, i)) > tol) {
            return false;
        }
    }
    return true;
}

void vector_scalar_multiply_into(struct vector* v, double s) {
    for(int i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(v, i) = VECTOR_IDX_INTO(v, i) * s;
    }
}

double vector_dot_product(struct vector* v1, struct vector* v2) {
    assert(vector_lengths_equal(v1, v2));
    double dp = 0;
    for(int i = 0; i < v1->length; i++) {
        dp += VECTOR_IDX_INTO(v1, i) * VECTOR_IDX_INTO(v2, i);
    }
    return dp;
}

double vector_norm(struct vector* v) {
    double norm_squared = vector_dot_product(v, v);
    return sqrt(norm_squared);
}

void vector_print(struct vector* v) {
    if(v->length == 0) {
        printf("[]\n");
    } else if (v->length == 1) {
        printf("[%.2f]\n", VECTOR_IDX_INTO(v, 0));
    } else {
        printf("[%.2f", VECTOR_IDX_INTO(v, 0));
        for(int i = 1; i < v->length - 1; i++) {
            printf(", ");
            printf("%.2f", VECTOR_IDX_INTO(v, i));
        }
        printf(", %.2f]\n", VECTOR_IDX_INTO(v, v->length - 1));
    }
}

bool vector_lengths_equal(struct vector* v1, struct vector* v2) {
    return (v1->length == v2->length);
}
