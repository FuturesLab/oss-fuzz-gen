#include <cstdint>
#include <cstddef>
#include <cstring> // Include for std::memcpy
#include <cmath>

// Assume the function LogL16fromY is defined in some C library
extern "C" {
    int LogL16fromY(double value, int exponent);
}

extern "C" int LLVMFuzzerTestOneInput_245(const uint8_t *data, size_t size) {
    if (size < sizeof(double) + sizeof(int)) {
        return 0; // Not enough data to extract both parameters
    }

    // Extract a double from the input data
    double value;
    std::memcpy(&value, data, sizeof(double));

    // Extract an int from the input data
    int exponent;
    std::memcpy(&exponent, data + sizeof(double), sizeof(int));

    // Call the function-under-test
    int result = LogL16fromY(value, exponent);

    // Optionally, use the result to prevent compiler optimizations
    volatile int prevent_optimization = result;
    (void)prevent_optimization;

    return 0;
}