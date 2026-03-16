#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for 'write' and 'close' functions
#include <sys/types.h> // Include for 'ssize_t'
#include <sys/stat.h>
#include <fcntl.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_317(const uint8_t *data, size_t size) {
    TIFF *tiff;
    void *buf;
    uint32_t row;
    uint16_t sample;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        return 0;
    }

    // Allocate buffer for a scanline
    buf = _TIFFmalloc(TIFFScanlineSize(tiff));
    if (!buf) {
        TIFFClose(tiff);
        return 0;
    }

    // Initialize row and sample
    row = 0;
    sample = 0;

    // Call the function-under-test
    TIFFReadScanline(tiff, buf, row, sample);

    // Clean up
    _TIFFfree(buf);
    TIFFClose(tiff);

    return 0;
}