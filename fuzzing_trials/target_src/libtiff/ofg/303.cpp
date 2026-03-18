#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <tiffio.h>
#include <unistd.h> // Include for close() and unlink()

extern "C" {
    // Include the necessary TIFF headers
    #include <tiff.h>
    #include <tiffio.h>
}

// Function-under-test
extern "C" uint64_t TIFFGetStrileByteCountWithErr(TIFF *, uint32_t, int *);

extern "C" int LLVMFuzzerTestOneInput_303(const uint8_t *data, size_t size) {
    // Create a temporary TIFF file
    char tmpl[] = "/tmp/fuzzfileXXXXXX.tiff";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the input data to the temporary file
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
        unlink(tmpl);
        return 0;
    }

    // Prepare parameters for the function call
    uint32_t strileIndex = 0; // Example index, can be varied
    int error = 0;

    // Call the function-under-test
    uint64_t byteCount = TIFFGetStrileByteCountWithErr(tiff, strileIndex, &error);

    // Clean up
    TIFFClose(tiff);
    unlink(tmpl);

    return 0;
}