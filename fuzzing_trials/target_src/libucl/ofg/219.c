#include <stdint.h>
#include <stddef.h>
#include <ucl.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a string
    if (size < 2) {
        return 0;
    }

    // Initialize a UCL object
    ucl_object_t *root = ucl_object_typed_new(UCL_OBJECT);

    // Create a key-value pair in the UCL object
    const char *key = "test_key";
    ucl_object_insert_key(root, ucl_object_fromstring("test_value"), key, strlen(key), false);

    // Use part of the input data as a key to lookup
    size_t lookup_size = size - 1;
    char *lookup_key = (char *)malloc(lookup_size + 1);
    if (lookup_key == NULL) {
        ucl_object_unref(root);
        return 0;
    }
    memcpy(lookup_key, data, lookup_size);
    lookup_key[lookup_size] = '\0';

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_lookup_len(root, lookup_key, lookup_size);

    // Clean up
    free(lookup_key);
    ucl_object_unref(root);

    return 0;
}