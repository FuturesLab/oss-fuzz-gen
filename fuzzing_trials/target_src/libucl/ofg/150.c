#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // If size is 0, return early as we need data to create a valid UCL object
    if (size == 0) {
        return 0;
    }

    // Create a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Check for parsing errors
    if (ucl_parser_get_error(parser) != NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the root object from the parser
    const ucl_object_t *root_obj = ucl_parser_get_object(parser);
    if (root_obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function-under-test
    ucl_object_iter_t iter = ucl_object_iterate_new(root_obj);

    // Clean up
    ucl_object_iterate_free(iter);
    ucl_object_unref(root_obj);
    ucl_parser_free(parser);

    return 0;
}