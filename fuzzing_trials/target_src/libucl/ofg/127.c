#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts: one for the key and one for the object
    size_t key_size = data[0] % size; // Determine the size of the key
    const char *key = (const char *)(data + 1); // Key starts after the first byte
    const uint8_t *object_data = data + 1 + key_size; // Object data starts after the key
    size_t object_size = size - 1 - key_size; // Remaining data for the object

    // Create a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the object data
    if (!ucl_parser_add_chunk(parser, object_data, object_size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Ensure the key is null-terminated
    char *key_null_terminated = (char *)malloc(key_size + 1);
    if (key_null_terminated == NULL) {
        ucl_parser_free(parser);
        return 0;
    }
    memcpy(key_null_terminated, key, key_size);
    key_null_terminated[key_size] = '\0';

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_lookup(root, key_null_terminated);

    // Clean up
    free(key_null_terminated);
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}