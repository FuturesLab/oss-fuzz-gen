#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include for close() and write()
#include <fcntl.h>  // Include for mkstemp()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_226(const uint8_t *data, size_t size) {
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

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tif = TIFFOpen(tmpl, "r+");
    if (tif == NULL) {
        // If TIFFOpen fails, clean up the temporary file
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFFlushData(tif);

    // Close the TIFF file
    TIFFClose(tif);

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}