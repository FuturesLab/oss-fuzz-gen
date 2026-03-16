#include <cstdint>
#include <cstdio>
#include <unistd.h> // For close, write, and mkstemp
#include <cstdlib>  // For remove

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_258(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file using the temporary file
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif != nullptr) {
        // Call the function-under-test
        uint32_t numTiles = TIFFNumberOfTiles(tif);

        // Clean up by closing the TIFF file
        TIFFClose(tif);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}