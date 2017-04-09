#pragma once
#include "vector.h"
#include "matrix.h"

struct eigen {
    int n;
    struct vector* eigenvalues;
    struct matrix* eigenvectors;
}

struct eigen* eigen_new();
struct eigen* eigen_solve(matrix* M);
