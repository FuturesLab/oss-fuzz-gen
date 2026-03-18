#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h> // Include this for the bool type

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Initialize the ucl_parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Prepare an int64_t variable to store the result
    int64_t result = 0;

    // Call the function-under-test
    bool success = ucl_object_toint_safe(root, &result);

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}