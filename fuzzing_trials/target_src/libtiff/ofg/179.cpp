#include <cstdint>
#include <cstdio>
#include <cstdlib>  // For mkstemp and remove
#include <unistd.h> // For close

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_179(const uint8_t *data, size_t size) {
    // Create a temporary file to hold the TIFF data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == nullptr) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file using libtiff
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    uint64_t rowSize = TIFFTileRowSize64(tiff);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}