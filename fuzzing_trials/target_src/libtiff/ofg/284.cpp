#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>
#include <unistd.h>  // Include for close() and unlink()
#include <cstring>   // Include for memcpy()

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_284(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t strip = 0;
    void *buffer = nullptr;
    tmsize_t bufferSize = static_cast<tmsize_t>(size);

    // Create a temporary file to act as a TIFF image
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "w+");
    if (tiff == nullptr) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Ensure the buffer is not NULL
    if (size > 0) {
        buffer = malloc(size);
        if (buffer == nullptr) {
            TIFFClose(tiff);
            close(fd);
            unlink(tmpl);
            return 0;
        }
        memcpy(buffer, data, size);
    }

    // Call the function-under-test
    TIFFWriteRawStrip(tiff, strip, buffer, bufferSize);

    // Clean up
    if (buffer != nullptr) {
        free(buffer);
    }
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl);

    return 0;
}