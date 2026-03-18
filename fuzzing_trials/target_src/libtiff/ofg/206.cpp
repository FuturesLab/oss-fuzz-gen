#include <cstdint>
#include <cstddef>
#include <cstring> // Include this for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_206(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to form a uint32_t
    }

    // Copy the first 4 bytes into a uint32_t variable
    uint32_t value;
    memcpy(&value, data, sizeof(uint32_t));

    // Call the function-under-test
    TIFFSwabLong(&value);

    return 0;
}