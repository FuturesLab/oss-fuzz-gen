#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>  // For close()
#include <cstring>   // For memcpy()

extern "C" int LLVMFuzzerTestOneInput_328(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t strip = 0;
    tmsize_t result;
    void *buffer;

    // Create a temporary file to write the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }

    // Initialize TIFF structure
    tiff = TIFFOpen(tmpl, "w");
    if (!tiff) {
        fclose(file);
        return 0;
    }

    // Allocate buffer for TIFF data
    buffer = malloc(size);
    if (!buffer) {
        TIFFClose(tiff);
        fclose(file);
        return 0;
    }

    // Copy data into buffer
    memcpy(buffer, data, size);

    // Call the function-under-test
    result = TIFFWriteEncodedStrip(tiff, strip, buffer, (tmsize_t)size);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    fclose(file);
    remove(tmpl);

    return 0;
}