#include <stddef.h>
#include <stdint.h>

// Assume the function is defined in some library we are linking against
void janet_gcpressure(size_t);

int LLVMFuzzerTestOneInput_244(const uint8_t *data, size_t size) {
    // Convert the input data to a size_t value
    size_t pressure_value = 0;

    // Ensure we have enough data to read a size_t value
    if (size >= sizeof(size_t)) {
        // Copy the data into the pressure_value variable
        pressure_value = *((const size_t *)data);
    } else {
        // If not enough data, use the size itself as a pressure value
        pressure_value = size;
    }

    // Call the function-under-test
    janet_gcpressure(pressure_value);

    return 0;
}