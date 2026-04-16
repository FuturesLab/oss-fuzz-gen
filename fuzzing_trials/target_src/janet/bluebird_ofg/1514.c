#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

extern int janet_symeq(Janet, const char *);

int LLVMFuzzerTestOneInput_1514(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a non-empty string
    if (size == 0) return 0;

    // Initialize the Janet environment
    janet_init();

    // Ensure null-termination for the C string
    char c_str[size + 1];
    memcpy(c_str, data, size);
    c_str[size] = '\0';

    // Create a Janet string from the input data
    Janet janet_str = janet_cstringv(c_str);

    // Call the function-under-test
    janet_symeq(janet_str, c_str);

    // Clean up the Janet environment
    janet_deinit();

    return 0;
}