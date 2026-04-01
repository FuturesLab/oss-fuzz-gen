#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
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
        // Prepare a size variable
        size_t str_size = 0;

        // Call the function under test
        const char *str = ucl_object_tolstring(obj, &str_size);

        // Use the resulting string and size
        if (str != NULL) {
            // Do something with the string if needed
            // For example, print it (not needed for fuzzing, just illustrative)
            // printf("String: %s, Size: %zu\n", str, str_size);
        }
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}