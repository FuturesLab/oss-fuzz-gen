#include <cstdint>
#include <cstddef>
#include <cmath>
#include <limits>
#include <cstring> // Include this header for std::memcpy

// Function signature from the task
extern "C" int LogL10fromY(double, int);

// Fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract both a double and an int
    if (size < sizeof(double) + sizeof(int)) {
        return 0;
    }

    // Extract a double value from the input data
    double value;
    std::memcpy(&value, data, sizeof(double));

    // Extract an int value from the input data
    int exponent;
    std::memcpy(&exponent, data + sizeof(double), sizeof(int));

    // Call the function-under-test with the extracted values
    int result = LogL10fromY(value, exponent);

    // Use the result in some way (here we simply ignore it)
    (void)result;

    return 0;
}