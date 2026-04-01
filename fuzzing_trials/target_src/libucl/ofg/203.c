#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ucl.h"  // Assuming this is the header file where the function and related types are declared

int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_DEFAULT);
    if (parser == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a file path
    char *file_path = (char *)malloc(size + 1);
    if (file_path == NULL) {
        ucl_parser_free(parser);
        return 0;
    }
    memcpy(file_path, data, size);
    file_path[size] = '\0';

    // Define some non-null values for the enums
    enum ucl_duplicate_strategy duplicate_strategy = UCL_DUPLICATE_APPEND;
    enum ucl_parse_type parse_type = UCL_PARSE_UCL;

    // Call the function-under-test
    bool result = ucl_parser_add_file_full(parser, file_path, 0, duplicate_strategy, parse_type);

    // Clean up
    free(file_path);
    ucl_parser_free(parser);

    return 0;
}