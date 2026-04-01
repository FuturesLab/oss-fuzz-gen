#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

// Fuzzing harness for ucl_parser_add_chunk_priority
int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Initialize the UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0; // Return if parser initialization fails
    }

    // Ensure that the data is not NULL and size is greater than 0
    if (data != NULL && size > 0) {
        // Define a non-zero priority
        unsigned int priority = 1;

        // Call the function under test
        bool result = ucl_parser_add_chunk_priority(parser, data, size, priority);

        // Use the result to avoid compiler optimizations
        (void)result;
    }

    // Clean up the parser
    ucl_parser_free(parser);

    return 0;
}