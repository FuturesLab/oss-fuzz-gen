#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for close() and write() functions

extern "C" int LLVMFuzzerTestOneInput_156(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
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

    // Open the temporary file as a TIFF file
    TIFF* tiff = TIFFOpen(tmpl, "r+");
    if (tiff == nullptr) {
        close(fd);
        return 0;
    }

    // Call the function-under-test
    TIFFCreateEXIFDirectory(tiff);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    remove(tmpl);

    return 0;
}