#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_336(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a buffer
    if (size < 1) {
        return 0;
    }

    // Open a TIFF memory stream for writing
    TIFF *tiff = TIFFOpen("dummy.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Allocate a buffer for TIFFWriteBufferSetup
    void *buffer = malloc(size);
    if (buffer == nullptr) {
        TIFFClose(tiff);
        return 0;
    }

    // Copy data into the buffer
    memcpy(buffer, data, size);

    // Call the function under test
    TIFFWriteBufferSetup(tiff, buffer, static_cast<tmsize_t>(size));

    // Clean up
    free(buffer);
    TIFFClose(tiff);

    return 0;
}