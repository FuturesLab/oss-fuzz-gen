#include <cstdint>
#include <cstddef>
#include <cmath>

// Assuming that the function LogL16toY is defined elsewhere
extern "C" double LogL16toY(int value);

extern "C" int LLVMFuzzerTestOneInput_251(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to form an int
    }

    // Convert the first 4 bytes of the data into an int
    int input_value = 0;
    for (size_t i = 0; i < sizeof(int); ++i) {
        input_value |= (data[i] << (i * 8));
    }

    // Call the function-under-test
    double result = LogL16toY(input_value);

    // Use the result in some way to avoid compiler optimizations removing the call
    volatile double use_result = result;

    return 0;
}