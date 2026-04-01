#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <tiffio.h>
#include <stdlib.h> // Include for mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to hold the TIFF data
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
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == NULL) {
        return 0;
    }

    // Call the function-under-test
    TIFFUnmapFileProc unmapFileProc = TIFFGetUnmapFileProc(tiff);

    // Perform any additional operations with unmapFileProc if needed
    // For this fuzzing harness, we just call the function

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}