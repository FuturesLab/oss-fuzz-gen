#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include string.h for memcpy
#include "janet.h"

// Mock function for JanetCFunction
static Janet mock_cfun(int32_t argc, Janet *argv) {
    return janet_wrap_nil();
}

int LLVMFuzzerTestOneInput_1337(const uint8_t *data, size_t size) {
    // Initialize Janet environment
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Create a mock JanetRegExt array
    JanetRegExt reg_ext[] = {
        {"mock_function", mock_cfun, "A mock function for testing."},
        {NULL, NULL, NULL} // Sentinel value to indicate end of array
    };

    // Convert data to a string for the name parameter
    char name[256];
    size_t name_len = size < 255 ? size : 255;
    memcpy(name, data, name_len);
    name[name_len] = '\0';

    // Call the function-under-test
    janet_cfuns_ext(table, name, reg_ext);

    // Clean up Janet environment
    janet_deinit();

    return 0;
}