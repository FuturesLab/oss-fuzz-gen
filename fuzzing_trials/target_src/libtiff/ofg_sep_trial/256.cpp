#include <cstdint>
#include <cstddef>

extern "C" {
    // Declaration of the function-under-test
    void LogLuv32toXYZ(uint32_t input, float *output);
}

extern "C" int LLVMFuzzerTestOneInput_256(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Extract a uint32_t value from the input data
    uint32_t input = *(reinterpret_cast<const uint32_t*>(data));

    // Initialize a float array to store the output
    float output[3] = {0.0f, 0.0f, 0.0f};

    // Call the function-under-test
    LogLuv32toXYZ(input, output);

    return 0;
}