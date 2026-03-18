#include <cstdint>
#include <cstdio>
#include <cstdlib>  // Include for mkstemp and remove
#include <unistd.h> // Include for close
#include <tiffio.h>

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // Not enough data to proceed
    }

    // Create a temporary TIFF file in memory
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0; // Failed to open file descriptor
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0; // Failed to open TIFF
    }

    // Initialize width and height
    uint32_t width = 0;
    uint32_t height = 0;

    // Call the function-under-test
    TIFFDefaultTileSize(tiff, &width, &height);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}