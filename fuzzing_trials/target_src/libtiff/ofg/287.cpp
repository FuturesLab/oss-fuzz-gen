#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
#include <tiffio.h>

// Correct the function signature to match the declaration in tiffio.h
void TIFFWarningExtR(TIFF *, const char *, const char *, ...);
}

extern "C" int LLVMFuzzerTestOneInput_287(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/dev/null", "w");
    if (!tiff) {
        return 0;
    }

    // Prepare strings from the input data
    char *module = (char *)malloc(size / 3 + 1);
    char *fmt = (char *)malloc(size / 3 + 1);
    char *dummy = (char *)malloc(size / 3 + 1);

    if (!module || !fmt || !dummy) {
        TIFFClose(tiff);
        free(module);
        free(fmt);
        free(dummy);
        return 0;
    }

    // Split data into three parts for module, fmt, and dummy
    size_t part_size = size / 3;
    memcpy(module, data, part_size);
    memcpy(fmt, data + part_size, part_size);
    memcpy(dummy, data + 2 * part_size, part_size);

    // Null-terminate the strings
    module[part_size] = '\0';
    fmt[part_size] = '\0';
    dummy[part_size] = '\0';

    // Call the function-under-test
    TIFFWarningExtR(tiff, module, fmt, (void *)dummy);

    // Clean up
    TIFFClose(tiff);
    free(module);
    free(fmt);
    free(dummy);

    return 0;
}