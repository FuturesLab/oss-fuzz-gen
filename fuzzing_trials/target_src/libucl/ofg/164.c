#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
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
        // Call the function under test
        char *result = ucl_copy_value_trash(obj);

        // Free the result if it was allocated
        if (result != NULL) {
            free(result);
        }
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}