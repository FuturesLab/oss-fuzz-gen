#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ucl.h>

// Dummy macro handler function
bool dummy_macro_handler(const unsigned char *data, size_t len, const ucl_object_t *args, ucl_object_t **res, void *ud) {
    return true;
}

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    const char *macro_name = "test_macro";
    void *user_data = (void *)0x1; // Non-NULL user data

    // Initialize the parser
    parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);

    // Ensure the parser is created successfully
    if (parser == NULL) {
        return 0;
    }

    // Register the macro with the parser
    ucl_parser_register_macro(parser, macro_name, dummy_macro_handler, user_data);

    // Feed the input data to the parser
    ucl_parser_add_chunk(parser, data, size);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}