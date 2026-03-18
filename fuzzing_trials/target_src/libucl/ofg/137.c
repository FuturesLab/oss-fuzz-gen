#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a ucl_parser and parse the input data
    struct ucl_parser *parser = ucl_parser_new(0);
    ucl_parser_add_string(parser, (const char *)data, size);

    // Get the root object
    const ucl_object_t *obj = ucl_parser_get_object(parser);

    // Prepare a boolean variable to store the result
    _Bool result = false;

    // Call the function-under-test
    if (obj != NULL) {
        ucl_object_toboolean_safe(obj, &result);
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}