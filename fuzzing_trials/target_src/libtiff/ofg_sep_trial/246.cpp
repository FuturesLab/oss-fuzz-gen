#include <cstdint>
#include <cstddef>
#include <cmath>
#include <cstring> // Include for memcpy

// Function-under-test
extern "C" {
    int LogL16fromY(double, int);
}

extern "C" int LLVMFuzzerTestOneInput_246(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for extracting two values
    if (size < sizeof(double) + sizeof(int)) {
        return 0;
    }

    // Extract double from data
    double param1;
    std::memcpy(&param1, data, sizeof(double));

    // Extract int from data
    int param2;
    std::memcpy(&param2, data + sizeof(double), sizeof(int));

    // Call the function-under-test
    int result = LogL16fromY(param1, param2);

    // Optional: Use the result in some way to avoid compiler optimizations
    volatile int use_result = result;
    (void)use_result;

    return 0;
}