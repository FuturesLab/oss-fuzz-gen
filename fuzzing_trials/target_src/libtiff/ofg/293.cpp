#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h> // Include this for the 'close' function

extern "C" {
    #include <tiffio.h> // Ensure all C headers are wrapped with extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_293(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write the fuzz data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFComputeTile
    uint32_t x = size > 0 ? data[0] : 0;
    uint32_t y = size > 1 ? data[1] : 0;
    uint32_t z = size > 2 ? data[2] : 0;
    uint16_t sample = size > 3 ? data[3] : 0;

    // Call the function-under-test
    TIFFComputeTile(tiff, x, y, z, sample);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}