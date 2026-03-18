#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // For close()
#include <string.h>  // For memcpy()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_202(const uint8_t *data, size_t size) {
    TIFF *tiff;
    void *buf;
    uint32_t row;
    uint16_t sample;

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "w");
    if (tiff == NULL) {
        return 0;
    }

    // Initialize buffer with non-NULL data
    buf = malloc(size > 0 ? size : 1);
    if (buf == NULL) {
        TIFFClose(tiff);
        return 0;
    }
    memcpy(buf, data, size > 0 ? size : 1);

    // Set row and sample to non-zero values
    row = size > 0 ? data[0] : 1;
    sample = size > 1 ? data[1] : 1;

    // Call the function-under-test
    TIFFWriteScanline(tiff, buf, row, sample);

    // Clean up
    free(buf);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}