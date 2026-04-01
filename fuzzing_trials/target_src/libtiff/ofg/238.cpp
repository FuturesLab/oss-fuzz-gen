#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include this header for close() and write() functions

extern "C" int LLVMFuzzerTestOneInput_238(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    TIFFFlush(tiff);

    // Close the TIFF file
    TIFFClose(tiff);

    // Remove the temporary file
    remove(tmpl);

    return 0;
}