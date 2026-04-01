#include <cstdint>
#include <cstdlib>
#include <cstring> // Added for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_174(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t) + sizeof(tmsize_t)) {
        // Not enough data to initialize all parameters
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzz.tiff", "w");
    if (tiff == NULL) {
        return 0;
    }

    // Initialize other parameters
    uint32_t strip = 0; // Example value, can be varied
    void *buf = malloc(size);
    if (buf == NULL) {
        TIFFClose(tiff);
        return 0;
    }
    tmsize_t bufsize = static_cast<tmsize_t>(size);

    // Copy data to buffer
    memcpy(buf, data, size);

    // Call the function-under-test
    tmsize_t result = TIFFReadRawStrip(tiff, strip, buf, bufsize);

    // Clean up
    free(buf);
    TIFFClose(tiff);

    return 0;
}