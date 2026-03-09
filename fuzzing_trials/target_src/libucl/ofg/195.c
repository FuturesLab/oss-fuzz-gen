#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract meaningful values
    if (size < sizeof(ucl_type_t) + sizeof(unsigned int)) {
        return 0;
    }

    // Extract ucl_type_t and unsigned int from the input data
    ucl_type_t obj_type = (ucl_type_t)data[0];
    unsigned int flags = *(unsigned int *)(data + 1);

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_new_full(obj_type, flags);

    // Clean up the created object
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}