#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_294(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Define some non-NULL strings for the function parameters
    const char *key = "example_key";
    const char *source_file = "example_source.c";
    const char *docstring = "This is a documentation string.";

    // Create a Janet value
    Janet janet_value = janet_wrap_integer(42);

    // Define an integer for the flags parameter
    int32_t flags = 0;

    // Call the function-under-test
    janet_def_sm(table, key, janet_value, source_file, docstring, flags);

    // Cleanup Janet
    janet_deinit();

    return 0;
}