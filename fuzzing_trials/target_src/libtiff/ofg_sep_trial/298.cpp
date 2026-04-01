#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for 'close' and 'mkstemp'

extern "C" {
    // Wrap the C library headers and functions in extern "C"
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_298(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Could not create a temp file
    }

    // Write the fuzz data to the file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }

    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Use a non-zero offset for toff_t
    toff_t offset = 8; // Arbitrary non-zero value

    // Call the function-under-test
    TIFFReadEXIFDirectory(tiff, offset);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}