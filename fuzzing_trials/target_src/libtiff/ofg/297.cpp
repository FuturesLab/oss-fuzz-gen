#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include this header for the 'close' function

extern "C" {
    // Ensure all C headers and functions are wrapped in extern "C"
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_297(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "rm");
    if (tiff) {
        // Call the function-under-test
        toff_t offset = 0; // Set a default offset value
        TIFFReadEXIFDirectory(tiff, offset);
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}