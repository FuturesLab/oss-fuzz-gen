#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Function to initialize Janet runtime
void initialize_janet_273() {
    janet_init();
}

int LLVMFuzzerTestOneInput_273(const uint8_t *data, size_t size) {
    // Initialize Janet runtime
    initialize_janet_273();

    Janet janet_value;

    if (size < sizeof(Janet)) {
        return 0;
    }

    // Initialize a Janet value from the input data
    janet_value = *(Janet *)data;

    // Call the function-under-test
    JanetType type = janet_type(janet_value);

    // Use the result to avoid any compiler optimizations
    if (type == JANET_NIL) {
        return 0;
    }

    // Clean up Janet runtime
    janet_deinit();

    return 0;
}