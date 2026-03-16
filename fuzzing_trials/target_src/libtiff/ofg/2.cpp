#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib> // Include this header for mkstemp

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    TIFF *tiff = nullptr;
    uint32_t rowsPerStrip = 1; // Initialize with a non-zero value

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    uint64_t stripSize = TIFFVStripSize64(tiff, rowsPerStrip);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}