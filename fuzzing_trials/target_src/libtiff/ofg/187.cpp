#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_187(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0;  // Not enough data to extract a uint32_t
    }

    // Create a temporary file to store the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;  // Could not create temporary file
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;  // Failed to write all data
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        return 0;  // Failed to open TIFF file
    }

    // Extract a uint32_t value from the input data
    uint32_t strileIndex;
    memcpy(&strileIndex, data, sizeof(uint32_t));

    // Prepare an error code variable
    int errorCode = 0;

    // Call the function-under-test
    uint64_t offset = TIFFGetStrileOffsetWithErr(tiff, strileIndex, &errorCode);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}