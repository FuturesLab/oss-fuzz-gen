#include <cstdint>
#include <cstdio>
#include <cstdlib>  // For mkstemp
#include <unistd.h>  // For close, unlink, write

// Ensure all C headers and code are wrapped in extern "C" for C++ compatibility
extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_351(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t stripIndex = 0;

    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file as a TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    tmsize_t result = TIFFRawStripSize(tiff, stripIndex);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}