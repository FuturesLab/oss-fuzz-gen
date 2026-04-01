#include <cstdint>
#include <cstddef>
#include <cstring>  // Include this header for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_231(const uint8_t *data, size_t size) {
    // Ensure the size is at least 8 bytes to form a valid uint64_t
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Cast the input data to a uint64_t pointer
    uint64_t value;
    memcpy(&value, data, sizeof(uint64_t));

    // Call the function-under-test
    TIFFSwabLong8(&value);

    return 0;
}