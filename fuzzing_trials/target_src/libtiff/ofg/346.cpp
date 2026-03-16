#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>
#include <unistd.h>  // For close
#include <cstring>   // For memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_346(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t tileIndex = 0;
    void *buffer;
    tmsize_t bufferSize;

    // Create a temporary file to use with TIFF
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb+");
    if (!file) {
        close(fd);
        return 0;
    }

    // Initialize TIFF structure
    tiff = TIFFOpen(tmpl, "w");
    if (!tiff) {
        fclose(file);
        return 0;
    }

    // Ensure the buffer is not NULL and has a valid size
    if (size > 0) {
        bufferSize = static_cast<tmsize_t>(size);
        buffer = malloc(bufferSize);
        if (buffer) {
            memcpy(buffer, data, size);

            // Call the function-under-test
            TIFFWriteRawTile(tiff, tileIndex, buffer, bufferSize);

            free(buffer);
        }
    }

    // Cleanup
    TIFFClose(tiff);
    fclose(file);
    remove(tmpl);

    return 0;
}