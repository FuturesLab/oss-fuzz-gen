#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" {
    // Assuming the function is declared in a C header file
    uint32_t LogLuv24fromXYZ(float *xyz, int param);
}

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract float values and an int
    if (size < sizeof(float) * 3 + sizeof(int)) {
        return 0;
    }

    // Declare and initialize the float array for XYZ values
    float xyz[3];
    std::memcpy(xyz, data, sizeof(float) * 3);

    // Extract the integer parameter
    int param;
    std::memcpy(&param, data + sizeof(float) * 3, sizeof(int));

    // Call the function-under-test
    uint32_t result = LogLuv24fromXYZ(xyz, param);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}