#include <cstdint>
#include <cstdio>
#include <cstdlib>   // For mkstemp and close
#include <unistd.h>  // For mkstemp and close

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_112(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff) {
        // Call the function-under-test
        uint64_t tileSize = TIFFTileSize64(tiff);

        // Close the TIFF file
        TIFFClose(tiff);
    }

    // Clean up the temporary file
    remove(tmpl);

    return 0;
}