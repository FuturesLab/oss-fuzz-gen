#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
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
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif) {
        // Prepare parameters for TIFFGetFieldDefaulted
        uint32_t tag = 0; // Example tag, could be any valid tag value
        void *value = malloc(256); // Allocate memory for the value

        // Call the function-under-test
        TIFFGetFieldDefaulted(tif, tag, value);

        // Clean up
        free(value);
        TIFFClose(tif);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}