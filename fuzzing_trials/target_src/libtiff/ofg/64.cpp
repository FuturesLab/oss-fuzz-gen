#include <cstdint>
#include <cstdlib>
#include <unistd.h>  // Include for close() and unlink()
#include <tiffio.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff;
    uint64_t dir_offset = 0;

    // Create a temporary file to act as a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Could not create a temporary file
    }

    // Open the temporary file as a TIFF file
    tiff = TIFFFdOpen(fd, tmpl, "w");
    if (!tiff) {
        close(fd);
        return 0; // Could not open the file as a TIFF
    }

    // Call the function-under-test
    TIFFWriteCustomDirectory(tiff, &dir_offset);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl);

    return 0;
}