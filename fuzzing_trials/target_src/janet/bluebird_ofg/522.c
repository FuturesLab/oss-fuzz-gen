#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

int LLVMFuzzerTestOneInput_522(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to work with
    }

    // Initialize Janet
    janet_init();

    // Prepare the JanetTable parameter
    JanetTable *env = janet_table(0);

    // Prepare the string parameters
    char *source = (char *)malloc(size + 1);
    if (!source) {
        janet_deinit();
        return 0;
    }
    memcpy(source, data, size);
    source[size] = '\0'; // Ensure null-terminated

    const char *source_name = "fuzz_source"; // A simple source name

    // Prepare the Janet result parameter
    Janet result;

    // Call the function-under-test
    janet_dostring(env, source, source_name, &result);

    // Clean up
    free(source);
    janet_deinit();

    return 0;
}