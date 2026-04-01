#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object
    const ucl_object_t *root = ucl_parser_get_object(parser);

    // Call the function-under-test if root is not NULL
    if (root != NULL) {
        ucl_type_t type = ucl_object_type(root);
    }

    // Free the parser and the root object
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}