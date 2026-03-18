#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_198(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract parameters
    if (size < sizeof(ucl_type_t) + sizeof(unsigned int)) {
        return 0;
    }

    // Extract parameters from the input data
    ucl_type_t type = *(ucl_type_t *)data;
    unsigned int flags = *(unsigned int *)(data + sizeof(ucl_type_t));

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_new_full(type, flags);

    // Clean up
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}