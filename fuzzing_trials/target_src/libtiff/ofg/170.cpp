#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_170(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
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

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file using libtiff
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff) {
        // Define a non-zero tile index
        uint32_t tileIndex = 1;

        // Call the function-under-test
        uint64_t tileSize = TIFFVTileSize64(tiff, tileIndex);

        // Use the tileSize in some way to avoid compiler optimization issues
        if (tileSize > 0) {
            // Do something with tileSize if needed
        }

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}