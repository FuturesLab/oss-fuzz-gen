#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Include for close, unlink, and write

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the TIFF file from the temporary file
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif != NULL) {
        // Call the function-under-test
        int result = TIFFIsUpSampled(tif);

        // Close the TIFF file
        TIFFClose(tif);
    }

    // Clean up the temporary file
    unlink(tmpl);

    return 0;
}