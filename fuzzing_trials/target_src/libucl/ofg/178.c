#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_178(const uint8_t *data, size_t size) {
    // Initialize a ucl_parser structure
    struct ucl_parser *parser = ucl_parser_new(0);

    // Add data to the parser if size is greater than 0
    if (size > 0) {
        ucl_parser_add_string(parser, (const char *)data, size);
    }

    // Call the function-under-test
    int priority = ucl_parser_get_default_priority(parser);

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}