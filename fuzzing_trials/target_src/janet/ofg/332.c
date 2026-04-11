#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Ensure that the Janet library is initialized before using it
static void initialize_janet_332() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

int LLVMFuzzerTestOneInput_332(const uint8_t *data, size_t size) {
    // Initialize Janet
    initialize_janet_332();

    // Define and initialize JanetSignal and Janet
    JanetSignal signal = (JanetSignal)(size % 5); // Example: mod size to limit to known signals
    Janet janet_value;

    // Ensure data is not empty to create a valid Janet string
    if (size > 0) {
        janet_value = janet_wrap_string(janet_string(data, size));
    } else {
        // Create a default Janet value if data is empty
        const char *default_str = "default";
        janet_value = janet_wrap_string(janet_cstring(default_str));
    }

    // Call the function-under-test
    janet_signalv(signal, janet_value);

    return 0;
}