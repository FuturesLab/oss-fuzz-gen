#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    char *input_string;
    unsigned int priority;

    // Initialize the parser
    parser = ucl_parser_new(UCL_PARSER_DEFAULT);
    if (parser == NULL) {
        return 0;
    }

    // Ensure that the input string is null-terminated
    input_string = (char *)malloc(size + 1);
    if (input_string == NULL) {
        ucl_parser_free(parser);
        return 0;
    }
    memcpy(input_string, data, size);
    input_string[size] = '\0';

    // Set a fixed priority for fuzzing
    priority = 1;

    // Call the function-under-test
    bool result = ucl_parser_add_string_priority(parser, input_string, size, priority);

    // Clean up
    free(input_string);
    ucl_parser_free(parser);

    return 0;
}