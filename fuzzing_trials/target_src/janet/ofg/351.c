#include <stdint.h>
#include <stddef.h>
#include <janet.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_351(const uint8_t *data, size_t size) {
    if (size < 2) return 0; // Ensure there's enough data for format string and at least one argument

    // Initialize Janet VM
    janet_init();

    // Create a JanetBuffer
    JanetBuffer *buffer = janet_buffer(10); // Initial size of 10

    // Use the first byte as the length of the format string
    size_t format_len = data[0] % (size - 1); // Ensure it doesn't exceed the data size
    const char *format = (const char *)(data + 1);

    // Ensure the format string is null-terminated
    char *format_str = (char *)malloc(format_len + 1);
    if (!format_str) {
        janet_deinit();
        return 0;
    }
    memcpy(format_str, format, format_len);
    format_str[format_len] = '\0';

    // Use the remaining data as the argument
    Janet arg = janet_wrap_string(janet_string((const uint8_t *)(data + 1 + format_len), size - 1 - format_len));

    // Call the function-under-test
    janet_formatb(buffer, format_str, arg);

    // Clean up
    free(format_str);
    janet_deinit();

    return 0;
}