#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_332(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract a uint16_t
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Extract a uint16_t value from the input data
    uint16_t codec = *(reinterpret_cast<const uint16_t*>(data));

    // Call the function-under-test
    int result = TIFFIsCODECConfigured(codec);

    return 0;
}