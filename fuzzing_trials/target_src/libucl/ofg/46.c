#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>  // Include the stdbool.h header for the bool type

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Initialize two ucl_object_t objects
    ucl_object_t *obj1 = ucl_object_new();
    ucl_object_t *obj2 = ucl_object_new();

    // Add some data to the objects if size is sufficient
    if (size > 0) {
        ucl_object_insert_key(obj1, ucl_object_fromstring((const char *)data), "key1", 4, false);
        ucl_object_insert_key(obj2, ucl_object_fromstring((const char *)data), "key2", 4, false);
    }

    // Set the boolean flag for merging
    bool merge_flag = true;

    // Call the function-under-test
    bool result = ucl_array_merge(obj1, obj2, merge_flag);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}