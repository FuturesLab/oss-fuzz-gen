#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>  // Include for 'write', 'close', and 'unlink' functions
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff != nullptr) {
        // Call the function-under-test
        tmsize_t scanlineSize = TIFFScanlineSize(tiff);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Clean up the temporary file
    unlink(tmpl);

    return 0;
}