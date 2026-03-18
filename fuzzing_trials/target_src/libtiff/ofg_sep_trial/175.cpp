#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <tiffio.h>

extern "C" {
    #include <stdlib.h> // Include for mkstemp

    // Function signature from the project
    uint64_t TIFFGetStrileOffset(TIFF *, uint32_t);
}

extern "C" int LLVMFuzzerTestOneInput_175(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        remove(tmpl);
        return 0;
    }

    // Use a non-zero, non-NULL strile index for testing
    uint32_t strileIndex = 1;

    // Call the function-under-test
    uint64_t offset = TIFFGetStrileOffset(tiff, strileIndex);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}