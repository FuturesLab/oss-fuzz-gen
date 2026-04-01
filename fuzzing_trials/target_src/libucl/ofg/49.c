#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a key
    if (size == 0) {
        return 0;
    }

    // Create a new UCL object
    ucl_object_t *ucl_obj = ucl_object_new();

    // Add a dummy key-value pair to the UCL object
    const char *dummy_key = "dummy_key";
    ucl_object_insert_key(ucl_obj, ucl_object_fromstring("dummy_value"), dummy_key, strlen(dummy_key), false);

    // Use the input data as the key to delete
    const char *key_to_delete = (const char *)data;

    // Call the function-under-test
    bool result = ucl_object_delete_keyl(ucl_obj, key_to_delete, size);

    // Clean up
    ucl_object_unref(ucl_obj);

    return 0;
}