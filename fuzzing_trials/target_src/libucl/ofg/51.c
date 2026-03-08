#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure size is not zero to avoid passing a NULL key
    if (size == 0) {
        return 0;
    }

    // Create a ucl_object_t object
    ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

    // Use the first part of the data as a key
    const char *key = (const char *)data;
    size_t key_len = size;

    // Add a dummy value to the object with the key
    ucl_object_insert_key(obj, ucl_object_fromstring("dummy_value"), key, key_len, false);

    // Call the function under test
    bool result = ucl_object_delete_keyl(obj, key, key_len);

    // Clean up
    ucl_object_unref(obj);

    return 0;
}