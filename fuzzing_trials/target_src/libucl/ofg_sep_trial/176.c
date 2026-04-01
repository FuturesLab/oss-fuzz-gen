#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    // Ensure the size is non-zero to avoid undefined behavior
    if (size == 0) {
        return 0;
    }

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);

    // Add the input data as a string to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Clear any errors in the parser
    ucl_parser_clear_error(parser);

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}