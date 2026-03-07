#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Initialize a ucl_parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    if (size > 0 && data != NULL) {
        ucl_parser_add_chunk(parser, data, size);
    }

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root != NULL) {
        // Call the function-under-test
        const ucl_object_t *head = ucl_array_head(root);
        (void)head; // Suppress unused variable warning
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}