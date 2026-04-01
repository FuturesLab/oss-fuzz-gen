#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Create a new UCL object
    ucl_object_t *ucl_array = ucl_object_typed_new(UCL_ARRAY);

    // Add some elements to the UCL array
    for (size_t i = 0; i < size; ++i) {
        ucl_object_t *obj = ucl_object_fromint((int64_t)data[i]);
        ucl_array_append(ucl_array, obj);
    }

    // Call the function-under-test
    ucl_object_t *popped_obj = ucl_array_pop_last(ucl_array);

    // Free the popped object if it is not NULL
    if (popped_obj != NULL) {
        ucl_object_unref(popped_obj);
    }

    // Free the UCL array
    ucl_object_unref(ucl_array);

    return 0;
}