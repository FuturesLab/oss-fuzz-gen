#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_282(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t) * 3 + sizeof(uint16_t)) {
        return 0; // Not enough data to extract necessary parameters
    }

    // Create a temporary TIFF file for writing
    const char *filename = "/tmp/fuzz_tile.tiff";
    TIFF *tiff = TIFFOpen(filename, "w");
    if (!tiff) {
        return 0;
    }

    // Extract parameters from the input data
    uint32_t x = *(reinterpret_cast<const uint32_t*>(data));
    uint32_t y = *(reinterpret_cast<const uint32_t*>(data + sizeof(uint32_t)));
    uint32_t z = *(reinterpret_cast<const uint32_t*>(data + 2 * sizeof(uint32_t)));
    uint16_t sample = *(reinterpret_cast<const uint16_t*>(data + 3 * sizeof(uint32_t)));

    // The remaining data is used as the tile buffer
    void *buffer = nullptr;
    size_t buffer_size = size - (3 * sizeof(uint32_t) + sizeof(uint16_t));
    if (buffer_size > 0) {
        buffer = malloc(buffer_size);
        if (buffer) {
            memcpy(buffer, data + 3 * sizeof(uint32_t) + sizeof(uint16_t), buffer_size);
        }
    }

    // Call the function under test
    TIFFWriteTile(tiff, buffer, x, y, z, sample);

    // Clean up
    if (buffer) {
        free(buffer);
    }
    TIFFClose(tiff);

    return 0;
}