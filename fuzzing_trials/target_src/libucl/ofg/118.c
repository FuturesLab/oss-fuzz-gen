#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    struct ucl_parser *parser = ucl_parser_new(0);
    ucl_include_trace_func_t *trace_func = (ucl_include_trace_func_t *)data; // Casting data to function pointer
    void *user_data = (void *)(data + size / 2); // Some non-NULL pointer value

    // Ensure that the parser is not NULL
    if (parser != NULL) {
        // Call the function-under-test
        ucl_parser_set_include_tracer(parser, trace_func, user_data);

        // Clean up
        ucl_parser_free(parser);
    }

    return 0;
}