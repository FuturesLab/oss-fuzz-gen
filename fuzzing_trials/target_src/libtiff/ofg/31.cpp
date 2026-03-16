#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>  // For close()
#include <cstring>   // For memcpy()

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to proceed with fuzzing
    if (size < sizeof(uint32_t) + sizeof(tmsize_t)) {
        return 0;
    }

    // Create a temporary file to act as a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "w");
    if (!tiff) {
        close(fd);
        return 0;
    }

    // Extract parameters from the input data
    uint32_t tileIndex = *(reinterpret_cast<const uint32_t*>(data));
    tmsize_t bufferSize = *(reinterpret_cast<const tmsize_t*>(data + sizeof(uint32_t)));

    // Ensure bufferSize does not exceed the remaining data size
    if (bufferSize > size - sizeof(uint32_t) - sizeof(tmsize_t)) {
        bufferSize = size - sizeof(uint32_t) - sizeof(tmsize_t);
    }

    // Allocate buffer for tile data
    void *buffer = malloc(bufferSize);
    if (!buffer) {
        TIFFClose(tiff);
        close(fd);
        return 0;
    }

    // Copy data into the buffer
    memcpy(buffer, data + sizeof(uint32_t) + sizeof(tmsize_t), bufferSize);

    // Call the function-under-test
    TIFFWriteEncodedTile(tiff, tileIndex, buffer, bufferSize);

    // Clean up
    free(buffer);
    TIFFClose(tiff);
    close(fd);
    remove(tmpl);

    return 0;
}