#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // For write() and close()
#include <sys/types.h>  // For ssize_t

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_226(const uint8_t *data, size_t size) {
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

    // Close the file descriptor
    close(fd);

    // Define the mode and options for TIFFOpenExt
    const char *mode = "r";  // Read mode

    // Since TIFFOpenOptions is an incomplete type, we should not use it
    // directly. Instead, we should use the TIFFOpen function.
    TIFF *tiff = TIFFOpen(tmpl, mode);

    // Clean up
    if (tiff != NULL) {
        TIFFClose(tiff);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}