#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_147(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Reset the file descriptor to the beginning of the file
    lseek(fd, 0, SEEK_SET);

    // Define and initialize the parameters for TIFFFdOpenExt
    const char *mode = "r";  // Open in read mode
    TIFFOpenOptions *options = nullptr;  // No additional options

    // Call the function-under-test
    TIFF *tiff = TIFFFdOpenExt(fd, tmpl, mode, options);

    // Clean up
    if (tiff != nullptr) {
        TIFFClose(tiff);
    }
    close(fd);
    unlink(tmpl);

    return 0;
}