#include <ucl.h>
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    struct ucl_parser *parser;
    unsigned int priority = 1; // Example priority value

    // Initialize the parser
    parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);

    if (parser != NULL) {
        // Call the function-under-test
        bool result = ucl_parser_add_chunk_priority(parser, data, size, priority);

        // Clean up the parser
        ucl_parser_free(parser);
    }

    return 0;
}