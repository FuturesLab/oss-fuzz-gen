#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Initialize a ucl_object_t from the input data
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

    // Prepare an int64_t variable to store the conversion result
    int64_t result = 0;

    // Call the function-under-test
    bool conversion_success = ucl_object_toint_safe(root, &result);

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}