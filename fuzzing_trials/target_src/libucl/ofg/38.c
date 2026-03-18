#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a key for testing
    if (size < 2) {
        return 0;
    }

    // Create a ucl_object_t for testing
    ucl_object_t *obj = ucl_object_new();

    // Create a key from the input data
    char key[256];
    size_t key_length = size < 255 ? size : 255;
    memcpy(key, data, key_length);
    key[key_length] = '\0'; // Ensure null-termination

    // Add a key-value pair to the object
    ucl_object_insert_key(obj, ucl_object_fromstring("test_value"), key, key_length, false);

    // Call the function-under-test
    ucl_object_t *popped_obj = ucl_object_pop_key(obj, key);

    // Clean up
    if (popped_obj) {
        ucl_object_unref(popped_obj);
    }
    ucl_object_unref(obj);

    return 0;
}