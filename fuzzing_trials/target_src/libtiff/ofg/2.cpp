#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <tiffio.h>
#include <cstdarg>

extern "C" {
    // The correct function signature from tiffio.h
    int TIFFVGetFieldDefaulted(TIFF *tif, uint32_t tag, va_list ap);
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    if (size < sizeof(uint32_t)) {
        return 0; // Not enough data to extract a uint32_t tag
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Failed to open a file stream
    }

    fwrite(data, 1, size, file);
    fclose(file);

    // Open the TIFF file
    TIFF *tiff = TIFFOpen(tmpl, "r");
    if (!tiff) {
        remove(tmpl);
        return 0; // Failed to open TIFF
    }

    // Extract a uint32_t tag from the data
    uint32_t tag;
    memcpy(&tag, data, sizeof(uint32_t));

    // Initialize a va_list
    va_list ap;
    int value = 0; // Example value to pass to the va_list

    // Instead of using va_start and va_end, directly call the function
    // Note: This assumes the tag expects an integer as a parameter
    TIFFVGetFieldDefaulted(tiff, tag, ap);

    // Clean up
    TIFFClose(tiff);
    remove(tmpl);

    return 0;
}