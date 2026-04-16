#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy
#include <janet.h>   // Include Janet library

// Initialize the Janet runtime
__attribute__((constructor))
static void initialize_janet_304(void) {
    janet_init();
}

// Fuzzing harness for janet_unwrap_boolean
int LLVMFuzzerTestOneInput_304(const uint8_t *data, size_t size) {
    // Check if size is sufficient to create a Janet value
    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize a Janet value from the input data
    Janet janet_value;
    memcpy(&janet_value, data, sizeof(Janet));

    // Call the function-under-test
    int result = janet_unwrap_boolean(janet_value);

    // Use the result in some way to prevent the compiler from optimizing it away
    (void)result;

    return 0;
}

// Cleanup the Janet runtime
__attribute__((destructor))
static void cleanup_janet(void) {
    janet_deinit();
}