#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    ucl_object_t *obj;
    unsigned int index = 0; // Initialize index to a valid value

    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a new UCL parser
    parser = ucl_parser_new(0);

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Call the function-under-test
    obj = ucl_parser_get_current_stack_object(parser, index);

    // Free the parser
    ucl_parser_free(parser);

    // Free the object if it was successfully retrieved
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}