extern "C" {
#include <tiffio.h>
#include <unistd.h> // For mkstemp, unlink, write, close
#include <fcntl.h>  // For open, O_RDWR
#include <sys/types.h> // For types like uint32_t
#include <sys/stat.h>  // For file status
#include <stdint.h>    // For uint8_t
#include <stdio.h>     // For snprintf
#include <stdlib.h>    // For mkstemp
}

extern "C" int LLVMFuzzerTestOneInput_296(const uint8_t *data, size_t size) {
    // Initialize variables
    TIFF *tiff = nullptr;
    uint32_t sampleValue = 1; // Initialize with a non-zero value

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Return if file creation fails
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl); // Ensure file is removed if writing fails
        return 0; // Return if writing fails
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl); // Ensure file is removed if TIFFOpen fails
        return 0; // Return if TIFFOpen fails
    }

    // Call the function-under-test
    tmsize_t tileSize = TIFFVTileSize(tiff, sampleValue);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl); // Remove the temporary file

    return 0;
}