#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

// Define a dummy include trace function
void dummy_include_trace_func(const char *filename, const char *path, void *ud) {
    // This is a placeholder function for tracing includes
    (void)filename;
    (void)path;
    (void)ud;
}

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Initialize the ucl_parser structure
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Create a dummy user data pointer
    void *user_data = (void *)data;

    // Call the function-under-test
    ucl_parser_set_include_tracer(parser, dummy_include_trace_func, user_data);

    // Clean up
    ucl_parser_free(parser);

    return 0;
}