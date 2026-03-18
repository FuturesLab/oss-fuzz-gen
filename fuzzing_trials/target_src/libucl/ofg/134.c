#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

// Dummy macro handler function
bool dummy_macro_handler_134(struct ucl_parser *parser, const unsigned char *data,
                         size_t len, const ucl_object_t *args, void *ud) {
    return true;
}

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    const char *macro_name = "test_macro";
    void *user_data = (void *)0x1;  // Non-NULL user data

    // Initialize the parser
    parser = ucl_parser_new(0);

    // Ensure the parser is not NULL
    if (parser == NULL) {
        return 0;
    }

    // Register the macro
    ucl_parser_register_macro(parser, macro_name, dummy_macro_handler_134, user_data);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}