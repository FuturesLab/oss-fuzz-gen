#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_284(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t strip = 0;
    void *buffer;
    tmsize_t bufferSize;

    // Ensure that the size is not zero to avoid null buffer
    if (size == 0) {
        return 0;
    }

    // Create a temporary TIFF file in memory
    tiff = TIFFOpen("temp.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Allocate buffer and copy data into it
    bufferSize = static_cast<tmsize_t>(size);
    buffer = malloc(bufferSize);
    if (buffer == nullptr) {
        TIFFClose(tiff);
        return 0;
    }
    memcpy(buffer, data, size);

    // Call the function-under-test
    TIFFWriteRawStrip(tiff, strip, buffer, bufferSize);

    // Clean up
    free(buffer);
    TIFFClose(tiff);

    return 0;
}