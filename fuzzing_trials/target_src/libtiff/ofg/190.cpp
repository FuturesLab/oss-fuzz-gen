#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>  // Include for 'close' and 'remove'

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_190(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
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

    // Prepare parameters for the function call
    uint32_t strileIndex = 0; // Example index, can be varied
    int errorCode = 0; // Variable to capture error code

    // Call the function-under-test
    uint64_t offset = TIFFGetStrileOffsetWithErr(tiff, strileIndex, &errorCode);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}