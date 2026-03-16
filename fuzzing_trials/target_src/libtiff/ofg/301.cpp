#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib> // Include this header for mkstemp

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_301(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
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

    // Close the file descriptor as TIFFOpen will open it again
    close(fd);

    // Open the temporary file with libtiff
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Call the function-under-test
    TIFFForceStrileArrayWriting(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}