#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    // Ensure that size is not zero to avoid undefined behavior
    if (size == 0) {
        return 0;
    }

    // Create a new ucl_parser instance
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Call the function-under-test
    bool result = ucl_parser_add_chunk(parser, data, size);

    // Free the parser
    ucl_parser_free(parser);

    // Return 0 as the fuzzer requires
    return 0;
}