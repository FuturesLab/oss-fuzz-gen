#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Ensure that there is enough data for two strings
    if (size < 2) {
        return 0;
    }

    // Allocate memory for two strings
    size_t half_size = size / 2;
    char *var_name = (char *)malloc(half_size + 1);
    char *var_value = (char *)malloc(half_size + 1);

    if (var_name == NULL || var_value == NULL) {
        free(var_name);
        free(var_value);
        return 0;
    }

    // Copy data into two strings and null-terminate them
    memcpy(var_name, data, half_size);
    var_name[half_size] = '\0';

    memcpy(var_value, data + half_size, half_size);
    var_value[half_size] = '\0';

    // Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        free(var_name);
        free(var_value);
        return 0;
    }

    // Call the function-under-test
    ucl_parser_register_variable(parser, var_name, var_value);

    // Clean up
    ucl_parser_free(parser);
    free(var_name);
    free(var_value);

    return 0;
}