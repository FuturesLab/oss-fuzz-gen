#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

// Fuzzing harness for ucl_object_get_priority
int LLVMFuzzerTestOneInput_89(const uint8_t *data, size_t size) {
    // If size is 0, there's nothing to parse.
    if (size == 0) {
        return 0;
    }

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    if (!ucl_parser_add_string(parser, (const char *)data, size)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Get the UCL object from the parser
    const ucl_object_t *obj = ucl_parser_get_object(parser);
    if (obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function-under-test
    unsigned int priority = ucl_object_get_priority(obj);

    // Clean up
    ucl_object_unref(obj);
    ucl_parser_free(parser);

    return 0;
}