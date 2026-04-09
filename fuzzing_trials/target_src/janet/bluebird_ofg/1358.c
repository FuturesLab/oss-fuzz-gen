#include <stdint.h>
#include <stddef.h>
#include "janet.h"
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_1358(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for our needs
    if (size < 2) return 0;

    // Initialize Janet
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Use part of the data as a string key
    size_t key_length = size / 2;
    char *key = (char *)malloc(key_length + 1); // Allocate memory for the key
    if (!key) {
        janet_deinit();
        return 0;
    }
    memcpy(key, data, key_length);
    key[key_length] = '\0'; // Null-terminate the string

    // Use another part of the data as a string documentation
    size_t doc_length = size - key_length - 1;
    char *doc = (char *)malloc(doc_length + 1); // Allocate memory for the doc
    if (!doc) {
        free(key);
        janet_deinit();
        return 0;
    }
    memcpy(doc, data + key_length, doc_length);
    doc[doc_length] = '\0'; // Null-terminate the string

    // Create a Janet value
    Janet value = janet_wrap_integer((int32_t)data[0]);

    // Call the function-under-test
    janet_def(table, key, value, doc);

    // Free allocated memory
    free(key);
    free(doc);

    // Clean up Janet
    janet_deinit();

    return 0;
}