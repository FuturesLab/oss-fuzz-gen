#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // If size is 0, there's nothing to do
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

    // Get the root UCL object
    const ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj != NULL) {
        // Create an iterator
        ucl_object_iter_t iter = ucl_object_iterate_new(obj);

        // Free the iterator
        ucl_object_iterate_free(iter);
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}