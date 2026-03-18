#include <cstdint>
#include <cmath>
#include <cstddef> // Include for size_t

// Function-under-test declaration
extern "C" {
    double LogL10toY(int input);
}

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *data, std::size_t size) {
    // Ensure the size is sufficient to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data
    int input = 0;
    for (std::size_t i = 0; i < sizeof(int); ++i) {
        input |= (data[i] << (i * 8));
    }

    // Call the function-under-test
    double result = LogL10toY(input);

    // Use the result in some way to prevent compiler optimizations
    volatile double use_result = result;
    (void)use_result;

    return 0;
}