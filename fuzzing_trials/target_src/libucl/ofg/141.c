#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    const char *string;
    unsigned int priority;
    bool result;

    // Initialize the parser
    parser = ucl_parser_new(UCL_PARSER_DEFAULT);

    // Ensure that the data is not NULL and has a size greater than 0
    if (data == NULL || size == 0) {
        return 0;
    }

    // Use the input data as the string to be parsed
    string = (const char *)data;

    // Set a non-zero priority for testing
    priority = 1;

    // Call the function under test
    result = ucl_parser_add_string_priority(parser, string, size, priority);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}