#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_179(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Ensure there is enough data to create two objects
    }

    // Create two ucl_object_t instances
    ucl_object_t *obj1 = ucl_object_fromstring_common((const char *)data, size / 2, UCL_STRING_RAW);
    ucl_object_t *obj2 = ucl_object_fromstring_common((const char *)(data + size / 2), size - size / 2, UCL_STRING_RAW);

    // Call the function-under-test
    ucl_object_t *result = ucl_elt_append(obj1, obj2);

    // Clean up
    if (result != obj1 && result != obj2) {
        ucl_object_unref(result);
    }
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}