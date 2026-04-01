#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create two ucl_object_t objects
    ucl_object_t *obj1 = ucl_object_fromstring_common((const char *)data, size / 2, 0);
    ucl_object_t *obj2 = ucl_object_fromstring_common((const char *)(data + size / 2), size - size / 2, 0);

    // Ensure neither object is NULL
    if (obj1 == NULL || obj2 == NULL) {
        if (obj1 != NULL) {
            ucl_object_unref(obj1);
        }
        if (obj2 != NULL) {
            ucl_object_unref(obj2);
        }
        return 0;
    }

    // Call the function-under-test
    int result = ucl_object_compare(obj1, obj2);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}