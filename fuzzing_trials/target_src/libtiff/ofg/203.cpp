#include <cstdint>
#include <cstdio>
#include <unistd.h>  // Include for close, mkstemp, and write
#include <sys/types.h>  // Include for ssize_t
#include <cstdlib>  // Include for remove

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t tag = 0;
    TIFFDataType dataType = TIFF_NOTYPE;

    // Create a temporary file to store the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != ssize_t(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file as a TIFF file
    tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Fuzz the TIFFFindField function
    const TIFFField *field = TIFFFindField(tiff, tag, dataType);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}