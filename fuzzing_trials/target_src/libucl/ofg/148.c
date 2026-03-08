#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // If size is 0 we need a null-terminated string.
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser;
    const ucl_object_t *comments;

    // Initialize the parser
    parser = ucl_parser_new(0);

    // Add data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Retrieve comments
    comments = ucl_parser_get_comments(parser);

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}