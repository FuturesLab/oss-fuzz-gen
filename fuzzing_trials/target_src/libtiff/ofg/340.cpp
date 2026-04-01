#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" {
    // Function-under-test declaration
    uint32_t LogLuv32fromXYZ(float *xyz, int colorspace);
}

extern "C" int LLVMFuzzerTestOneInput_340(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a float array
    if (size < 3 * sizeof(float)) {
        return 0;
    }

    // Create a float array from the input data
    float xyz[3];
    memcpy(xyz, data, 3 * sizeof(float));

    // Use a fixed value for colorspace for fuzzing
    int colorspace = 1;

    // Call the function-under-test
    uint32_t result = LogLuv32fromXYZ(xyz, colorspace);

    // Use the result in some way to avoid compiler optimizations
    volatile uint32_t use_result = result;
    (void)use_result;

    return 0;
}