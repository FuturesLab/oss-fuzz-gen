#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_50(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a key
    if (size < 1) {
        return 0;
    }

    // Create a ucl_object_t
    ucl_object_t *obj = ucl_object_new();

    // Add a key-value pair to the object for testing deletion
    const char *key = "test_key";
    ucl_object_insert_key(obj, ucl_object_fromstring("test_value"), key, strlen(key), false);

    // Prepare a key from the data
    const char *key_to_delete = (const char *)data;
    size_t key_len = size;

    // Call the function-under-test
    bool result = ucl_object_delete_keyl(obj, key_to_delete, key_len);

    // Cleanup
    ucl_object_unref(obj);

    return 0;
}