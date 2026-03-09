#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_144(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    ucl_object_t *top = ucl_object_typed_new(UCL_OBJECT);
    ucl_object_t *elt = ucl_object_typed_new(UCL_OBJECT);
    char *key = NULL;
    bool merge = true;

    // Ensure size is sufficient to extract a key
    if (size > 0) {
        // Allocate memory for the key and copy from data
        key = (char *)malloc(size + 1);
        if (key != NULL) {
            memcpy(key, data, size);
            key[size] = '\0'; // Null-terminate the key
        }
    }

    // Call the function-under-test
    if (key != NULL) {
        ucl_object_insert_key_merged(top, elt, key, size, merge);
    }

    // Clean up
    if (key != NULL) {
        free(key);
    }
    ucl_object_unref(top);
    ucl_object_unref(elt);

    return 0;
}