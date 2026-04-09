#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_374(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for creating a string and Janet value
    if (size < 2) {
        return 0;
    }

    // Initialize Janet environment
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Use the first byte of data as a string length
    size_t str_len = data[0] % (size - 1) + 1; // Ensure str_len is at least 1 and less than size
    const char *key = (const char *)(data + 1);

    // Ensure the key is null-terminated
    char *key_copy = (char *)malloc(str_len + 1);
    if (!key_copy) {
        janet_deinit();
        return 0;
    }
    memcpy(key_copy, key, str_len);
    key_copy[str_len] = '\0';

    // Create a Janet value from the remaining data
    Janet value = janet_wrap_integer(data[str_len + 1]);

    // Use a constant string for the documentation
    const char *doc = "Fuzzing test documentation";

    // Call the function-under-test
    janet_def(table, key_copy, value, doc);

    // Clean up
    free(key_copy);
    janet_deinit();

    return 0;
}