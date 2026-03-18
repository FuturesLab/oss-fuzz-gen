#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t strip = 0;
    void *buf = nullptr;
    tmsize_t bufsize = 0;

    // Create a temporary TIFF file to work with
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
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
    tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Allocate a buffer to read the strip data
    bufsize = TIFFStripSize(tiff);
    buf = malloc(bufsize);
    if (!buf) {
        TIFFClose(tiff);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFReadRawStrip(tiff, strip, buf, bufsize);

    // Clean up
    free(buf);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}