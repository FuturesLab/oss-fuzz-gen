#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_198(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
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
        const char *result = ucl_object_tostring_forced(obj);

        // Use the result in some way to avoid compiler optimizations
        if (result != NULL) {
            size_t len = strlen(result);
            (void)len; // Suppress unused variable warning
        }
    }

    // Clean up
    ucl_object_unref(obj);
    ucl_parser_free(parser);

    return 0;
}