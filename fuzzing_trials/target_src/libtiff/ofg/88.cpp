#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy
#include <unistd.h> // Include for write and close
#include <tiffio.h>

extern "C" {
    #include <tiffio.h> // Ensure TIFF functions are wrapped in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *data, size_t size) {
    // Create a temporary file name
    char filename[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    TIFF *tiff = TIFFOpen(filename, "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Allocate a buffer for TIFFReadBufferSetup
    void *buffer = malloc(size);
    if (buffer == nullptr) {
        TIFFClose(tiff);
        return 0;
    }

    // Copy the input data into the buffer
    memcpy(buffer, data, size);

    // Call the function-under-test
    TIFFReadBufferSetup(tiff, buffer, static_cast<tmsize_t>(size));

    // Clean up
    free(buffer);
    TIFFClose(tiff);

    // Remove the temporary file
    remove(filename);

    return 0;
}