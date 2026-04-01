#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

// Dummy macro handler function
bool dummy_macro_handler_133(struct ucl_parser *parser, const unsigned char *data, size_t len, void *ud) {
    return true;
}

int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    const char *macro_name = "test_macro";
    void *user_data = (void *)0x1;  // Arbitrary non-NULL pointer for user data

    // Initialize the parser
    parser = ucl_parser_new(UCL_PARSER_DEFAULT);
    if (parser == NULL) {
        return 0;
    }

    // Register the macro
    ucl_parser_register_macro(parser, macro_name, dummy_macro_handler_133, user_data);

    // Feed the input data to the parser
    ucl_parser_add_chunk(parser, data, size);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}