#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h> // Include for mkstemp, write, and close
#include <stdlib.h> // Include for remove

extern "C" {
    // Wrap the C library functions in extern "C"
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_302(const uint8_t *data, size_t size) {
    if (size == 0) return 0;

    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) return 0;

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        remove(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFForceStrileArrayWriting(tiff);

    // Close the TIFF file and remove the temporary file
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}