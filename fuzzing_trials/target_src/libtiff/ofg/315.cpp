#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h> // Include for close, write, and unlink
#include <tiffio.h>

extern "C" {
    #include <tiffio.h> // Ensure TIFF functions are properly linked
}

extern "C" int LLVMFuzzerTestOneInput_315(const uint8_t *data, size_t size) {
    TIFF *tiff;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);

    if (fd < 0) {
        return 0;
    }

    // Write fuzz data to the temporary file
    if (write(fd, data, size) != static_cast<ssize_t>(size)) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the TIFF file from the temporary file
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        return 0;
    }

    // Attempt to get strile byte count with a few different indices
    uint32_t indices[] = {0, 1, 2, 3, 4};
    for (uint32_t index : indices) {
        TIFFGetStrileByteCount(tiff, index);
    }

    // Close the TIFF file
    TIFFClose(tiff);

    // Remove the temporary file
    unlink(tmpl);

    return 0;
}