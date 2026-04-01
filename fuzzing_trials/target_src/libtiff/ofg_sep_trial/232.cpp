#include <cstdint>
#include <cstddef>
#include <cstring> // Include for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    // Ensure that the size is at least the size of a uint64_t
    if (size < sizeof(uint64_t)) {
        return 0;
    }

    // Initialize a uint64_t variable and copy data into it
    uint64_t value;
    std::memcpy(&value, data, sizeof(uint64_t));

    // Call the function-under-test
    TIFFSwabLong8(&value);

    return 0;
}