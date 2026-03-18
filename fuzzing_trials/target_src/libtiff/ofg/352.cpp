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

extern "C" int LLVMFuzzerTestOneInput_352(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t stripIndex = 0;

    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        remove(tmpl);
        return 0;
    }

    // Open the temporary file as a TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        close(fd);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    tmsize_t result = TIFFRawStripSize(tiff, stripIndex);

    // Clean up
    TIFFClose(tiff);
    close(fd);
    remove(tmpl);

    return 0;
}