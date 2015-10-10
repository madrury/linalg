#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "matrix.h"


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

void test_vector_dot_product() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(5, D1);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(5, D2);
    double dp = vector_dot_product(v1, v2);
    printf("%.2f\n", dp);
    vector_free(v1); vector_free(v2);
}

void test_vector_add() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(5, D1);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(5, D2);
    struct vector* v = vector_add(v1, v2);
    vector_print(v);
    vector_free(v1); vector_free(v2); vector_free(v);
}

void test_vector_add_into() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(5, D1);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(5, D2);
    vector_add_into(v1, v2);
    vector_print(v1);
    vector_free(v1); vector_free(v2);
}

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

void test_vector_normalize_into() {
    double D[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v = vector_from_array(5, D);
    vector_normalize_into(v);
    vector_print(v);
    vector_free(v);
}

void test_matrix_zeros() {
    struct matrix* M = matrix_zeros(3, 3);
    matrix_print(M);
    matrix_free(M);
}

void test_matrix_identity() {
    struct matrix* M = matrix_identity(5);
    matrix_print(M);
    matrix_free(M);
}

void test_matrix_from_array() {
    double D[] = {1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0};
    struct matrix* M = matrix_from_array(D, 3, 3);
    matrix_print(M);
    matrix_free(M);
}

void test_matrix_transpose() {
    double D[] = {1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct matrix* Mt = matrix_transpose(M);
    matrix_print(Mt);
    matrix_free(M); matrix_free(Mt);
}

void test_matrix_multiply() {
    double D[] = {1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0};
    struct matrix* Mleft = matrix_from_array(D, 3, 3);
    struct matrix* Mright = matrix_identity(3);
    struct matrix* Mprod = matrix_multiply(Mleft, Mright);
    matrix_print(Mprod);
    matrix_free(Mleft); matrix_free(Mright); matrix_free(Mprod);
}

void test_matrix_multiply_2() {
    double D[] = {1.0, 1.0, 0.0,
                  0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0};
    struct matrix* Mleft = matrix_from_array(D, 3, 3);
    struct matrix* Mprod = matrix_multiply(Mleft, Mleft);
    matrix_print(Mprod);
    matrix_free(Mleft); matrix_free(Mprod);
}

void test_matrix_vector_multiply_identity() {
    struct matrix* I = matrix_identity(3);
    double D[] = {1.0, 2.0, 3.0};
    struct vector* v = vector_from_array(3, D);
    struct vector* w = matrix_vector_multiply(I, v);
    vector_print(w);
    matrix_free(I); vector_free(v); vector_free(w);
}

void test_matrix_vector_multiply() {
    double D[] = {1.0, 1.0, 0.0,
                  0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0};
    struct matrix* M = matrix_from_array(D, 3, 3);
    double V[] = {1.0, 2.0, 3.0};
    struct vector* v = vector_from_array(3, V);
    struct vector* w = matrix_vector_multiply(M, v);
    vector_print(w);
    matrix_free(M); vector_free(v); vector_free(w);
}


void test_matrix_row_copy() {
    double D[] = {1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct vector* r = matrix_row_copy(M, 1);
    vector_print(r);
    vector_free(r); matrix_free(M);
}

void test_matrix_column_copy() {
    double D[] = {1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct vector* c = matrix_column_copy(M, 1);
    vector_print(c);
    vector_free(c); matrix_free(M);
}

void test_matrix_copy_vector_into_row() {
    struct matrix* M = matrix_zeros(3, 3);
    struct vector* v = vector_linspace(3, 0, 1);
    matrix_copy_vector_into_row(M, v, 1);
    matrix_print(M);
    matrix_free(M); vector_free(v);
}

void test_matrix_copy_vector_into_column() {
    struct matrix* M = matrix_zeros(3, 3);
    struct vector* v = vector_linspace(3, 0, 1);
    matrix_copy_vector_into_column(M, v, 1);
    matrix_print(M);
    matrix_free(M); vector_free(v);
}

void test_qr_decomp_identity() {
    struct matrix* I = matrix_identity(3);
    struct qr_decomp* qr = matrix_qr_decomposition(I);
    matrix_print(qr->q);
    matrix_print(qr->r);
    qr_decomp_free(qr);
}

void test_qr_decomp() {
    double D[] = {1, 1, 0,
                  1, 0, 1,
                  0, 1, 1};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    printf("q: "); matrix_print(qr->q);
    printf("r: "); matrix_print(qr->r);
    struct matrix* P = matrix_multiply(qr->q, qr->r);
    printf("q*r: "); matrix_print(P);
    matrix_free(P); qr_decomp_free(qr);
}

void test_qr_decomp_2() {
    double D[] = {1, 2, 0,
                  0, 1, 1,
                  1, 0, 1};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    printf("q: "); matrix_print(qr->q);
    printf("r: "); matrix_print(qr->r);
    struct matrix* P = matrix_multiply(qr->q, qr->r);
    printf("q*r: "); matrix_print(P);
    matrix_free(P); qr_decomp_free(qr);
}

void test_qr_decomp_non_square() {
    double D[] = {1, -1, 4,
                  1, 4, -2,
                  1, 4,  2,
                  1, -1, 0};
    struct matrix* M = matrix_from_array(D, 4, 3);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    printf("q: "); matrix_print(qr->q);
    printf("r: "); matrix_print(qr->r);
    struct matrix* P = matrix_multiply(qr->q, qr->r);
    printf("q*r: "); matrix_print(P);
    matrix_free(P); qr_decomp_free(qr);
}

int main(int argc, char** argv) {

//    test_vector_zeros();
//    test_vector_from_array();
//    test_vector_linspace();
//    test_vector_dot_product();
//    test_vector_add();
//    test_vector_add_into();
//    test_vector_subtract();
//    test_vector_subtract_into();
//    test_vector_normalize_into();
//    test_vector_view();
//    test_vector_slice();
    test_matrix_zeros();
    test_matrix_identity();
    test_matrix_from_array();
    test_matrix_transpose();
    test_matrix_multiply();
    test_matrix_multiply_2();
    test_matrix_vector_multiply_identity();
    test_matrix_vector_multiply();
    test_matrix_row_copy();
    test_matrix_column_copy();
    test_matrix_copy_vector_into_row();
    test_matrix_copy_vector_into_column();
//    test_qr_decomp_identity();
//    test_qr_decomp();
//    test_qr_decomp_2();
//    test_qr_decomp_non_square();

    return 0;
}
