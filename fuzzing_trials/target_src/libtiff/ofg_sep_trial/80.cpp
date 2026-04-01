#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != ssize_t(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Rewind the file descriptor to the start
    lseek(fd, 0, SEEK_SET);

    // Open the TIFF file using the temporary file
    TIFF *tiff = TIFFFdOpen(fd, tmpl, "r");
    if (tiff == NULL) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    tmsize_t stripSize = TIFFStripSize(tiff);

    // Print the strip size (optional, for debugging purposes)
    printf("TIFF Strip Size: %ld\n", (long)stripSize);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl);

    return 0;
}