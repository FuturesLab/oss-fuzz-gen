#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_string(parser, (char *)data, size);

    // Call the function-under-test
    unsigned int column = ucl_parser_get_column(parser);

    // Optionally, use the result in some way to avoid compiler optimizations
    if (column > 0) {
        // Do something trivial
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}