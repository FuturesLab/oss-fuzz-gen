#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Define the LLVMFuzzerTestOneInput function
int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
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

    // Get the root object from the parser
    ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function under test
    ucl_object_t *popped_object = ucl_array_pop_first(root);

    // Clean up
    if (popped_object != NULL) {
        ucl_object_unref(popped_object);
    }
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}