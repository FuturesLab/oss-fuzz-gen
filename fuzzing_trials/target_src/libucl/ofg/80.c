#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;

    // Initialize a new UCL parser
    parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Call the function-under-test with the provided data
    bool result = ucl_parser_insert_chunk(parser, data, size);

    // Free the parser after use
    ucl_parser_free(parser);

    return result ? 0 : 1;
}