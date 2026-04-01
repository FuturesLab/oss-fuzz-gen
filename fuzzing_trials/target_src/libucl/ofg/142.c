#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    struct ucl_parser *parser = ucl_parser_new(0);
    const char *input_string = (const char *)data;
    unsigned int priority = 0; // You can try different priority values

    if (parser != NULL && input_string != NULL && size > 0) {
        // Call the function-under-test
        bool result = ucl_parser_add_string_priority(parser, input_string, size, priority);

        // You can add additional logic here to further test or verify the result
        (void)result; // Suppress unused variable warning
    }

    ucl_parser_free(parser);

    return 0;
}