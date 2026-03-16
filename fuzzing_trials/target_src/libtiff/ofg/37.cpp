#include <tiffio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include this header for close, unlink, and write functions

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file using the TIFF library
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Prepare the TIFFRGBAImage structure
    TIFFRGBAImage img;
    char emsg[1024]; // Error message buffer

    // Call the function-under-test
    int result = TIFFRGBAImageBegin(&img, tiff, 0, emsg);

    // Cleanup
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}