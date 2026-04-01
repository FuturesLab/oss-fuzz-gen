#include "/src/libucl/include/ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h> // Include this header for the bool type

int LLVMFuzzerTestOneInput_171(const uint8_t *data, size_t size) {
    // Create two ucl_object_t objects
    ucl_object_t *array = ucl_object_typed_new(UCL_ARRAY);
    ucl_object_t *element = ucl_object_fromstring_common((const char *)data, size, 0);

    // Ensure that the element is not NULL
    if (element == NULL) {
        ucl_object_unref(array);
        return 0;
    }

    // Call the function under test
    bool result = ucl_array_prepend(array, element);

    // Clean up
    ucl_object_unref(array);
    ucl_object_unref(element);

    return 0;
}