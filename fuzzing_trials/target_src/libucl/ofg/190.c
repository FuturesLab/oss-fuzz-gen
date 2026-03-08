#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form a key
    if (size == 0) {
        return 0;
    }

    // Create a ucl_object_t
    ucl_object_t *obj = ucl_object_new();

    // Create a key from the input data
    // Ensure the key is null-terminated
    char *key = (char *)malloc(size + 1);
    if (key == NULL) {
        ucl_object_unref(obj);
        return 0;
    }
    memcpy(key, data, size);
    key[size] = '\0';

    // Call the function-under-test
    bool result = ucl_object_delete_key(obj, key);

    // Clean up
    free(key);
    ucl_object_unref(obj);

    return 0;
}