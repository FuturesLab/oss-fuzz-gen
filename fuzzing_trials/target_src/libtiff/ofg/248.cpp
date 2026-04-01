#include <cstdint>
#include <cstddef>
#include <cmath>
#include <cstring> // Include the necessary header for memcpy

// Function signature for the function-under-test
extern "C" int LogL16fromY(double, int);

// Fuzzing harness for the function-under-test
extern "C" int LLVMFuzzerTestOneInput_248(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract parameters
    if (size < sizeof(double) + sizeof(int)) {
        return 0;
    }

    // Extract a double value from the input data
    double param1;
    std::memcpy(&param1, data, sizeof(double));

    // Extract an int value from the input data
    int param2;
    std::memcpy(&param2, data + sizeof(double), sizeof(int));

    // Call the function-under-test with the extracted parameters
    int result = LogL16fromY(param1, param2);

    // Use the result in some way to avoid compiler optimizations
    volatile int sink = result;
    (void)sink;

    return 0;
}