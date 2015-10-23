#pragma once
#include "vector.h"
#include "matrix.h"

struct vector* solve_upper_triangular(struct matrix* M, struct vector* v);
struct vector* linsolve_qr(struct matrix* M, struct vector* v);
