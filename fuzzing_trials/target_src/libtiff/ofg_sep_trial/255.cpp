#include <cstdint>
#include <cstddef>

// Assume the function-under-test is declared in an external C library.
extern "C" {
    void LogLuv32toXYZ(uint32_t input, float *output);
}

extern "C" int LLVMFuzzerTestOneInput_255(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for a uint32_t.
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Extract a uint32_t from the input data.
    uint32_t input_value = 0;
    for (size_t i = 0; i < sizeof(uint32_t); ++i) {
        input_value |= static_cast<uint32_t>(data[i]) << (i * 8);
    }

    // Initialize the output float array.
    float output[3] = {0.0f, 0.0f, 0.0f};

    // Call the function-under-test.
    LogLuv32toXYZ(input_value, output);

    return 0;
}