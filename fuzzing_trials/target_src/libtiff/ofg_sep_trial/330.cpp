#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_330(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract a uint16_t value
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Extract a uint16_t value from the input data
    uint16_t codec = *(reinterpret_cast<const uint16_t*>(data));

    // Call the function-under-test
    int result = TIFFIsCODECConfigured(codec);

    // Use the result in some way (e.g., print, log, or check)
    // In this case, we just return 0 to indicate the function was called
    (void)result; // Suppress unused variable warning

    return 0;
}