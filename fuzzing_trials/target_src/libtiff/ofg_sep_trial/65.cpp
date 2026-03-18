#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include this header for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    // Create a temporary file to act as a TIFF file
    char tmpl[] = "/tmp/fuzz_tiffXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write the fuzz data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as a TIFF image
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Initialize a non-NULL uint64_t pointer
    uint64_t customDirOffset = 0;
    uint64_t *offsetPtr = &customDirOffset;

    // Call the function-under-test
    TIFFWriteCustomDirectory(tiff, offsetPtr);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}