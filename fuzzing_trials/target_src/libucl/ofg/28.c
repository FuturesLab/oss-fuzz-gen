#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Ensure size is non-zero for a valid string
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Convert data to a null-terminated string
    char *input_string = (char *)data;

    // Call the function-under-test
    bool result = ucl_parser_add_string(parser, input_string, size);

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}