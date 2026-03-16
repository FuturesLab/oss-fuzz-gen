#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for 'close'
#include <tiffio.h>

extern "C" {
    #include <tiffio.h> // Ensure TIFF functions are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff) {
        // Use a non-zero toff_t value as input
        toff_t directoryOffset = 1;

        // Call the function-under-test
        TIFFReadGPSDirectory(tiff, directoryOffset);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}