#pragma once
#include "errors.c"

void check_memory(void* mem) {
    if(mem == NULL) {
        raise_memory_allocation_error();
    }
}
