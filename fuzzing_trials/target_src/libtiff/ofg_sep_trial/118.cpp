#include <cstdint>
#include <cmath>
#include <cstddef>  // For size_t
#include <cstring>  // For std::memcpy

// Function signature provided
extern "C" double LogL10toY(int x);

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Ensure the input size is at least the size of an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int x;
    std::memcpy(&x, data, sizeof(int));

    // Call the function-under-test
    double result = LogL10toY(x);

    // Use the result in some way to avoid compiler optimizations
    volatile double avoid_optimization = result;

    return 0;
}