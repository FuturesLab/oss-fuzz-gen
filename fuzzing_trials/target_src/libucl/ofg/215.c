#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to extract a ucl_type_t value
    if (size < sizeof(ucl_type_t)) {
        return 0;
    }

    // Extract a ucl_type_t value from the input data
    ucl_type_t type = *(ucl_type_t *)data;

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_typed_new(type);

    // Clean up the created object
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}