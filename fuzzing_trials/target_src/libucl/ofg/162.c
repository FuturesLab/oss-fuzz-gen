#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    unsigned int priority = 1; // Arbitrary non-zero priority
    enum ucl_duplicate_strategy duplicate_strategy = UCL_DUPLICATE_APPEND; // Example strategy
    enum ucl_parse_type parse_type = UCL_PARSE_UCL; // Example parse type

    // Initialize UCL parser
    parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0; // Exit if parser creation fails
    }

    // Call the function-under-test
    if (size > 0) {
        ucl_parser_add_chunk_full(parser, data, size, priority, duplicate_strategy, parse_type);
    }

    // Clean up
    ucl_parser_free(parser);

    return 0;
}