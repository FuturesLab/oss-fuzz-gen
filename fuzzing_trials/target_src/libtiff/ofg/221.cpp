extern "C" {
#include <tiffio.h>
#include <unistd.h>  // Include for 'unlink' and 'close'
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_221(const uint8_t *data, size_t size) {
    // Ensure data is large enough to create a valid string
    if (size < 1) {
        return 0;
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the temporary file as a TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "w");
    if (!tiff) {
        close(fd);
        return 0;
    }

    // Set up a non-NULL string for the third parameter
    char description[256];
    size_t desc_len = (size < 255) ? size : 255;
    memcpy(description, data, desc_len);
    description[desc_len] = '\0';

    // Call the function-under-test
    int result = TIFFWriteCheck(tiff, 1, description);

    // Cleanup
    TIFFClose(tiff);
    close(fd);
    unlink(tmpl);

    return 0;
}