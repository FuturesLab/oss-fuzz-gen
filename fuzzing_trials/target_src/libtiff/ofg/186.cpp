#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include for close, unlink, and write

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_186(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Ensure there's enough data for the strile index
    }

    // Create a temporary file to hold the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0; // Failed to write all data
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0; // Failed to open TIFF file
    }

    // Extract a uint32_t value from the data for the strile index
    uint32_t strileIndex;
    memcpy(&strileIndex, data, sizeof(uint32_t));

    // Initialize an error variable
    int error = 0;

    // Call the function-under-test
    uint64_t offset = TIFFGetStrileOffsetWithErr(tiff, strileIndex, &error);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}