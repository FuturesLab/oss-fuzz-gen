#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Initialize a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    if (!ucl_parser_add_chunk(parser, data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root object from the parser
    const ucl_object_t *root_obj = ucl_parser_get_object(parser);
    if (root_obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Prepare a size variable
    size_t str_size = 0;

    // Call the function under test
    const char *result_str = ucl_object_tolstring(root_obj, &str_size);

    // Print the result string and its size
    if (result_str != NULL) {
        printf("Result string: %.*s\n", (int)str_size, result_str);
    }

    // Free the UCL parser and the root object
    ucl_object_unref(root_obj);
    ucl_parser_free(parser);

    return 0;
}