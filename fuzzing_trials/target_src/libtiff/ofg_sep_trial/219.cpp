#include <cstdint>
#include <cstdlib>
#include <cstring> // Include this for memcpy

extern "C" {
    #include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_219(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfile.tiff", "w");
    if (tiff == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated for the string parameter
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        TIFFClose(tiff);
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    // Set a non-zero value for the second parameter (e.g., 1)
    int isTiled = 1;

    // Call the function-under-test
    TIFFWriteCheck(tiff, isTiled, name);

    // Clean up
    free(name);
    TIFFClose(tiff);

    return 0;
}