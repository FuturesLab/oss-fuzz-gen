#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to create a ucl_object_t
    if (size == 0) {
        return 0;
    }

    // Create a ucl_parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object
    const ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj != NULL) {
        // Call the function-under-test
        double result = ucl_object_todouble(obj);
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}