#include <assert.h>
#include "vector.h"
#include "matrix.h"
#include "eigen.h"

struct eigen* eigen_new() {
    struct eigen* e = malloc(sizeof(struct eigen));
    return e;
}

struct eigen* eigen_solve() {
    struct eigen* e = eigen_new();
    return e;
}
