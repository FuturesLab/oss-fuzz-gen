#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h> // Include for close() and remove()

extern "C" int LLVMFuzzerTestOneInput_271(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data to
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadEncodedStrip
    uint32_t strip = 0; // Assuming we want to read the first strip
    tmsize_t buffer_size = 1024; // Arbitrary buffer size
    void *buffer = malloc(buffer_size);
    if (!buffer) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadEncodedStrip(tiff, strip, buffer, buffer_size);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}