#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for close function
#include <tiffio.h>

extern "C" {
    #include <unistd.h> // Ensure unistd.h is included within extern "C" for C compatibility
}

extern "C" int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    // Initialize variables
    TIFF *tiff;
    void *buf;
    uint32_t row;
    uint16_t sample;

    // Create a temporary file to use with TIFF
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write the input data to the file
    fwrite(data, 1, size, file);
    fflush(file);
    fseek(file, 0, SEEK_SET);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r+");
    if (!tiff) {
        fclose(file);
        remove(tmpl);
        return 0;
    }

    // Allocate a buffer for the scanline
    buf = malloc(TIFFScanlineSize(tiff));
    if (!buf) {
        TIFFClose(tiff);
        fclose(file);
        remove(tmpl);
        return 0;
    }

    // Set arbitrary non-zero values for row and sample
    row = 1;
    sample = 1;

    // Call the function-under-test
    TIFFWriteScanline(tiff, buf, row, sample);

    // Clean up
    free(buf);
    TIFFClose(tiff);
    fclose(file);
    remove(tmpl);

    return 0;
}