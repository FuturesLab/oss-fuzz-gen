#include <cstdint>
#include <cstdlib>
#include <unistd.h>  // Include for write and close functions
#include <cstdio>    // Include for remove function
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Create a temporary file to store the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r+");
    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    TIFFCreateEXIFDirectory(tiff);

    // Close the TIFF file
    TIFFClose(tiff);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}