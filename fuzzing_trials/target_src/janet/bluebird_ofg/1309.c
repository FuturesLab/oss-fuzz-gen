#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

// Declare the external function correctly
extern void janet_var(JanetTable *, const char *, Janet, const char *);

// Define the fuzzer test function
int LLVMFuzzerTestOneInput_1309(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for our needs
    if (size < 4) return 0;

    // Initialize Janet runtime
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Ensure null-terminated strings
    char key[256];
    char documentation[256];

    // Copy and null-terminate the key and documentation strings
    size_t key_len = (size < 255) ? size : 255;
    memcpy(key, data, key_len);
    key[key_len] = '\0';

    size_t doc_len = (size - 2 < 255) ? size - 2 : 255;
    memcpy(documentation, data + 2, doc_len);
    documentation[doc_len] = '\0';

    // Use the second byte as an index for a Janet value
    Janet value = janet_wrap_integer(data[1]);

    // Call the function-under-test
    janet_var(table, key, value, documentation);

    // Clean up Janet runtime
    janet_deinit();

    return 0;
}