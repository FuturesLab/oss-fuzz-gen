#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Initialize a ucl_parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Prepare a size variable
    size_t key_length = 0;

    // Call the function-under-test
    const char *key = ucl_object_keyl(root, &key_length);

    // Use the key and key_length to avoid unused variable warnings
    if (key != NULL) {
        // Just a dummy operation to use the key and key_length
        volatile size_t dummy = key_length;
        (void)dummy;
    }

    // Free the parser and the root object
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}