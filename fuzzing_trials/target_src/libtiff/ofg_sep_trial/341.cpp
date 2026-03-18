#include <cstdint>
#include <cstddef>

extern "C" {
    // Function-under-test declaration
    uint32_t LogLuv32fromXYZ(float *xyz, int illuminant);
}

extern "C" int LLVMFuzzerTestOneInput_341(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create at least one float and an int
    if (size < sizeof(float) + sizeof(int)) {
        return 0;
    }

    // Initialize the float array with the first part of the data
    float xyz[3];
    for (size_t i = 0; i < 3; ++i) {
        if (size < (i + 1) * sizeof(float)) {
            return 0;  // Not enough data for a full float
        }
        xyz[i] = *reinterpret_cast<const float*>(data + i * sizeof(float));
    }

    // Initialize the illuminant with the remaining part of the data
    int illuminant = *reinterpret_cast<const int*>(data + 3 * sizeof(float));

    // Call the function-under-test
    uint32_t result = LogLuv32fromXYZ(xyz, illuminant);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}