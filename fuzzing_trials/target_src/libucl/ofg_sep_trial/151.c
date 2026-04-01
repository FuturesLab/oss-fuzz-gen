#include <stdint.h>
#include <stddef.h>
#include "ucl.h"

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // If size is 0, we cannot create a valid string for parsing.
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    
    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Call the function-under-test
    unsigned int line_number = ucl_parser_get_linenum(parser);

    // Use the line_number in some way to avoid compiler optimizations
    if (line_number > 0) {
        // Dummy operation
        line_number = line_number;
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}