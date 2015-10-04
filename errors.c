#include <stdlib.h>
#include <stdio.h>
#include "errors.h"

void raise_memory_allocation_error() {
    fprintf(stderr, "Memory allocation error.\n");
    exit(EXIT_FAILURE);
}

void raise_non_commensurate_vector_error() {
    fprintf(stderr, "Vectors are not of the same length.\n");
    exit(EXIT_FAILURE);
}
void raise_non_zero_reference_free_error() {
    fprintf(stderr, "Attempted to free memory with non-zero reference count.\n");
    exit(EXIT_FAILURE);
}
