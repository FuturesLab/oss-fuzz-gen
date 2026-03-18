#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    // If size is 0, return early as we need some data to work with
    if (size == 0) {
        return 0;
    }

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root != NULL) {
        // Call the function-under-test
        unsigned int priority = ucl_object_get_priority(root);

        // Use the priority value to avoid compiler optimizations
        (void)priority;
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}