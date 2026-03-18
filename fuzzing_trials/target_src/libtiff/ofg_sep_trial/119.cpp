#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include this header for the 'close' function

extern "C" {
    #include <tiffio.h>  // Wrap the libtiff header in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
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
        uint32_t tag = 0; // Initialize tag to a default value
        void *value = malloc(256); // Allocate memory for the value
        if (value) {
            // Call the function under test
            TIFFGetFieldDefaulted(tif, tag, value);
            free(value); // Free the allocated memory
        }
        TIFFClose(tif);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}