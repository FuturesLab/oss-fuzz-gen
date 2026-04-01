#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
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
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function-under-test
    const ucl_object_t *tail = ucl_array_tail(root);

    // Perform any additional operations or checks if necessary
    // For example, you can verify if the tail is not NULL
    if (tail != NULL) {
        // Do something with the tail if needed
    }

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}