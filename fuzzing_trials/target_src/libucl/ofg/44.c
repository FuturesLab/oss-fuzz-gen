#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create two ucl_object_t arrays
    ucl_object_t *obj1 = ucl_object_new();
    ucl_object_t *obj2 = ucl_object_new();

    // Initialize the objects as arrays
    ucl_object_t *array1 = ucl_object_typed_new(UCL_ARRAY);
    ucl_object_t *array2 = ucl_object_typed_new(UCL_ARRAY);

    // Add the input data to the arrays
    ucl_object_t *element1 = ucl_object_fromstring_common((const char *)data, size / 2, 0);
    ucl_object_t *element2 = ucl_object_fromstring_common((const char *)(data + size / 2), size - size / 2, 0);

    ucl_array_append(array1, element1);
    ucl_array_append(array2, element2);

    // Merge the arrays
    bool merge_result = ucl_array_merge(array1, array2, true);

    // Clean up
    ucl_object_unref(array1);
    ucl_object_unref(array2);

    return 0;
}