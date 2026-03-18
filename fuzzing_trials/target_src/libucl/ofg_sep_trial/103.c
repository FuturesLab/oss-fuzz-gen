#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    if (!ucl_parser_add_string(parser, (const char *)data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);
    if (root == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function-under-test
    unsigned int array_size = ucl_array_size(root);

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}