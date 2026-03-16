#include <cstdint>
#include <cstddef>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    // Ensure the input size is at least the size of a uint16_t
    if (size < sizeof(uint16_t)) {
        return 0;
    }

    // Cast the input data to a uint16_t pointer
    uint16_t *shortData = (uint16_t *)data;

    // Call the function-under-test
    TIFFSwabShort(shortData);

    return 0;
}