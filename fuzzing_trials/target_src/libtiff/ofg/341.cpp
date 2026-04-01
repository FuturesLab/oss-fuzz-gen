#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" {
    // Declare the function to be fuzzed
    uint32_t LogLuv32fromXYZ(float *xyz, int illuminant);
}

extern "C" int LLVMFuzzerTestOneInput_341(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for at least one float and one int
    if (size < sizeof(float) + sizeof(int)) {
        return 0;
    }

    // Allocate memory for the float array
    float xyz[3] = {0.0f, 0.0f, 0.0f};

    // Copy data into the float array, ensuring we don't exceed the input size
    std::memcpy(xyz, data, sizeof(float) * 3);

    // Extract the int value for illuminant from the remaining data
    int illuminant = 0;
    if (size >= sizeof(float) * 3 + sizeof(int)) {
        std::memcpy(&illuminant, data + sizeof(float) * 3, sizeof(int));
    }

    // Call the function under test
    uint32_t result = LogLuv32fromXYZ(xyz, illuminant);

    // Optionally use the result to prevent compiler optimizations
    (void)result;

    return 0;
}