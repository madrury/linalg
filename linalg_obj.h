#pragma once

struct linalg_obj {
    bool owns_memory;
    struct linalg_obj* memory_owner;
    int ref_count;
    double* data;
};

#ifndef OWNS_MEMORY
#define OWNS_MEMORY(object) (((struct linalg_obj*) object)->owns_memory)
#endif

#ifndef MEMORY_OWNER
#define MEMORY_OWNER(object) (((struct linalg_obj*) object)->memory_owner)
#endif

#ifndef REF_COUNT
#define REF_COUNT(object) (((struct linalg_obj*) object)->ref_count)
#endif

#ifndef DATA
#define DATA(object) (((struct linalg_obj*) object)->data)
#endif
