#pragma once
#include "vector.h"
#include "matrix.h"

struct eigen {
    int n;
    struct vector* eigenvalues;
    // struct matrix* eigenvectors;
}

struct eigen* eigen_new();
struct eigen_free(eigen* e);

struct eigen* eigen_solve(matrix* M, double tol, int max_iter);
struct vector* eigen_solve_eigenvalues(matrix* M, double tol, int max_iter);
// struct matrix* eigen_solve_eigenvectors(matrix* M, vector* eigenvectors);
