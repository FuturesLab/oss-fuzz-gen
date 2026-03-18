#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Initialize a uint32_t variable from the input data
    uint32_t value;
    // Copy the first 4 bytes from data into value
    value = *(reinterpret_cast<const uint32_t*>(data));

    // Call the function-under-test
    TIFFSwabLong(&value);

    return 0;
}