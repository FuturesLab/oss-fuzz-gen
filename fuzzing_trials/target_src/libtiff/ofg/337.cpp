#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_337(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    void *buffer = nullptr;
    tmsize_t bufferSize = static_cast<tmsize_t>(size);

    // Ensure that the buffer is not NULL by allocating memory
    if (size > 0) {
        buffer = malloc(size);
        if (buffer == nullptr) {
            return 0; // Exit if memory allocation fails
        }
        // Copy data to the buffer
        memcpy(buffer, data, size);
    }

    // Open a TIFF file in memory for writing
    tiff = TIFFOpen("mem:", "w");
    if (tiff == nullptr) {
        free(buffer);
        return 0; // Exit if TIFFOpen fails
    }

    // Call the function-under-test
    TIFFWriteBufferSetup(tiff, buffer, bufferSize);

    // Clean up
    TIFFClose(tiff);
    free(buffer);

    return 0;
}