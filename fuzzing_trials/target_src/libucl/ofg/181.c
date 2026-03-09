#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    // Ensure size is non-zero to avoid undefined behavior
    if (size == 0) {
        return 0;
    }

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root UCL object
    const ucl_object_t *obj = ucl_parser_get_object(parser);

    // Unreference the UCL object if it is not NULL
    if (obj != NULL) {
        ucl_object_unref((ucl_object_t *)obj);
    }

    // Free the UCL parser
    ucl_parser_free(parser);

    return 0;
}