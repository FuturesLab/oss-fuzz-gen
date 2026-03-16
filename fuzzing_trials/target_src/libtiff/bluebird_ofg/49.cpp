#include "tiffio.h"
#include "cstdint"
#include "cstdlib"
#include <cstdio>
#include <unistd.h> // Include for 'close' and 'unlink'

extern "C" {
    #include "tiffio.h"
}

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
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
        unlink(tmpl);
        return 0;
    }

    // Prepare buffer for reading
    tmsize_t bufferSize = 1024; // Arbitrary buffer size for testing
    void *buffer = malloc(bufferSize);
    if (!buffer) {
        TIFFClose(tiff);
        unlink(tmpl);
        return 0;
    }

    // Read the encoded tile
    uint32_t tileIndex = 0; // Start with the first tile for fuzzing
    tmsize_t bytesRead = TIFFReadEncodedTile(tiff, tileIndex, buffer, bufferSize);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}