#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

// A sample variable handler function
static const char *sample_variable_handler(const char *var, size_t var_len, void *ud) {
    // Just return a static string for simplicity
    return "sample_value";
}

int LLVMFuzzerTestOneInput_74(const uint8_t *data, size_t size) {
    // Initialize the parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Use the first byte of data to decide whether to set a non-NULL user data
    void *user_data = NULL;
    if (size > 0 && data[0] % 2 == 0) {
        user_data = (void *)data;
    }

    // Set the variable handler
    ucl_parser_set_variables_handler(parser, sample_variable_handler, user_data);

    // Clean up
    ucl_parser_free(parser);
    return 0;
}