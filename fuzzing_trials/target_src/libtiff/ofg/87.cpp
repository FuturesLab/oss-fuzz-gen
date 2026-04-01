#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>  // Ensure TIFF functions are linked correctly
}

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a buffer
    if (size < 1) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("dummy.tiff", "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Allocate a buffer with the provided data
    void *buffer = malloc(size);
    if (buffer == nullptr) {
        TIFFClose(tiff);
        return 0;
    }

    // Copy data into the buffer
    memcpy(buffer, data, size);

    // Call the function-under-test
    TIFFReadBufferSetup(tiff, buffer, static_cast<tmsize_t>(size));

    // Clean up
    free(buffer);
    TIFFClose(tiff);

    return 0;
}