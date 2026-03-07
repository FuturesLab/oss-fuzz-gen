#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a key string
    if (size < 2) {
        return 0;
    }

    // Create a ucl_object_t
    ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

    // Add a key-value pair to the object for testing
    const char *key = "test_key";
    ucl_object_t *val = ucl_object_fromstring("test_value");
    ucl_object_insert_key(obj, val, key, strlen(key), false);

    // Use part of the input data as a key for ucl_object_pop_key
    char *input_key = (char *)malloc(size + 1);
    memcpy(input_key, data, size);
    input_key[size] = '\0';  // Ensure null-termination

    // Call the function-under-test
    ucl_object_t *popped_obj = ucl_object_pop_key(obj, input_key);

    // Clean up
    if (popped_obj != NULL) {
        ucl_object_unref(popped_obj);
    }
    ucl_object_unref(obj);
    free(input_key);

    return 0;
}