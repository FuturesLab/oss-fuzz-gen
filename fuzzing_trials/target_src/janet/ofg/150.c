#include <stdint.h>
#include <janet.h>

// Initialize the Janet environment
static void initialize_janet_150(void) {
    janet_init();
}

// Fuzzing function
int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Initialize Janet if not already initialized
    static int initialized = 0;
    if (!initialized) {
        initialize_janet_150();
        initialized = 1;
    }

    // Ensure data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a Janet object from the input data
    Janet janet_obj = janet_stringv((const char *)data, size);

    // Call the function-under-test
    int32_t length = janet_length(janet_obj);

    // Use the length in some way to avoid compiler optimizations
    if (length < 0) {
        return 0;
    }

    return 0;
}