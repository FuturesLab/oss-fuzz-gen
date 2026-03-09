#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a meaningful ucl_object_t
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
    if (root != NULL) {
        // Call the function-under-test
        int64_t result = ucl_object_toint(root);
        (void)result; // Suppress unused variable warning
    }

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}