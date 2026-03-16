#include <stdint.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_331(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract a uint16_t value
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Extract a uint16_t value from the input data
    uint16_t codec = *(reinterpret_cast<const uint16_t*>(data));

    // Call the function-under-test
    int result = TIFFIsCODECConfigured(codec);

    // Use the result in some way to prevent compiler optimizations from removing the call
    (void)result;

    return 0;
}