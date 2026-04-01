#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Initialize two ucl_object_t objects
    ucl_object_t *obj1 = ucl_object_new_full(UCL_ARRAY, NULL);
    ucl_object_t *obj2 = ucl_object_new_full(UCL_ARRAY, NULL);

    // Add some dummy data to the objects to ensure they are not NULL
    ucl_object_t *dummy_obj1 = ucl_object_fromstring("dummy1");
    ucl_object_t *dummy_obj2 = ucl_object_fromstring("dummy2");
    ucl_array_append(obj1, dummy_obj1);
    ucl_array_append(obj2, dummy_obj2);

    // Use the first byte of data to determine the boolean parameter
    bool merge_recursively = size > 0 ? (data[0] % 2 == 0) : false;

    // Call the function under test
    bool result = ucl_array_merge(obj1, obj2, merge_recursively);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}