#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    // Initialize the ucl_parser structure
    struct ucl_parser *parser = ucl_parser_new(0);

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Call the function-under-test
    int error_code = ucl_parser_get_error_code(parser);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}