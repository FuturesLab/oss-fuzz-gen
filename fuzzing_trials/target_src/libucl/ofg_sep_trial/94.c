#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_94(const uint8_t *data, size_t size) {
    // Initialize the ucl_parser structure
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Call the function-under-test
    bool result = ucl_parser_add_chunk(parser, data, size);

    // Free the parser after use
    ucl_parser_free(parser);

    return 0;
}