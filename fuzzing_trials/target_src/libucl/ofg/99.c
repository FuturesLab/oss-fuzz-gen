#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    const unsigned char *chunk;
    unsigned int priority;

    // Initialize parser
    parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Use the provided data as the chunk
    chunk = data;

    // Set a non-zero priority
    priority = 1;

    // Call the function under test
    bool result = ucl_parser_add_chunk_priority(parser, chunk, size, priority);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}