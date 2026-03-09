#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    ucl_object_t *obj = NULL;
    ucl_object_iter_t iter = NULL;

    if (parser != NULL) {
        // Attempt to parse the input data
        ucl_parser_add_chunk(parser, data, size);

        // Get the parsed object
        obj = ucl_parser_get_object(parser);

        // If an object was successfully parsed, create an iterator
        if (obj != NULL) {
            iter = ucl_object_iterate_new(obj);
        }

        // Free the parser
        ucl_parser_free(parser);
    }

    // Free the iterator if it was created
    if (iter != NULL) {
        ucl_object_iterate_free(iter);
    }

    // Free the parsed object
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}