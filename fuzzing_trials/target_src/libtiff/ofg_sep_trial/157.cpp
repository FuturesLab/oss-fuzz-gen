#include <cstdint>
#include <cstddef>
#include <cstring> // Include this header for std::memcpy

// Assuming the function is defined elsewhere
extern "C" int LogL10fromY(double, int);

extern "C" int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
    if (size < sizeof(double) + sizeof(int)) {
        return 0; // Not enough data to extract both double and int
    }

    // Extract a double from the input data
    double d;
    std::memcpy(&d, data, sizeof(double));

    // Extract an int from the input data
    int i;
    std::memcpy(&i, data + sizeof(double), sizeof(int));

    // Call the function-under-test
    LogL10fromY(d, i);

    return 0;
}