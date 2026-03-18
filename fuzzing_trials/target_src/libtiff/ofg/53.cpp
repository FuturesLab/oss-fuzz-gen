#include <cstdint>
#include <cstddef>
#include <cstring> // Include this for std::memcpy
#include <tiffio.h>

extern "C" {
    #include <tiffio.h> // Ensure TIFF library functions are treated as C
}

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Ensure there is enough data for a uint16_t
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Initialize a uint16_t variable from the input data
    uint16_t value;
    std::memcpy(&value, data, sizeof(uint16_t));

    // Call the function-under-test
    TIFFSwabShort(&value);

    return 0;
}