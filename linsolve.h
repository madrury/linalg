#pragma once
#include "vector.h"
#include "matrix.h"

struct vector* linsolve_qr(struct matrix* M, struct vector* v);
struct vector* linsolve_from_qr(struct qr_decomp* qr, struct vector* v);
struct vector* linsolve_upper_triangular(struct matrix* M, struct vector* v);
