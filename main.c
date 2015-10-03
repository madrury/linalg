#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


void test_vector_zeros() {
    struct vector* v1 = vector_zeros(5);
    vector_print(v1);
    vector_free(v1);
}

void test_vector_from_array() {
    double D[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    struct vector* v2 = vector_from_array(5, D);
    vector_print(v2);
    vector_free(v2);
}

void test_vector_view() {
    struct vector* v = vector_zeros(5);
    struct vector* view = vector_new_view((struct linalg_obj*) v, DATA(v), 3);
    vector_print(view);
    vector_free(view); vector_free(v);
}

void test_vector_linspace() {
    struct vector* v3 = vector_linspace(11, 0, 1);
    vector_print(v3);
    vector_free(v3);
}

//void test_vector_dot_product() {
//    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
//    struct vector* v1 = vector_from_array(5, D1);
//    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
//    struct vector* v2 = vector_from_array(5, D2);
//    double dp = vector_dot_product(v1, v2);
//    printf("%.2f\n", dp);
//    vector_free(v1); vector_free(v2);
//}
//
//void test_vector_add() {
//    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
//    struct vector* v1 = vector_from_array(5, D1);
//    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
//    struct vector* v2 = vector_from_array(5, D2);
//    struct vector* v = vector_add(v1, v2);
//    vector_print(v);
//    vector_free(v1); vector_free(v2); vector_free(v);
//}
//
//void test_vector_add_into() {
//    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
//    struct vector* v1 = vector_from_array(5, D1);
//    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
//    struct vector* v2 = vector_from_array(5, D2);
//    vector_add_into(v1, v2);
//    vector_print(v1);
//    vector_free(v1); vector_free(v2);
//}

void test_vector_subtract() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(5, D1);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(5, D2);
    struct vector* v = vector_subtract(v1, v2);
    vector_print(v);
    vector_free(v1); vector_free(v2); vector_free(v);
}

void test_vector_subtract_into() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(5, D1);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(5, D2);
    vector_subtract_into(v1, v2);
    vector_print(v1);
    vector_free(v1); vector_free(v2);
}

void test_vector_slice() {
    double D[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    struct vector* v = vector_from_array(5, D);
    struct vector* w = vector_slice(v, 2, 4);
    vector_print(v);
    vector_print(w);
    //vector_free(w); 
    vector_free(v);
}

int main(int argc, char** argv) {

//    test_vector_zeros();
//    test_vector_from_array();
//    test_vector_linspace();
//    test_vector_dot_product();
//    test_vector_add();
//    test_vector_add_into();
    test_vector_subtract();
    test_vector_subtract_into();
//    test_vector_view();
//    test_vector_slice();

    return 0;
}
