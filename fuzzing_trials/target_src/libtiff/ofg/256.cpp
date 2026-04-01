#include <tiffio.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_256(const uint8_t *data, size_t size) {
    TIFF *tiff = nullptr;
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
    uint16_t sample = 0;

    // Create a temporary file to hold the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file as a TIFF
    tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Fuzzing the TIFFCheckTile function
    TIFFCheckTile(tiff, x, y, z, sample);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}