#include <cstdint>
#include <cstdio>
#include <unistd.h>   // For close, write, and mkstemp
#include <cstdlib>    // For remove

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t stripIndex = 0;

    // Create a temporary file to simulate a TIFF file
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
    close(fd);

    // Open the temporary file with libtiff
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    uint64_t stripSize = TIFFVStripSize64(tiff, stripIndex);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}