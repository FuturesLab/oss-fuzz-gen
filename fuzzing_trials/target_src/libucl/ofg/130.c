#include "ucl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create two ucl_object_t objects
    ucl_object_t *obj1 = ucl_object_new();
    ucl_object_t *obj2 = ucl_object_new();

    // Add some data to the objects
    ucl_object_insert_key(obj1, ucl_object_fromstring("value1"), "key1", 0, false);
    ucl_object_insert_key(obj2, ucl_object_fromstring("value2"), "key2", 0, false);

    // Use the first byte of data to determine the boolean value for merging
    bool merge_recursive = data[0] % 2 == 0;

    // Call the function under test
    ucl_object_merge(obj1, obj2, merge_recursive);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}