#include "vector.h"

int main(int argc, char** argv) {
    struct vector* v1 = vector_zeros(5);
    vector_print(v1);
    vector_free(v1);
    return 0;
}
