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

void test_vector_linspace() {
    struct vector* v3 = vector_linspace(11, 0, 1);
    vector_print(v3);
    vector_free(v3);
}

void test_vector_dot_product() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(5, D1);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(5, D2);
    double dp = vector_dot_product(v1, v2);
    printf("%.2f\n", dp);
}

int main(int argc, char** argv) {

    test_vector_zeros();
    test_vector_from_array();
    test_vector_linspace();
    test_vector_dot_product();

    return 0;
}
