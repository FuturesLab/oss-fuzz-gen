#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h> // For close()
#include <cstring> // For memcpy()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_329(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t strip = 0;
    void *buffer;
    tmsize_t bufferSize;

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "w");
    if (!tiff) {
        return 0;
    }

    // Initialize buffer
    bufferSize = static_cast<tmsize_t>(size);
    buffer = malloc(bufferSize);
    if (!buffer) {
        TIFFClose(tiff);
        return 0;
    }

    // Copy data to buffer
    memcpy(buffer, data, size);

    // Call the function-under-test
    TIFFWriteEncodedStrip(tiff, strip, buffer, bufferSize);

    // Cleanup
    free(buffer);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}