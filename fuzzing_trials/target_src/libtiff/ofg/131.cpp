#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>  // Include this header for the 'close' function

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Prepare parameters for TIFFReadRGBATileExt
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t raster[256]; // Example size, adjust as needed
    int stopOnError = 1;

    // Call the function-under-test
    TIFFReadRGBATileExt(tiff, x, y, raster, stopOnError);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}