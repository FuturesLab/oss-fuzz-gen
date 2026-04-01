#include <tiffio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include this for the close() function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    if (size < 1) return 0;  // Ensure there's at least some data

    // Create a temporary file to simulate a TIFF file input
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;  // If file creation fails, exit
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file using libtiff
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Initialize TIFFRGBAImage
    TIFFRGBAImage img;
    char emsg[1024] = {0};  // Error message buffer

    // Call the function-under-test
    int result = TIFFRGBAImageBegin(&img, tiff, 0, emsg);

    // Clean up
    TIFFRGBAImageEnd(&img);
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}