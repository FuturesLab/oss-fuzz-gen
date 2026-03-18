#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_204(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    unsigned int priority = 0;
    enum ucl_duplicate_strategy duplicate_strategy = UCL_DUPLICATE_APPEND;
    enum ucl_parse_type parse_type = UCL_PARSE_UCL;

    // Initialize the parser
    parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Call the function-under-test
    bool result = ucl_parser_add_chunk_full(parser, data, size, priority, duplicate_strategy, parse_type);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}