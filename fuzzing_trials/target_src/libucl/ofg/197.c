#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract both parameters
    if (size < sizeof(ucl_type_t) + sizeof(unsigned int)) {
        return 0;
    }

    // Extract ucl_type_t from the data
    ucl_type_t type = *(ucl_type_t *)data;

    // Extract unsigned int from the data
    unsigned int priority = *(unsigned int *)(data + sizeof(ucl_type_t));

    // Call the function under test
    ucl_object_t *obj = ucl_object_new_full(type, priority);

    // Clean up if necessary
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}