#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(int argc, char** argv) {

    /* Test vector_zeros */
    struct vector* v1 = vector_zeros(5);
    vector_print(v1);
    vector_free(v1);

    /* Test vector_from_array */
    double D[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    struct vector* v2 = vector_from_array(5, D);
    vector_print(v2);
    vector_free(v2);

    /* Test linspace */
    struct vector* v3 = vector_linspace(11, 0, 1);
    vector_print(v3);
    vector_free(v3);

    return 0;
}
