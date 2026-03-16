#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include this header for 'close' and 'write' functions

extern "C" int LLVMFuzzerTestOneInput_240(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {  // Cast size to ssize_t for comparison
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file with libtiff
    TIFF* tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    int result = TIFFIsBigTIFF(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}