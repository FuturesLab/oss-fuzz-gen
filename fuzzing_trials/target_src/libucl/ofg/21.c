#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Initialize two ucl_object_t pointers
    ucl_object_t *array = ucl_object_typed_new(UCL_ARRAY);
    ucl_object_t *element = ucl_object_fromstring("element");

    // Add the element to the array
    ucl_array_append(array, element);

    // Call the function-under-test
    ucl_object_t *result = ucl_array_delete(array, element);

    // Clean up
    ucl_object_unref(array);
    ucl_object_unref(result);

    return 0;
}