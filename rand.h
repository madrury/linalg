#pragma once
#include "vector.h"
#include "matrix.h"


void init_random();
struct vector* vector_random_uniform(int length, double low, double high);
struct matrix* matrix_random_uniform(int n_row, int n_col, double low, double high);

struct vector* vector_random_gaussian(int length, double mu, double sigma);
