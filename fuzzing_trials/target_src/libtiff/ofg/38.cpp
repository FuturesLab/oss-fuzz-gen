#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h> // For mkstemp and close
#include <stdlib.h> // For mkstemp and remove
#include <tiffio.h>

extern "C" {
    // Function signature to be fuzzed
    int TIFFRGBAImageBegin(TIFFRGBAImage *, TIFF *, int, char *);
}

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to create a valid TIFF image
    if (size < 4) {
        return 0;
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Initialize TIFFRGBAImage
    TIFFRGBAImage img;
    char emsg[1024];
    int stopOnError = 0; // Example value, can be varied

    // Call the function-under-test
    TIFFRGBAImageBegin(&img, tiff, stopOnError, emsg);

    // Cleanup
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}