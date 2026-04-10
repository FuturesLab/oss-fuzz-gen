#include <stdint.h>
#include <stddef.h>
#include <janet.h> // Assuming this is the correct header for JanetParser and related functions

int LLVMFuzzerTestOneInput_333(const uint8_t *data, size_t size) {
    // Initialize Janet environment
    janet_init();

    // Create a new Janet parser
    JanetParser parser;
    janet_parser_init(&parser);

    // Feed data to the parser, byte by byte
    for (size_t i = 0; i < size; i++) {
        janet_parser_consume(&parser, data[i]);
    }

    // Call the function-under-test
    enum JanetParserStatus status = janet_parser_status(&parser);

    // Clean up
    janet_parser_deinit(&parser);
    janet_deinit();

    return 0;
}