#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_331(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to extract a uint16_t
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Extract a uint16_t value from the input data
    uint16_t codec = *(reinterpret_cast<const uint16_t*>(data));

    // Call the function-under-test
    int result = TIFFIsCODECConfigured(codec);

    // Optionally, you can use the result to perform further checks or logging
    // For this fuzzing harness, we simply return 0
    (void)result; // Suppress unused variable warning

    return 0;
}