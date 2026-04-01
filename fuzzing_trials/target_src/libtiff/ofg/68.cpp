#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <unistd.h>  // Include for close, write, and unlink
#include <sys/types.h> // Include for ssize_t
#include <fcntl.h> // Include for mkstemp

extern "C" {
    // All C headers and functions must be wrapped in extern "C"
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *data, size_t size) {
    // Create a temporary file to store the fuzz data
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
    close(fd);

    // Open the TIFF file using the temporary file
    TIFF* tif = TIFFOpen(tmpl, "r");
    if (tif != nullptr) {
        // Call the function-under-test
        int mode = TIFFGetMode(tif);

        // Close the TIFF file
        TIFFClose(tif);
    }

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}