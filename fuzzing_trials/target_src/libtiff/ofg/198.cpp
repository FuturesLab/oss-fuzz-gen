#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Include this header for close() and write()

extern "C" int LLVMFuzzerTestOneInput_198(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Close the file descriptor to flush the data
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        return 0;
    }

    // Call the function-under-test
    TIFFCloseProc closeProc = TIFFGetCloseProc(tiff);

    // Use the retrieved TIFFCloseProc if needed
    if (closeProc != NULL) {
        // Example usage of closeProc, if applicable
        // closeProc(tiff);
    }

    // Close the TIFF file
    TIFFClose(tiff);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}