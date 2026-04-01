#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for close()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    if (size < 1) return 0; // Ensure there's at least one byte for the filename

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Write the data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file using TIFF library
    TIFF *tif = TIFFOpen(tmpl, "r");
    if (tif) {
        // Use the first byte of data as the toff_t offset
        toff_t offset = static_cast<toff_t>(data[0]);

        // Call the function-under-test
        TIFFReadGPSDirectory(tif, offset);

        // Close the TIFF file
        TIFFClose(tif);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}