#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
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
    if (!ucl_parser_add_string(parser, (const char *)data, size)) {
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
    ucl_object_t *ref_obj = ucl_object_ref(root_obj);

    // Clean up
    ucl_object_unref(ref_obj);
    ucl_parser_free(parser);

    return 0;
}