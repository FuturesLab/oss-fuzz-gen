#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Initialize two ucl_object_t objects
    ucl_object_t *obj1 = ucl_object_fromstring((const char *)data);
    ucl_object_t *obj2 = ucl_object_fromstring((const char *)(data + 1));

    // Ensure both objects are not NULL
    if (obj1 == NULL || obj2 == NULL) {
        if (obj1 != NULL) ucl_object_unref(obj1);
        if (obj2 != NULL) ucl_object_unref(obj2);
        return 0;
    }

    // Determine the boolean value for the merge function
    bool merge_recursively = data[0] % 2 == 0;

    // Call the function-under-test
    bool result = ucl_object_merge(obj1, obj2, merge_recursively);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}