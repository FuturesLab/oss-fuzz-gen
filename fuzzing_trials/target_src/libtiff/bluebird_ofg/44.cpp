#include "cstdint"
#include <cstddef>
#include <cstdio>

// Assuming the function LogLuv32toXYZ is defined in a C library
extern "C" {
    void LogLuv32toXYZ(uint32_t value, float *output);
}

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to extract a uint32_t value
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Extract a uint32_t value from the input data
    uint32_t value = 0;
    for (size_t i = 0; i < sizeof(uint32_t); ++i) {
        value |= static_cast<uint32_t>(data[i]) << (i * 8);
    }

    // Initialize a float array to store the output
    float output[3] = {0.0f, 0.0f, 0.0f};

    // Call the function-under-test
    LogLuv32toXYZ(value, output);

    // Optionally, print the output for debugging purposes
    printf("Output: [%f, %f, %f]\n", output[0], output[1], output[2]);

    return 0;
}