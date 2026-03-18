#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate a TIFF file
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

    // Write the fuzz data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (tiff == nullptr) {
        remove(tmpl);
        return 0;
    }

    // Use a non-zero strip index for testing
    uint32_t stripIndex = 1;

    // Call the function-under-test
    uint64_t result = TIFFRawStripSize64(tiff, stripIndex);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}