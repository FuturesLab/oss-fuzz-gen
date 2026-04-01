#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Ensure there's enough data for a null-terminated string
    if (size < 2) {
        return 0;
    }

    // Initialize the ucl_parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Prepare a null-terminated string from the input data
    char *file_name = (char *)malloc(size + 1);
    if (file_name == NULL) {
        ucl_parser_free(parser);
        return 0;
    }
    memcpy(file_name, data, size);
    file_name[size] = '\0';

    // Use the first byte of data as the priority value
    unsigned int priority = (unsigned int)data[0];

    // Call the function under test
    bool result = ucl_parser_add_file_priority(parser, file_name, priority);

    // Clean up
    free(file_name);
    ucl_parser_free(parser);

    return 0;
}