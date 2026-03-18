#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_202(const uint8_t *data, size_t size) {
    // Ensure the data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add data to the parser
    ucl_parser_add_chunk(parser, data, size);

    // Get the root object from the parser
    const ucl_object_t *root_obj = ucl_parser_get_object(parser);
    if (root_obj != NULL) {
        // Call the function-under-test
        const char *result = ucl_object_tostring_forced(root_obj);

        // Use the result to prevent compiler optimizations
        if (result != NULL) {
            volatile size_t result_len = strlen(result);
            (void)result_len;
        }
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}