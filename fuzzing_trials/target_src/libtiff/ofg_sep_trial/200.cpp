#include <cstdint>
#include <cstddef>
#include <tiffio.h>  // Include the TIFF library header

extern "C" int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form a uint32_t
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Cast the input data to a uint32_t pointer
    uint32_t *longValue = (uint32_t *)data;

    // Call the function-under-test
    TIFFSwabLong(longValue);

    return 0;
}