#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_278(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    janet_init();

    // Create a JanetParser
    JanetParser parser;
    janet_parser_init(&parser);

    // Feed the input data into the parser, one byte at a time
    for (size_t i = 0; i < size; i++) {
        janet_parser_consume(&parser, data[i]);
    }

    // Call the function-under-test
    Janet result = janet_parser_produce(&parser);

    // Clean up
    janet_parser_deinit(&parser);
    janet_deinit();

    return 0;
}