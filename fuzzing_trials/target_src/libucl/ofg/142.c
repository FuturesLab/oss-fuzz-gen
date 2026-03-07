#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_DEFAULT);
    const char *input_string = (const char *)data;
    unsigned int priority = 0;

    // Ensure size is not zero to avoid passing a NULL string
    if (size > 0) {
        // Call the function-under-test
        bool result = ucl_parser_add_string_priority(parser, input_string, size, priority);

        // Optionally, you can use the result to perform further operations or checks
        (void)result; // Suppress unused variable warning
    }

    // Clean up
    ucl_parser_free(parser);

    return 0;
}