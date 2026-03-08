#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>  // Include for the bool type

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Initialize two ucl_object_t pointers
    ucl_object_t *obj1 = ucl_object_new();
    ucl_object_t *obj2 = ucl_object_new();

    // Ensure the objects are arrays
    ucl_object_t *array1 = ucl_object_typed_new(UCL_ARRAY);
    ucl_object_t *array2 = ucl_object_typed_new(UCL_ARRAY);

    // Add some data to the arrays if size is sufficient
    if (size > 0) {
        ucl_object_t *item1 = ucl_object_fromstring_common((const char *)data, size, 0);
        ucl_array_append(array1, item1);

        ucl_object_t *item2 = ucl_object_fromstring_common((const char *)data, size, 0);
        ucl_array_append(array2, item2);
    }

    // Assign the arrays to the objects
    obj1 = array1;
    obj2 = array2;

    // Call the function under test with both true and false for the boolean parameter
    bool result1 = ucl_array_merge(obj1, obj2, true);
    bool result2 = ucl_array_merge(obj1, obj2, false);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}