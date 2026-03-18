#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

// Removed 'extern "C"' as it is not valid in C, it's for C++ linkage
int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    unsigned int priority = 1;  // Arbitrary priority value
    enum ucl_duplicate_strategy duplicate_strategy = UCL_DUPLICATE_APPEND;
    enum ucl_parse_type parse_type = UCL_PARSE_UCL;

    // Initialize the parser
    parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);
    if (parser == NULL) {
        return 0;
    }

    // Call the function-under-test with the provided data
    bool result = ucl_parser_add_chunk_full(parser, data, size, priority, duplicate_strategy, parse_type);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}