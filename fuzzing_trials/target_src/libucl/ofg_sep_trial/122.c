#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    const ucl_object_t *obj = NULL;
    const ucl_object_t *tail = NULL;

    // Initialize a new UCL parser
    parser = ucl_parser_new(0);

    // Add the input data as a string to the parser
    if (size > 0) {
        ucl_parser_add_string(parser, (const char *)data, size);
    }

    // Get the parsed object
    obj = ucl_parser_get_object(parser);

    // Call the function-under-test
    if (obj != NULL) {
        tail = ucl_array_tail(obj);
    }

    // Clean up
    if (obj != NULL) {
        ucl_object_unref(obj);
    }
    ucl_parser_free(parser);

    return 0;
}