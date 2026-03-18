#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include this header for the 'close' function
#include <tiffio.h>

extern "C" {
    int TIFFReadEXIFDirectory(TIFF *, toff_t);
}

extern "C" int LLVMFuzzerTestOneInput_299(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Set a non-zero offset for the EXIF directory
    toff_t offset = 8; // Arbitrary non-zero value for testing

    // Call the function-under-test
    TIFFReadEXIFDirectory(tiff, offset);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}