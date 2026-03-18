#include <cstdint>
#include <cstddef>

extern "C" {
    // Assume the function is defined in an external C library
    uint32_t LogLuv24fromXYZ(float *xyz, int illuminant);
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for at least 3 floats
    if (size < sizeof(float) * 3) {
        return 0;
    }

    // Prepare the float array for XYZ values
    float xyz[3];
    // Copy data into the float array, ensuring proper alignment
    for (size_t i = 0; i < 3; ++i) {
        xyz[i] = reinterpret_cast<const float*>(data)[i];
    }

    // Choose an illuminant value, for fuzzing purposes, we can use a fixed value
    int illuminant = 1;

    // Call the function-under-test
    uint32_t result = LogLuv24fromXYZ(xyz, illuminant);

    // Optionally, use the result in some way to prevent optimizations from removing the call
    (void)result;

    return 0;
}