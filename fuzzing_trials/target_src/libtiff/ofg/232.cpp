#include <cstdint>
#include <cstddef>
#include <cstring>  // Include the C string library for memcpy

extern "C" {
    #include <tiffio.h>  // Ensure the libtiff library is included
}

extern "C" int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    // Ensure there's enough data to form a uint64_t
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Initialize a uint64_t variable with data from the input
    uint64_t value;
    // Copy the first 8 bytes from the input data to the value
    memcpy(&value, data, sizeof(uint64_t));

    // Call the function-under-test
    TIFFSwabLong8(&value);

    return 0;
}