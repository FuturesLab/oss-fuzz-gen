#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_306(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
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

    // Initialize parameters for TIFFReadRGBAStripExt
    uint32_t strip = 0;  // Assuming the first strip
    uint32_t buffer[256];  // Arbitrary buffer size, adjust as needed
    int stopOnError = 1;  // Example value

    // Call the function-under-test
    TIFFReadRGBAStripExt(tiff, strip, buffer, stopOnError);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}