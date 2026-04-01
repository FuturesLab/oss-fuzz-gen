#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_189(const uint8_t *data, size_t size) {
    // Ensure size is at least 1 to have a valid string
    if (size < 1) {
        return 0;
    }

    // Create a ucl_object_t
    ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);

    // Create a string from the data
    char *key = (char *)malloc(size + 1);
    if (key == NULL) {
        ucl_object_unref(obj);
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0';

    // Add a key-value pair to the object
    ucl_object_insert_key(obj, ucl_object_fromstring("value"), key, size, false);

    // Call the function under test
    ucl_object_delete_key(obj, key);

    // Clean up
    free(key);
    ucl_object_unref(obj);

    return 0;
}