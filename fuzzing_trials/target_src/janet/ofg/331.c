#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

// Function prototype for the function-under-test
void janet_signalv(JanetSignal signal, Janet value);

int LLVMFuzzerTestOneInput_331(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient to extract a JanetSignal and a Janet value
    if (size < sizeof(JanetSignal) + sizeof(Janet)) {
        return 0;
    }

    // Extract a JanetSignal from the input data
    JanetSignal signal = (JanetSignal)(data[0] % 4);  // Assuming 4 possible signals

    // Extract a Janet value from the input data
    Janet value;
    janet_init();
    if (size > sizeof(JanetSignal)) {
        // Use the remaining data as a byte array for Janet
        value = janet_wrap_string(janet_string(data + sizeof(JanetSignal), size - sizeof(JanetSignal)));
    } else {
        // Default value if not enough data
        value = janet_wrap_nil();
    }

    // Call the function-under-test
    janet_signalv(signal, value);

    // Clean up Janet environment
    janet_deinit();

    return 0;
}