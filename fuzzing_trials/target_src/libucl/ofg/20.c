#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    // Create a new UCL object to represent an array
    ucl_object_t *array = ucl_object_typed_new(UCL_ARRAY);

    // Create a new UCL object to be deleted from the array
    ucl_object_t *obj_to_delete = ucl_object_fromstring((const char *)data);

    // Add the object to the array
    ucl_array_append(array, obj_to_delete);

    // Call the function under test
    ucl_object_t *result = ucl_array_delete(array, obj_to_delete);

    // Clean up
    ucl_object_unref(result);
    ucl_object_unref(array);

    return 0;
}