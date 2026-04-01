#include <cstdint>
#include <cstdio>
#include <unistd.h>  // Include for mkstemp and close
#include <cstdlib>   // Include for remove

extern "C" {
    #include <tiffio.h>
}

// Fuzzing harness for TIFFGetStrileOffsetWithErr
extern "C" int LLVMFuzzerTestOneInput_191(const uint8_t *data, size_t size) {
    // Create a temporary file to store the input data
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
    if (!tiff) {
        remove(tmpl);
        return 0;
    }

    // Initialize variables for the function call
    uint32_t strile = 0; // Example value, can be varied
    int error = 0;

    // Call the function-under-test
    uint64_t offset = TIFFGetStrileOffsetWithErr(tiff, strile, &error);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}