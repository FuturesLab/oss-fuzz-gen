extern "C" {
    #include <tiffio.h>
    #include <unistd.h>  // For close, write, and mkstemp
    #include <stdlib.h>  // For mkstemp
}

#include <cstdint>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        remove(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    uint64_t tileSize = TIFFTileSize64(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}