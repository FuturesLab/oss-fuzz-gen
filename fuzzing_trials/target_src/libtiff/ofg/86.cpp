#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    TIFF *tiff = TIFFOpen("dummy.tiff", "r");
    if (tiff == nullptr) {
        return 0; // Exit if TIFFOpen fails
    }

    // Allocate a buffer for reading
    void *buffer = malloc(size);
    if (buffer == nullptr) {
        TIFFClose(tiff);
        return 0; // Exit if memory allocation fails
    }

    // Copy the input data to the buffer
    memcpy(buffer, data, size);

    // Call the function-under-test
    TIFFReadBufferSetup(tiff, buffer, static_cast<tmsize_t>(size));

    // Clean up
    free(buffer);
    TIFFClose(tiff);

    return 0;
}