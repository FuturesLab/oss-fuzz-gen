#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    if (size < sizeof(ucl_type_t) + sizeof(unsigned int)) {
        return 0;
    }

    // Extract ucl_type_t from data
    ucl_type_t type = *(ucl_type_t *)data;

    // Extract unsigned int from data
    unsigned int flags = *(unsigned int *)(data + sizeof(ucl_type_t));

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_new_full(type, flags);

    // It's important to free the object if it was successfully created
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}