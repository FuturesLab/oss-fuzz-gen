#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
    // Initialize a ucl_parser structure
    struct ucl_parser *parser = ucl_parser_new(0);

    // Ensure the data is not empty and add it to the parser
    if (size > 0) {
        ucl_parser_add_string(parser, (const char *)data, size);
    }

    // Call the function-under-test
    int priority = ucl_parser_get_default_priority(parser);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}