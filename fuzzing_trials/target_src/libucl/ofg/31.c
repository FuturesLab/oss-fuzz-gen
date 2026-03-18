#include <ucl.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Initialize variables
    struct ucl_parser *parser;
    unsigned int priority = 0;
    enum ucl_duplicate_strategy duplicate_strategy;
    enum ucl_parse_type parse_type;

    // Create a new UCL parser
    parser = ucl_parser_new(UCL_PARSER_DEFAULT);

    // Ensure parser is not NULL
    if (parser == NULL) {
        return 0;
    }

    // Set duplicate_strategy and parse_type with valid enumeration values
    duplicate_strategy = UCL_DUPLICATE_APPEND; // Example value
    parse_type = UCL_PARSE_UCL; // Example value

    // Call the function-under-test
    ucl_parser_add_chunk_full(parser, data, size, priority, duplicate_strategy, parse_type);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}