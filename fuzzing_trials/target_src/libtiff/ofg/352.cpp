#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>  // For close, unlink, and write
#include <cstring>  // For memcpy

extern "C" int LLVMFuzzerTestOneInput_352(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Ensure there's enough data for the uint32_t parameter
    }

    // Create a temporary file to hold the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0; // Failed to write data to the file
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl); // Clean up the temporary file
        return 0; // Failed to open the TIFF file
    }

    // Extract a uint32_t value from the data for the second parameter
    uint32_t stripIndex;
    memcpy(&stripIndex, data, sizeof(uint32_t));

    // Call the function-under-test
    tmsize_t result = TIFFRawStripSize(tiff, stripIndex);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl); // Remove the temporary file

    return 0;
}