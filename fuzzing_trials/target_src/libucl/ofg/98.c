#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    unsigned int priority = 1; // Initialize with a non-zero priority

    // Initialize the parser
    parser = ucl_parser_new(UCL_PARSER_DEFAULT);
    if (parser == NULL) {
        return 0;
    }

    // Call the function-under-test
    ucl_parser_add_chunk_priority(parser, data, size, priority);

    // Clean up the parser
    ucl_parser_free(parser);

    return 0;
}