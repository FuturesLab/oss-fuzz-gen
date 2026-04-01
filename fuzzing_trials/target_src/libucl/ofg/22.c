#include "/src/libucl/include/ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    // Create two ucl_object_t objects
    ucl_object_t *array_obj = ucl_object_typed_new(UCL_ARRAY);
    ucl_object_t *element_obj = ucl_object_fromstring_common((const char *)data, size, 0);

    // Ensure that the objects are not NULL
    if (array_obj != NULL && element_obj != NULL) {
        // Call the function-under-test
        ucl_array_append(array_obj, element_obj);
    }

    // Clean up
    if (array_obj != NULL) {
        ucl_object_unref(array_obj);
    }
    if (element_obj != NULL) {
        ucl_object_unref(element_obj);
    }

    return 0;
}