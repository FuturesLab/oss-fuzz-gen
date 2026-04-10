#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <janet.h>

// Function to ensure valid Janet input
static Janet safe_janet_from_bytes(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be a valid Janet object
    if (size < sizeof(Janet)) {
        // Return a default Janet value if not enough data
        return janet_wrap_nil();
    }
    // Initialize a Janet object from the data
    Janet janet;
    memcpy(&janet, data, sizeof(Janet));
    return janet;
}

int LLVMFuzzerTestOneInput_326(const uint8_t *data, size_t size) {
    // Ensure we have enough data for the function parameters
    if (size < sizeof(Janet) + 2 * sizeof(int32_t) + 1) {
        return 0;
    }

    // Initialize parameters safely
    Janet janet_data = safe_janet_from_bytes(data, size);
    int32_t n = *(const int32_t *)(data + sizeof(Janet));
    int32_t def = *(const int32_t *)(data + sizeof(Janet) + sizeof(int32_t));
    const char *dflt = (const char *)(data + sizeof(Janet) + 2 * sizeof(int32_t));

    // Ensure dflt is null-terminated to prevent undefined behavior
    size_t dflt_len = size - (sizeof(Janet) + 2 * sizeof(int32_t));
    char *dflt_safe = (char *)malloc(dflt_len + 1);
    if (!dflt_safe) {
        return 0; // Handle allocation failure
    }
    memcpy(dflt_safe, dflt, dflt_len);
    dflt_safe[dflt_len] = '\0'; // Null-terminate

    // Validate the janet_data before using it
    if (!janet_checktype(janet_data, JANET_STRING) && !janet_checktype(janet_data, JANET_SYMBOL)) {
        free(dflt_safe);
        return 0;
    }

    // Call the function-under-test
    const char *result = janet_optcbytes(&janet_data, n, def, dflt_safe);

    // Use the result to avoid compiler optimizations removing the call
    if (result) {
        // Do something with result, e.g., print or log
    }

    // Free allocated memory
    free(dflt_safe);

    return 0;
}