#include <tiffio.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzz.tiff", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Ensure the input data is null-terminated for a string
    char *fieldName = (char *)malloc(size + 1);
    if (fieldName == nullptr) {
        TIFFClose(tiff);
        return 0;
    }
    memcpy(fieldName, data, size);
    fieldName[size] = '\0';

    // Call the function-under-test
    const TIFFField *field = TIFFFieldWithName(tiff, fieldName);

    // Clean up
    free(fieldName);
    TIFFClose(tiff);

    return 0;
}