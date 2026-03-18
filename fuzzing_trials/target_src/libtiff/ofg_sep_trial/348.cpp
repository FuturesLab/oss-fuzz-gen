#include <cstdint>
#include <cstddef>

extern "C" {
    void LogLuv24toXYZ(uint32_t input, float *output);
}

extern "C" int LLVMFuzzerTestOneInput_348(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to form a uint32_t
    }

    // Extract a uint32_t from the input data
    uint32_t input = 0;
    for (size_t i = 0; i < sizeof(uint32_t); ++i) {
        input |= static_cast<uint32_t>(data[i]) << (i * 8);
    }

    // Allocate memory for the float output
    float output[3] = {0.0f, 0.0f, 0.0f};

    // Call the function-under-test
    LogLuv24toXYZ(input, output);

    return 0;
}