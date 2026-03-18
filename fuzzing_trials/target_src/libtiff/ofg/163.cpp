#include <cstddef>
#include <cstdint>
#include <cmath>
#include <cstring> // Include this for std::memcpy

// Function signature from the task
extern "C" {
    int LogL10fromY(double, int);
}

// Fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_163(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract both a double and an int
    if (size < sizeof(double) + sizeof(int)) {
        return 0;
    }

    // Extract a double from the input data
    double inputDouble;
    std::memcpy(&inputDouble, data, sizeof(double));

    // Extract an int from the input data
    int inputInt;
    std::memcpy(&inputInt, data + sizeof(double), sizeof(int));

    // Call the function-under-test
    int result = LogL10fromY(inputDouble, inputInt);

    // Use the result in some way to avoid compiler optimizations removing the call
    volatile int sink = result;
    (void)sink;

    return 0;
}