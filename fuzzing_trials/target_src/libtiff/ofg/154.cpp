#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include this header for the 'close' function
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
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

    // Define a tag to retrieve
    uint32_t tag = TIFFTAG_IMAGEWIDTH;  // Initialize with a valid tag value

    // Define a buffer to hold the field value
    uint32_t field_value;  // Allocate memory for the field value

    // Call the function-under-test
    TIFFGetField(tiff, tag, &field_value);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}