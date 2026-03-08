#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Parse the input data as a UCL object
    ucl_parser_add_string(parser, (const char *)data, size);

    if (ucl_parser_get_error(parser) != NULL) {
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
    const ucl_object_t *head = ucl_array_head(root);

    // Clean up
    ucl_object_unref(root);
    ucl_parser_free(parser);

    return 0;
}