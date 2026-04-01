#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_283(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the test
    if (size < sizeof(uint32_t) + sizeof(tmsize_t)) {
        return 0;
    }

    // Initialize necessary variables
    TIFF *tif = nullptr;
    uint32_t strip = 0;
    void *buffer = nullptr;
    tmsize_t bufferSize = 0;

    // Create a temporary TIFF file in memory
    tif = TIFFOpen("temp.tiff", "w");
    if (!tif) {
        return 0;
    }

    // Extract strip number and buffer size from the input data
    memcpy(&strip, data, sizeof(uint32_t));
    memcpy(&bufferSize, data + sizeof(uint32_t), sizeof(tmsize_t));

    // Ensure bufferSize is not negative and does not exceed the remaining data
    if (bufferSize < 0 || bufferSize > size - sizeof(uint32_t) - sizeof(tmsize_t)) {
        TIFFClose(tif);
        return 0;
    }

    // Allocate buffer and copy the data
    buffer = malloc(bufferSize);
    if (buffer == nullptr) {
        TIFFClose(tif);
        return 0;
    }
    memcpy(buffer, data + sizeof(uint32_t) + sizeof(tmsize_t), bufferSize);

    // Call the function-under-test
    TIFFWriteRawStrip(tif, strip, buffer, bufferSize);

    // Clean up
    free(buffer);
    TIFFClose(tif);

    return 0;
}