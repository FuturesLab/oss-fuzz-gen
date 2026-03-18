#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_DEFAULT);

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root UCL object
    const ucl_object_t *obj = ucl_parser_get_object(parser);

    if (obj != NULL) {
        // Call the function-under-test
        const char *result = ucl_object_tostring(obj);

        // Optionally, you can use the result for further testing
        if (result != NULL) {
            // Do something with the result, if needed
        }
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}