#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include this header for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_316(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to proceed
    }

    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the data to the temporary file
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

    // Allocate buffer for scanline
    tsize_t scanlineSize = TIFFScanlineSize(tiff);
    void *buf = malloc(scanlineSize);
    if (!buf) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadScanline
    uint32_t row = 0; // Set to 0 for simplicity, you can vary this
    uint16_t sample = 0; // Set to 0 for simplicity, you can vary this

    // Call the function under test
    TIFFReadScanline(tiff, buf, row, sample);

    // Clean up
    free(buf);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}