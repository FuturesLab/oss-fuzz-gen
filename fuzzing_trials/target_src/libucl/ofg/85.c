#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>  // Include this for the bool type

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object from the parser
    const ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj != NULL) {
        // Call the function-under-test
        bool result = ucl_object_toboolean(obj);
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}