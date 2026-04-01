#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <unistd.h> // For close, unlink, and write

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl); // Clean up the temporary file
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl); // Clean up the temporary file
        return 0;
    }

    // Call the function-under-test
    tmsize_t stripSize = TIFFStripSize(tiff);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl); // Remove the temporary file

    return 0;
}