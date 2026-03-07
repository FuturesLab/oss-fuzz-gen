#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    struct ucl_parser *parser;
    ucl_include_trace_func_t *trace_func;
    void *user_data;

    // Initialize parser
    parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Initialize trace_func and user_data
    trace_func = (ucl_include_trace_func_t *)data; // Cast data to function pointer type
    user_data = (void *)(data + sizeof(ucl_include_trace_func_t)); // Use remaining data as user_data

    // Ensure user_data is not NULL
    if (size <= sizeof(ucl_include_trace_func_t)) {
        ucl_parser_free(parser);
        return 0;
    }

    // Call the function-under-test
    ucl_parser_set_include_tracer(parser, trace_func, user_data);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}