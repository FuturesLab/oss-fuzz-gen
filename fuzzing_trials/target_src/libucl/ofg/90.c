#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

// Fuzzing harness for ucl_object_get_priority
int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
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
    const ucl_object_t *root_obj = ucl_parser_get_object(parser);

    if (root_obj != NULL) {
        // Call the function-under-test
        unsigned int priority = ucl_object_get_priority(root_obj);

        // Use the result to avoid compiler optimizations
        if (priority == 0) {
            // Do something trivial
            (void)priority;
        }
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}