#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "tests.h"
#include "vector.h"
#include "matrix.h"
#include "linsolve.h"
#include "rand.h"


/* Unit tests for vector module. */

bool test_vector_zeros() {
    struct vector* zeros = vector_zeros(5);
    double D[] = {0.0, 0.0, 0.0, 0.0, 0.0};
    struct vector* exp = vector_from_array(D, 5);
    bool test = vector_equal(zeros, exp, .01);
    vector_free_many(2, zeros, exp);
    return test;
}

bool test_vector_view() {
    struct vector* v = vector_zeros(5);
    struct vector* view = vector_new_view((struct linalg_obj*) v, DATA(v), 3);
    double D[] = {0.0, 0.0, 0.0};
    struct vector* exp = vector_from_array(D, 3);
    bool test = vector_equal(view, exp, .01);
    vector_free_many(3, view, v, exp);
    return test;
}

bool test_vector_slice() {
    double D1[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    struct vector* v = vector_from_array(D1, 5);
    struct vector* sl = vector_slice(v, 1, 4);
    double D2[] = {2.0, 3.0, 4.0};
    struct vector* exp = vector_from_array(D2, 3);
    bool test = vector_equal(sl, exp, .01);
    vector_free_many(3, sl, exp, v);
    return test;
}

bool test_vector_linspace() {
    struct vector* linsp = vector_linspace(11, 0, 1);
    double D[11] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    struct vector* exp = vector_from_array(D, 11);
    bool test = vector_equal(linsp, exp, .01);
    vector_free_many(2, linsp, exp);
    return test;
}

bool test_vector_dot_product() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(D1, 5);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(D2, 5);
    double dp = vector_dot_product(v1, v2);
    vector_free_many(2, v1, v2);
    return dp == 1.0;
}

bool test_vector_add() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(D1, 5);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(D2, 5);
    struct vector* sum = vector_add(v1, v2);
    double D3[] = {1.0, 1.0, 2.0, 1.0, 1.0};
    struct vector* res = vector_from_array(D3, 5);
    bool test = vector_equal(sum, res, .01);
    vector_free_many(4, v1, v2, sum, res);
    return test;
}

bool test_vector_add_into() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(D1, 5);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(D2, 5);
    vector_add_into(v1, v2);
    double D3[] = {1.0, 1.0, 2.0, 1.0, 1.0};
    struct vector* res = vector_from_array(D3, 5);
    bool test = vector_equal(v1, res, .01);
    vector_free_many(3, v1, v2, res);
    return test;
}

bool test_vector_subtract() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(D1, 5);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(D2, 5);
    struct vector* sum = vector_subtract(v1, v2);
    double D3[] = {1.0, 1.0, 0.0, -1.0, -1.0};
    struct vector* res = vector_from_array(D3, 5);
    bool test = vector_equal(sum, res, .01);
    vector_free_many(4, v1, v2, sum, res);
    return test;
}

bool test_vector_subtract_into() {
    double D1[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v1 = vector_from_array(D1, 5);
    double D2[] = {0.0, 0.0, 1.0, 1.0, 1.0};
    struct vector* v2 = vector_from_array(D2, 5);
    vector_subtract_into(v1, v2);
    double D3[] = {1.0, 1.0, 0.0, -1.0, -1.0};
    struct vector* res = vector_from_array(D3, 5);
    bool test = vector_equal(v1, res, .01);
    vector_free_many(3, v1, v2, res);
    return test;
}


bool test_vector_normalize_into() {
    double D[] = {1.0, 1.0, 1.0, 0.0, 0.0};
    struct vector* v = vector_from_array(D, 5);
    double R[] = {1/sqrt(3), 1/sqrt(3), 1/sqrt(3), 0, 0};
    struct vector* res = vector_from_array(R, 5);
    vector_normalize_into(v);
    bool test = vector_equal(v, res, .01);
    vector_free_many(2, v, res);
    return test;
}


#define N_VECTOR_TESTS 10

struct test vector_tests[] = {
    {test_vector_zeros, "test_vector_zeros"},
    {test_vector_view, "test_vector_view"},
    {test_vector_slice, "test_vector_slice"},
    {test_vector_linspace, "test_vector_linspace"},
    {test_vector_dot_product, "test_vector_dot_product"},
    {test_vector_add, "test_vector_add"},
    {test_vector_add_into, "test_vector_add_into"},
    {test_vector_subtract, "test_vector_subtract"},
    {test_vector_subtract_into, "test_vector_subtract_into"},
    {test_vector_normalize_into, "test_vector_normalize_into"}
};


/* Unit tests for matrix module. */

bool test_matrix_zeros() {
    struct matrix* M = matrix_zeros(3, 3);
    double D[] = {0.0, 0.0, 0.0,
                  0.0, 0.0, 0.0,
                  0.0, 0.0, 0.0};
    struct matrix* res = matrix_from_array(D, 3, 3);
    bool test = matrix_equal(M, res, .01);
    matrix_free_many(2, M, res);
    return test;
}

bool test_matrix_identity() {
    struct matrix* M = matrix_identity(3);
    double I[] = {1.0, 0.0, 0.0,
                  0.0, 1.0, 0.0,
                  0.0, 0.0, 1.0};
    struct matrix* res = matrix_from_array(I, 3, 3);
    bool test = matrix_equal(M, res, .01);
    matrix_free_many(2, M, res);
    return test;
}

bool test_matrix_transpose() {
    double D[] = {1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0,
                  1.0, 2.0, 3.0};
    struct matrix* M = matrix_from_array(D, 4, 3);
    struct matrix* Mt = matrix_transpose(M);
    double T[] = {1.0, 4.0, 7.0, 1.0,
                  2.0, 5.0, 8.0, 2.0,
                  3.0, 6.0, 9.0, 3.0};
    struct matrix* res = matrix_from_array(T, 3, 4);
    bool test = matrix_equal(Mt, res, .01);
    matrix_free_many(3, M, Mt, res);
    return test;
}

bool test_matrix_multiply_identity() {
    double D[] = {1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0};
    struct matrix* Mleft = matrix_from_array(D, 3, 3);
    struct matrix* Mright = matrix_identity(3);
    struct matrix* Mprod = matrix_multiply(Mleft, Mright);
    bool test = matrix_equal(Mprod, Mleft, .01);
    matrix_free_many(3, Mleft, Mright, Mprod);
    return test;
}

bool test_matrix_multiply() {
    double D[] = {1.0, 1.0, 0.0,
                  0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0};
    struct matrix* Mleft = matrix_from_array(D, 3, 3);
    struct matrix* Mprod = matrix_multiply(Mleft, Mleft);
    double R[] = {1.0, 2.0, 0.0,
                  0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0};
    struct matrix* res = matrix_from_array(R, 3, 3);
    bool test = matrix_equal(Mprod, res, .01);
    matrix_free_many(3, Mleft, Mprod, res);
    return test;
}

bool test_matrix_multiply_MtN() {
    double D[] = {1.0, 1.0, 0.0,
                  0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0};
    struct matrix* Mleft = matrix_from_array(D, 3, 3);
    struct matrix* Mprod = matrix_multiply_MtN(Mleft, Mleft);
    double R[] = {1.0, 1.0, 0.0,
                  1.0, 2.0, 0.0,
                  0.0, 0.0, 0.0};
    struct matrix* res = matrix_from_array(R, 3, 3);
    bool test = matrix_equal(Mprod, res, .01);
    matrix_free_many(3, Mleft, Mprod, res);
    return test;
}

bool test_matrix_vector_multiply_identity() {
    struct matrix* I = matrix_identity(3);
    double D[] = {1.0, 2.0, 3.0};
    struct vector* v = vector_from_array(D, 3);
    struct vector* w = matrix_vector_multiply(I, v);
    bool test = vector_equal(v, w, .01);
    vector_free_many(2, v, w); matrix_free(I);
    return test;
}

bool test_matrix_vector_multiply() {
    double D[] = {1.0, 1.0, 0.0,
                  0.0, 1.0, 0.0,
                  0.0, 0.0, 1.0};
    struct matrix* M = matrix_from_array(D, 3, 3);
    double V[] = {1.0, 2.0, 3.0};
    struct vector* v = vector_from_array(V, 3);
    struct vector* w = matrix_vector_multiply(M, v);
    double R[] = {3.0, 2.0, 3.0};
    struct vector* res = vector_from_array(R, 3);
    bool test = vector_equal(w, res, .01);
    vector_free_many(3, v, w, res); matrix_free(M);
    return test;
}

bool test_matrix_vector_multiply_Mtv() {
    double D[] = {1.0, 1.0, 0.0,
                  0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0};
    struct matrix* M = matrix_from_array(D, 3, 3);
    double V[] = {1.0, 2.0, 3.0};
    struct vector* v = vector_from_array(V, 3);
    struct vector* w = matrix_vector_multiply_Mtv(M, v);
    double R[] = {1.0, 3.0, 0.0};
    struct vector* res = vector_from_array(R, 3);
    bool test = vector_equal(w, res, .01);
    vector_free_many(3, v, w, res); matrix_free(M);
    return test;
}

bool test_matrix_row_copy() {
    double D[] = {1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct vector* r = matrix_row_copy(M, 1);
    double R[] = {4.0, 5.0, 6.0};
    struct vector* res = vector_from_array(R, 3);
    bool test = vector_equal(r, res, .01);
    vector_free_many(2, r, res); matrix_free(M);
    return test;
}

bool test_matrix_column_copy() {
    double D[] = {1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0,
                  7.0, 8.0, 9.0};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct vector* c = matrix_column_copy(M, 1);
    double C[] = {2.0, 5.0, 8.0};
    struct vector* res = vector_from_array(C, 3);
    bool test = vector_equal(c, res, .01);
    matrix_free(M); vector_free_many(2, res, c);
    return test;
}

bool test_matrix_copy_vector_into_row() {
    struct matrix* M = matrix_zeros(3, 3);
    struct vector* v = vector_linspace(3, 0, 1);
    matrix_copy_vector_into_row(M, v, 1);
    double D[] = {0.0, 0.0, 0.0,
                  0.0, 0.5, 1.0,
                  0.0, 0.0, 0.0};
    struct matrix* res = matrix_from_array(D, 3, 3);
    bool test = matrix_equal(M, res, .01);
    matrix_free_many(2, M, res); vector_free(v);
    return test;
}

bool test_matrix_copy_vector_into_column() {
    struct matrix* M = matrix_zeros(3, 3);
    struct vector* v = vector_linspace(3, 0, 1);
    matrix_copy_vector_into_column(M, v, 1);
    double D[] = {0.0, 0.0, 0.0,
                  0.0, 0.5, 0.0,
                  0.0, 1.0, 0.0};
    struct matrix* res = matrix_from_array(D, 3, 3);
    bool test = matrix_equal(M, res, .01);
    matrix_free_many(2, M, res); vector_free(v);
    return test;
}

bool test_qr_decomp_identity() {
    struct matrix* I = matrix_identity(10);
    struct qr_decomp* qr = matrix_qr_decomposition(I);
    bool q_correct = matrix_equal(I, qr->q, .01);
    bool r_correct = matrix_equal(I, qr->r, .01);
    qr_decomp_free(qr); matrix_free(I);
    return q_correct && r_correct;
}

bool test_qr_decomp_recover_matrix() {
    double D[] = {1, 1, 0,
                  1, 0, 1,
                  0, 1, 1};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    struct matrix* P = matrix_multiply(qr->q, qr->r);
    bool test = matrix_equal(M, P, .01);
    matrix_free_many(2, M, P); qr_decomp_free(qr);
    return test;
}

bool test_qr_decomp_orthogonal() {
    double D[] = {1, 1, 0,
                  1, 0, 1,
                  0, 1, 1};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    struct matrix* qt = matrix_transpose(qr->q);
    struct matrix* P = matrix_multiply(qr->q, qt);
    struct matrix* I = matrix_identity(3);
    bool test = matrix_equal(P, I, .01);
    matrix_free_many(4, M, qt, P, I); qr_decomp_free(qr);
    return test;
}

bool test_qr_decomp() {
    double D[] = {1, 1, 0,
                  1, 0, 1,
                  0, 1, 1};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    double Q[] = {1/sqrt(2), 1/sqrt(6), -1/sqrt(3),
                  1/sqrt(2), -1/sqrt(6), 1/sqrt(3),
                  0        , 2/sqrt(6), 1/sqrt(3)};
    struct matrix* qres = matrix_from_array(Q, 3, 3);
    double R[] = {2/sqrt(2), 1/sqrt(2), 1/sqrt(2),
                  0        , 3/sqrt(6), 1/sqrt(6),
                  0        , 0        , 2/sqrt(3)};
    struct matrix* rres = matrix_from_array(R, 3, 3);
    bool qtest = matrix_equal(qr->q, qres, .01);
    bool rtest = matrix_equal(qr->r, rres, .01);
    matrix_free_many(3, M, qres, rres); qr_decomp_free(qr);
    return qtest && rtest;
}

bool test_qr_decomp_2() {
    double D[] = {1, 2, 0,
                  0, 1, 1,
                  1, 0, 1};
    struct matrix* M = matrix_from_array(D, 3, 3);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    double Q[] = {1/sqrt(2), 1/sqrt(3), -1/sqrt(6),
                  0        , 1/sqrt(3),  2/sqrt(6),
                  1/sqrt(2), -1/sqrt(3), 1/sqrt(6)};
    struct matrix* qres = matrix_from_array(Q, 3, 3);
    double R[] = {sqrt(2), sqrt(2), 1/sqrt(2),
                  0      , sqrt(3),         0,
                  0      , 0      , sqrt(6)/2};
    struct matrix* rres = matrix_from_array(R, 3, 3);
    bool qtest = matrix_equal(qr->q, qres, .01);
    bool rtest = matrix_equal(qr->r, rres, .01);
    matrix_free_many(3, M, qres, rres); qr_decomp_free(qr);
    return qtest && rtest;
}

bool test_qr_decomp_non_square() {
    double D[] = {1, -1, 4,
                  1, 4, -2,
                  1, 4,  2,
                  1, -1, 0};
    struct matrix* M = matrix_from_array(D, 4, 3);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    double Q[] = {0.5, -0.5,  0.5,
                  0.5,  0.5, -0.5,
                  0.5,  0.5,  0.5,
                  0.5, -0.5, -0.5};
    struct matrix* qres = matrix_from_array(Q, 4, 3);
    double R[] = {2, 3,  2,
                  0, 5, -2,
                  0, 0,  4};
    struct matrix* rres = matrix_from_array(R, 3, 3);
    bool qtest = matrix_equal(qr->q, qres, .01);
    bool rtest = matrix_equal(qr->r, rres, .01);
    matrix_free_many(3, M, qres, rres); qr_decomp_free(qr);
    return qtest && rtest;
}

bool test_qr_decomp_random() {
    struct matrix* M = matrix_random_uniform(10000, 100, 0, 1);
    struct matrix* I = matrix_identity(100);
    struct qr_decomp* qr = matrix_qr_decomposition(M);
    struct matrix* recovered_M = matrix_multiply(qr->q, qr->r);
    struct matrix* qt = matrix_transpose(qr->q);
    struct matrix* qt_q = matrix_multiply(qt, qr->q);
    bool test = matrix_equal(M, recovered_M, .01) && matrix_equal(qt_q, I, .01);
    matrix_free_many(5, M, I, recovered_M, qt, qt_q); qr_decomp_free(qr);
    return test;
}


#define N_MATRIX_TESTS 20

struct test matrix_tests[] = {
    {test_matrix_zeros, "test_matrix_zeros"},
    {test_matrix_identity, "test_matrix_identity"},
    {test_matrix_transpose, "test_matrix_transpose"},
    {test_matrix_multiply_identity, "test_matrix_multiply_identity"},
    {test_matrix_multiply, "test_matrix_multiply"},
    {test_matrix_multiply_MtN, "test_matrix_multiply_MtN"},
    {test_matrix_vector_multiply_identity, "test_matrix_vector_multiply_identity"},
    {test_matrix_vector_multiply, "test_matrix_vector_multiply"},
    {test_matrix_vector_multiply_Mtv, "test_matrix_vector_multiply_Mtv"},
    {test_matrix_row_copy, "test_matrix_row_copy"},
    {test_matrix_column_copy, "test_matrix_column_copy"},
    {test_matrix_copy_vector_into_row, "test_matrix_copy_vector_into_row"},
    {test_matrix_copy_vector_into_column, "test_matrix_copy_vector_into_column"},
    {test_qr_decomp_identity, "test_qr_decomp_identity"},
    {test_qr_decomp_recover_matrix, "test_qr_decomp_recover_matrix"},
    {test_qr_decomp_orthogonal, "test_qr_decomp_orthogonal"},
    {test_qr_decomp, "test_qr_decomp"},
    {test_qr_decomp_2, "test_qr_decomp_2"},
    {test_qr_decomp_non_square, "test_qr_decomp_non_square"},
    {test_qr_decomp_random, "test_qr_decomp_random"},
};


/* Unit tests for the linsolve module */

bool test_solve_qr_identity() {
    struct matrix* I = matrix_identity(3);
    double V[] = {1.0, 2.0, 3.0};
    struct vector* v = vector_from_array(V, 3);
    struct vector* s = linsolve_qr(I, v);
    bool test = vector_equal(s, v, .01);
    vector_free_many(2, v, s); matrix_free(I);
    return test;
}

bool test_solve_qr_upper_triangular() {
    double M[] = {1.0, 1.0, 1.0,
                  0.0, 1.0, 1.0,
                  0.0, 0.0, 1.0};
    struct matrix* m = matrix_from_array(M, 3, 3);
    double V[] = {3.0, 2.0, 1.0};
    struct vector* v = vector_from_array(V, 3);
    struct vector* s = linsolve_qr(m, v);
    double R[] = {1.0, 1.0, 1.0};
    struct vector* res = vector_from_array(R, 3);
    bool test = vector_equal(s, res, .01);
    vector_free_many(3, v, s, res); matrix_free(m);
    return test;
}

bool test_solve_qr_general() {
    double M[] = {1.0,  2.0,  3.0,
                  2.0, -4.0,  6.0,
                  3.0, -9.0,  -3.0};
    struct matrix* m = matrix_from_array(M, 3, 3);
    double V[] = {5.0, 18.0, 6.0};
    struct vector* v = vector_from_array(V, 3);
    struct vector* s = linsolve_qr(m, v);
    double R[] = {1.0, -1.0, 2.0};
    struct vector* res = vector_from_array(R, 3);
    bool test = vector_equal(s, res, .01);
    vector_free_many(3, s, v, res); matrix_free(m);
    return test;
}

bool test_solve_qr_random() {
    struct matrix* M = matrix_random_uniform(100, 100, 0, 1);
    struct vector* v = vector_random_uniform(100, 0, 1);
    struct vector* y = matrix_vector_multiply(M, v);
    struct vector* s = linsolve_qr(M, y);
    bool test = vector_equal(v, s, .01);
    vector_free_many(3, v, y, s); matrix_free(M);
    return test;
}


#define N_LINSOLVE_TESTS 4

struct test linsolve_tests[] = {
    {test_solve_qr_identity, "test_solve_qr_identity"},
    {test_solve_qr_upper_triangular, "test_solve_qr_upper_triangular"},
    {test_solve_qr_general, "test_solve_qr_general"},
    {test_solve_qr_random, "test_solve_qr_random"},
};

// Testing setup.

void _display_result(bool test_success, char* test_name) {
    if(test_success) {
        printf("*");
    } else {
        printf("\nTest %s failed.\n", test_name);
    }
}

void _display_final_result(bool all_success, int n_pass_tests, int n_fail_tests) {
    printf("\n");
    if(all_success) {
        printf("All tests pass (%d passed, %d failed).\n", 
               n_pass_tests, n_fail_tests);
    } else {
        printf("Test failure (%d passed, %d failed).\n",
               n_pass_tests, n_fail_tests);
    }
}

void run_tests(struct test tests[], int n_tests) {
    bool test_success;
    bool all_success = true;
    int n_pass_tests = 0; int n_fail_tests = 0;
    for(int i = 0; i < n_tests; i++) {
        test_success = (tests[i].test_f)();
        n_pass_tests += test_success; n_fail_tests += 1 - test_success;
        _display_result(test_success, tests[i].name);
        all_success = all_success && test_success;
    }
    _display_final_result(all_success, n_pass_tests, n_fail_tests);
}

void run_all() {
    run_tests(vector_tests, N_VECTOR_TESTS);
    run_tests(matrix_tests, N_MATRIX_TESTS);
    run_tests(linsolve_tests, N_LINSOLVE_TESTS);
}
