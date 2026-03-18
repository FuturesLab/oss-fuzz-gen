#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>  // For write and close functions
#include <sys/types.h> // For ssize_t
#include <sys/stat.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

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

    // Close the file descriptor so TIFFOpen can open it
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    tmsize_t scanlineSize = TIFFScanlineSize(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}