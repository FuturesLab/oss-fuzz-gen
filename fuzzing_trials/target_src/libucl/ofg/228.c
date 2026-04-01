#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_228(const uint8_t *data, size_t size) {
    // Initialize two ucl_object_t pointers
    ucl_object_t *array_obj = ucl_object_new_full(UCL_ARRAY, NULL);
    ucl_object_t *element_obj = ucl_object_fromstring_common((const char *)data, size, 0);

    // Add the element to the array to ensure it's not NULL
    ucl_array_append(array_obj, element_obj);

    // Call the function under test
    unsigned int index = ucl_array_index_of(array_obj, element_obj);

    // Clean up
    ucl_object_unref(array_obj);

    return 0;
}