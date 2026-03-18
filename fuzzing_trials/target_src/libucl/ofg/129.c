#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create meaningful objects
    if (size < 2) {
        return 0;
    }

    // Create two ucl_object_t objects
    ucl_object_t *obj1 = ucl_object_new();
    ucl_object_t *obj2 = ucl_object_new();

    // Add data to the objects
    ucl_object_insert_key(obj1, ucl_object_fromstring("value1"), "key1", 4, false);
    ucl_object_insert_key(obj2, ucl_object_fromstring("value2"), "key2", 4, false);

    // Use the first byte of data to determine the boolean value
    bool merge_deep = data[0] % 2 == 0;

    // Call the function under test
    ucl_object_merge(obj1, obj2, merge_deep);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}