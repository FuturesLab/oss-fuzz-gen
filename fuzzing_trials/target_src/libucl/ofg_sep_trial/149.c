#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object from the parser
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root != NULL) {
        // Call the function-under-test
        ucl_object_iter_t iter = ucl_object_iterate_new(root);

        // Normally, you would use the iterator here, but since we're fuzzing,
        // we just want to ensure that the function is called.
        (void)iter; // Suppress unused variable warning
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}