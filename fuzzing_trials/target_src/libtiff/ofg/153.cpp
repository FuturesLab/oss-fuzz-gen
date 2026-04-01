#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for close() and write()
#include <fcntl.h>  // Include for mkstemp()

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_153(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a valid filename and mode
    if (size < 10) return 0;

    // Create a temporary file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFFdOpenExt
    const char *filename = tmpl;
    const char *mode = "r"; // Open in read mode
    TIFFOpenOptions *options = TIFFOpenOptionsAlloc();

    // Call the function-under-test
    TIFF *tiff = TIFFFdOpenExt(fd, filename, mode, options);

    // Cleanup
    if (tiff != nullptr) {
        TIFFClose(tiff);
    }
    TIFFOpenOptionsFree(options);
    close(fd);
    remove(tmpl);

    return 0;
}