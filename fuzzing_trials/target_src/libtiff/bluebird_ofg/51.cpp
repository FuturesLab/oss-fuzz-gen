#include <stdint.h>
#include "cstdlib"
#include "cstring"
#include <unistd.h>  // Include for close, write, and unlink
#include <fcntl.h>   // Include for mkstemp

extern "C" {
    #include "tiffio.h"
    #include "/src/libtiff/libtiff/tiff.h"
}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for a minimal TIFF header
    if (size < 8) {
        return 0;
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        unlink(tmpl);
        return 0;
    }

    // Initialize the TIFFRGBAImage structure
    TIFFRGBAImage img;
    char emsg[1024];

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of TIFFRGBAImageBegin
    int result = TIFFRGBAImageBegin(&img, tiff, size, emsg);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}