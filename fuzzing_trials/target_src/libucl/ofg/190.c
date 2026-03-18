#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // If size is 0, return immediately as we need some data to process
    if (size == 0) {
        return 0;
    }

    struct ucl_parser *parser;
    const char *cur_file;

    // Create a new UCL parser
    parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Add the input data to the parser
    ucl_parser_add_string(parser, (const char *)data, size);

    // Call the function-under-test
    cur_file = ucl_parser_get_cur_file(parser);

    // Use the result in some way (e.g., print or check)
    if (cur_file != NULL) {
        // For demonstration purposes, you might print or log the file name
        // printf("Current file: %s\n", cur_file);
    }

    // Free the parser
    ucl_parser_free(parser);

    return 0;
}