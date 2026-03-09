#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        ucl_parser_free(parser);
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Define some valid values for the enums
    unsigned int priority = 1;
    enum ucl_duplicate_strategy duplicate_strategy = UCL_DUPLICATE_APPEND;
    enum ucl_parse_type parse_type = UCL_PARSE_UCL;

    // Call the function under test
    bool result = ucl_parser_add_file_full(parser, filename, priority, duplicate_strategy, parse_type);

    // Clean up
    free(filename);
    ucl_parser_free(parser);

    return 0;
}