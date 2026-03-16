#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_229(const uint8_t *data, size_t size) {
    // Check if the size is sufficient for the parameters
    if (size < sizeof(uint32_t) + 2 * sizeof(tmsize_t)) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/dev/null", "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Extract parameters from data
    uint32_t read_offset = *(reinterpret_cast<const uint32_t *>(data));
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    tmsize_t buffer_size = *(reinterpret_cast<const tmsize_t *>(data));
    data += sizeof(tmsize_t);
    size -= sizeof(tmsize_t);

    tmsize_t output_size = *(reinterpret_cast<const tmsize_t *>(data));
    data += sizeof(tmsize_t);
    size -= sizeof(tmsize_t);

    // Ensure buffer sizes are within the remaining data size
    if (buffer_size > size || output_size > size) {
        TIFFClose(tiff);
        return 0;
    }

    // Allocate buffers
    void *buffer = malloc(buffer_size);
    void *output = malloc(output_size);

    if (buffer == nullptr || output == nullptr) {
        free(buffer);
        free(output);
        TIFFClose(tiff);
        return 0;
    }

    // Copy data into buffers
    memcpy(buffer, data, buffer_size);
    memcpy(output, data, output_size);

    // Call the function under test
    TIFFReadFromUserBuffer(tiff, read_offset, buffer, buffer_size, output, output_size);

    // Clean up
    free(buffer);
    free(output);
    TIFFClose(tiff);

    return 0;
}