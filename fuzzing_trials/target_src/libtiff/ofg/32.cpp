#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h> // For close()
#include <cstring>  // For memcpy()

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t tile_index = 0;
    void *buffer;
    tmsize_t buffer_size = static_cast<tmsize_t>(size);

    // Create a temporary file to store TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the TIFF file for writing
    tiff = TIFFOpen(tmpl, "w");
    if (tiff == NULL) {
        close(fd);
        return 0;
    }

    // Initialize buffer with data
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        TIFFClose(tiff);
        close(fd);
        return 0;
    }
    memcpy(buffer, data, size);

    // Call the function-under-test
    TIFFWriteEncodedTile(tiff, tile_index, buffer, buffer_size);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    close(fd);
    remove(tmpl);

    return 0;
}