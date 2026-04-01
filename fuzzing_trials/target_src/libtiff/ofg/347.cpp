#include <cstdint>
#include <cstddef>

// Assume this is the function-under-test provided in some library
extern "C" void LogLuv24toXYZ(uint32_t input, float *output);

extern "C" int LLVMFuzzerTestOneInput_347(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Extract a uint32_t from the input data
    uint32_t input = 0;
    for (size_t i = 0; i < sizeof(uint32_t); ++i) {
        input |= static_cast<uint32_t>(data[i]) << (i * 8);
    }

    // Initialize a float array to hold the output
    float output[3] = {0.0f, 0.0f, 0.0f};

    // Call the function-under-test
    LogLuv24toXYZ(input, output);

    return 0;
}