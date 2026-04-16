#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

// Initialize Janet runtime
void initialize_janet_1417() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

int LLVMFuzzerTestOneInput_1417(const uint8_t *data, size_t size) {
    initialize_janet_1417();

    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize JanetTable
    JanetTable *table = janet_table(10);

    // Extract a string from the data
    char key[256];
    size_t key_length = size > 255 ? 255 : size;
    memcpy(key, data, key_length);
    key[key_length] = '\0';

    // Ensure data is large enough for a Janet value
    if (size < sizeof(Janet) + 1) {
        return 0;
    }

    // Extract a Janet value from the data safely
    Janet value;
    if (size >= sizeof(Janet)) {
        value = janet_wrap_integer((int32_t)data[0]);
    } else {
        value = janet_wrap_nil();
    }

    // Extract a string from the data for docstring
    const char *docstring = "This is a test docstring";

    // Extract a string from the data for source
    const char *source = "test_source";

    // Extract an integer from the data
    int32_t flags = (int32_t)data[0];

    // Call the function-under-test
    janet_def_sm(table, key, value, docstring, source, flags);

    return 0;
}