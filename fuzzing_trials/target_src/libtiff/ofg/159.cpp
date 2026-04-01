#include <cstdint>
#include <cstdio>
#include <unistd.h> // Include for mkstemp, close, and write
#include <sys/types.h> // Include for ssize_t
#include <sys/stat.h> // Include for file mode constants
#include <fcntl.h> // Include for file control options
#include <cstdlib> // Include for remove

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_159(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t tag = 0;

    // Create a temporary file to hold the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        remove(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file with libtiff
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Use a non-zero tag value for testing
    tag = 1;

    // Call the function-under-test
    const TIFFField *field = TIFFFieldWithTag(tiff, tag);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}