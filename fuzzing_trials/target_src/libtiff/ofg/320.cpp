#include <tiffio.h>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_320(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file with TIFFOpen
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Perform operations on the TIFF file if needed
        TIFFClose(tiff);
    }

    // Clean up: remove the temporary file
    unlink(tmpl);

    return 0;
}