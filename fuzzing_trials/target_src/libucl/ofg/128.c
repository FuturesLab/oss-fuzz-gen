#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a null-terminated string
    if (size == 0) {
        return 0;
    }

    // Create a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add data as a string to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Use a portion of the data as a key for lookup
    size_t key_size = size < 10 ? size : 10; // Use up to 10 bytes for the key
    char key[key_size + 1];
    memcpy(key, data, key_size);
    key[key_size] = '\0'; // Ensure null-termination

    // Call the function-under-test
    const ucl_object_t *result = ucl_object_lookup(root, key);

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}