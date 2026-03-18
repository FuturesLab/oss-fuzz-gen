#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include this for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_336(const uint8_t *data, size_t size) {
    // Initialize variables
    TIFF *tiff = TIFFOpen("test.tiff", "w");
    void *buffer = nullptr;
    tmsize_t bufferSize = static_cast<tmsize_t>(size);

    // Ensure the TIFF object is not NULL
    if (tiff == nullptr) {
        return 0;
    }

    // Allocate a buffer with the given size
    if (size > 0) {
        buffer = malloc(size);
        if (buffer == nullptr) {
            TIFFClose(tiff);
            return 0;
        }
        // Copy data into the buffer
        memcpy(buffer, data, size);
    }

    // Call the function-under-test
    TIFFWriteBufferSetup(tiff, buffer, bufferSize);

    // Clean up
    if (buffer != nullptr) {
        free(buffer);
    }
    TIFFClose(tiff);

    return 0;
}