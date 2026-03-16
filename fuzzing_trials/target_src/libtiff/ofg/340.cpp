#include <cstdint>
#include <cstddef>
#include <cstring>

// Assume the function is defined in an external C library
extern "C" {
    uint32_t LogLuv32fromXYZ(float *, int);
}

extern "C" int LLVMFuzzerTestOneInput_340(const uint8_t *data, size_t size) {
    // Ensure there's enough data for at least one float and an int
    if (size < sizeof(float) + sizeof(int)) {
        return 0;
    }

    // Allocate memory for a float array
    float floatArray[3];
    std::memset(floatArray, 0, sizeof(floatArray));

    // Copy data to floatArray, ensuring we don't exceed the buffer size
    size_t floatArraySize = size / sizeof(float);
    if (floatArraySize > 3) {
        floatArraySize = 3;
    }
    std::memcpy(floatArray, data, floatArraySize * sizeof(float));

    // Extract an integer from the remaining data
    int someInt = 0;
    if (size >= sizeof(float) * 3 + sizeof(int)) {
        std::memcpy(&someInt, data + sizeof(float) * 3, sizeof(int));
    }

    // Call the function-under-test
    uint32_t result = LogLuv32fromXYZ(floatArray, someInt);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}