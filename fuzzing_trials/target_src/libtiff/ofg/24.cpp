#include <cstdint>
#include <cstddef>
#include <cstring> // Include for std::memcpy

extern "C" {
    // Assume this is the function-under-test from an external C library
    uint32_t LogLuv24fromXYZ(float *xyz, int num);
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    if (size < sizeof(float) * 3) {
        return 0; // Not enough data to form a valid input
    }

    // Initialize the float array with the first three floats from the data
    float xyz[3];
    for (int i = 0; i < 3; ++i) {
        // Copy bytes into float
        uint32_t temp;
        std::memcpy(&temp, data + i * sizeof(float), sizeof(float));
        xyz[i] = *reinterpret_cast<float*>(&temp);
    }

    // Use the remaining data size as the integer parameter
    int num = static_cast<int>(size - sizeof(float) * 3);

    // Call the function-under-test
    uint32_t result = LogLuv24fromXYZ(xyz, num);

    // Optionally use the result to prevent compiler optimizations
    (void)result;

    return 0;
}