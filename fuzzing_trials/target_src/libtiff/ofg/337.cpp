#include <cstdint>
#include <cstdlib>
#include <unistd.h>   // For close
#include <cstring>    // For memcpy

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_337(const uint8_t *data, size_t size) {
    TIFF *tiff;
    void *buffer;
    tmsize_t bufferSize;

    // Initialize TIFF structure using a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    tiff = TIFFFdOpen(fd, "w", "r");
    if (tiff == nullptr) {
        close(fd);
        return 0;
    }

    // Ensure buffer is not NULL and has a reasonable size
    bufferSize = (tmsize_t)size;
    buffer = malloc(bufferSize);
    if (buffer == nullptr) {
        TIFFClose(tiff);
        close(fd);
        return 0;
    }

    // Copy data to buffer
    memcpy(buffer, data, bufferSize);

    // Call the function-under-test
    TIFFWriteBufferSetup(tiff, buffer, bufferSize);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    close(fd);

    return 0;
}