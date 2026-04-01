#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include for write and close
#include <fcntl.h>  // Include for mkstemp

extern "C" {
    // Ensure all C headers and functions are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_218(const uint8_t *data, size_t size) {
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
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (tiff == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFRewriteDirectory(tiff);

    // Close the TIFF file and remove the temporary file
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}