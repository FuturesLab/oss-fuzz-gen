#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    // Ensure the input size is at least the size of a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Create a uint32_t variable and initialize it with the first 4 bytes of data
    uint32_t value;
    value = *reinterpret_cast<const uint32_t*>(data);

    // Call the function-under-test
    TIFFSwabLong(&value);

    return 0;
}