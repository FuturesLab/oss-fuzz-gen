#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_22(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object
    ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Create a dummy object to delete
    ucl_object_t *dummy = ucl_object_fromstring("dummy");

    // Call the function under test
    ucl_object_t *result = ucl_array_delete(root, dummy);

    // Clean up
    ucl_object_unref(root);
    ucl_object_unref(dummy);
    ucl_parser_free(parser);

    // Unref the result if it's not NULL
    if (result != NULL) {
        ucl_object_unref(result);
    }

    return 0;
}