#include <stdint.h>
#include <stddef.h>
#include "janet.h"
#include <string.h>

// Helper function to check if a string is valid UTF-8
int is_valid_utf8(const char *string, size_t length) {
    const unsigned char *bytes = (const unsigned char *)string;
    size_t i = 0;
    while (i < length) {
        if (bytes[i] <= 0x7F) {
            // ASCII
            i += 1;
        } else if ((bytes[i] & 0xE0) == 0xC0) {
            // 2-byte sequence
            if (i + 1 >= length || (bytes[i + 1] & 0xC0) != 0x80) return 0;
            i += 2;
        } else if ((bytes[i] & 0xF0) == 0xE0) {
            // 3-byte sequence
            if (i + 2 >= length || (bytes[i + 1] & 0xC0) != 0x80 || (bytes[i + 2] & 0xC0) != 0x80) return 0;
            i += 3;
        } else if ((bytes[i] & 0xF8) == 0xF0) {
            // 4-byte sequence
            if (i + 3 >= length || (bytes[i + 1] & 0xC0) != 0x80 || (bytes[i + 2] & 0xC0) != 0x80 || (bytes[i + 3] & 0xC0) != 0x80) return 0;
            i += 4;
        } else {
            return 0;
        }
    }
    return 1;
}

int LLVMFuzzerTestOneInput_1388(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a valid symbol
    if (size == 0 || !is_valid_utf8((const char *)data, size)) {
        return 0;
    }

    // Initialize Janet environment
    janet_init();

    // Create a JanetSymbol from the input data
    const char *symbol_data = (const char *)data;
    JanetSymbol symbol = janet_symbol(symbol_data, size);

    // Call the function-under-test
    Janet result = janet_wrap_symbol(symbol);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    // Clean up Janet environment
    janet_deinit();

    return 0;
}