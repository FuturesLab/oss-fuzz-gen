#include <stdint.h>
#include <stddef.h>

// Function-under-test
void janet_gcpressure(size_t);

// Fuzzing harness
int LLVMFuzzerTestOneInput_245(const uint8_t *data, size_t size) {
    // Convert the input data to a size_t value
    size_t pressure_value = 0;

    // Ensure there's enough data to read a size_t value
    if (size >= sizeof(size_t)) {
        // Copy data to pressure_value
        for (size_t i = 0; i < sizeof(size_t); i++) {
            pressure_value |= ((size_t)data[i]) << (i * 8);
        }
    } else {
        // If not enough data, use a default non-zero value
        pressure_value = 1024;
    }

    // Call the function-under-test
    janet_gcpressure(pressure_value);

    return 0;
}