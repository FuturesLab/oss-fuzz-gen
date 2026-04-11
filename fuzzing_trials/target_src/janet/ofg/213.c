#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to contain at least one Janet value
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Cast the data to a Janet pointer
    const Janet *janet_data = (const Janet *)data;

    // Calculate the number of Janet elements we can safely access
    size_t janet_count = size / sizeof(Janet);

    // Iterate over each Janet element
    for (int32_t i = 0; i < (int32_t)janet_count; i++) {
        // Validate the Janet value before using it
        if (janet_checktype(janet_data[i], JANET_STRING)) {
            // Call the function-under-test with the correct arguments
            const char *result = janet_getcstring(janet_data, i);

            // Optionally, do something with the result to prevent optimizations from removing the call
            if (result != NULL) {
                // Example: print the result length (not necessary for fuzzing, just to use the result)
                size_t length = strlen(result);
                (void)length; // Suppress unused variable warning
            }
        }
    }

    return 0;
}