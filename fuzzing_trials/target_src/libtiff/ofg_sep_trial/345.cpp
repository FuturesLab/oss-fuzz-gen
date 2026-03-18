#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>  // Include for close()

extern "C" int LLVMFuzzerTestOneInput_345(const uint8_t *data, size_t size) {
    TIFF *tiff;
    uint32_t tileIndex = 0;
    tmsize_t dataSize = static_cast<tmsize_t>(size);

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzz-tiffXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the TIFF file
    tiff = TIFFOpen(tmpl, "w+");
    if (!tiff) {
        close(fd);
        return 0;
    }

    // Ensure the data pointer is not null and size is valid
    if (data != nullptr && size > 0) {
        // Call the function-under-test
        TIFFWriteRawTile(tiff, tileIndex, (void *)data, dataSize);
    }

    // Clean up
    TIFFClose(tiff);
    close(fd);
    remove(tmpl);

    return 0;
}