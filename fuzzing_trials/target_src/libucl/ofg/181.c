#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create two ucl_object_t objects
    if (size < 2) {
        return 0;
    }

    // Create two ucl_object_t objects
    ucl_object_t *obj1 = ucl_object_fromstring((const char *)data);
    ucl_object_t *obj2 = ucl_object_fromstring((const char *)(data + 1));

    // Call the function-under-test
    ucl_object_t *result = ucl_elt_append(obj1, obj2);

    // Clean up
    if (result != obj1) {
        ucl_object_unref(result);
    }
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}