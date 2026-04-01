#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include for close and write
#include <fcntl.h>   // Include for mkstemp

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a TIFF file
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif != NULL) {
        // Call the function-under-test
        tmsize_t tileSize = TIFFTileSize(tif);

        // Use the tileSize for any further processing if needed
        (void)tileSize;

        // Close the TIFF file
        TIFFClose(tif);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}