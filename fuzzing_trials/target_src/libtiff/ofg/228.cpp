#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <tiffio.h>

    // Forward declaration of the function-under-test
    uint32_t TIFFFieldTag(const TIFFField *);

    // Include the TIFFField definition from the correct path
    #include "/src/libtiff/libtiff/tif_dir.h"
}

extern "C" int LLVMFuzzerTestOneInput_228(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFField)) {
        return 0; // Not enough data to form a valid TIFFField
    }

    // Allocate memory for a TIFFField structure
    TIFFField *field = reinterpret_cast<TIFFField *>(malloc(sizeof(TIFFField)));
    if (field == nullptr) {
        return 0; // Memory allocation failed
    }

    // Copy data into the TIFFField structure
    memcpy(field, data, sizeof(TIFFField));

    // Ensure that the TIFFField structure is not NULL
    if (field != nullptr) {
        // Call the function-under-test
        uint32_t tag = TIFFFieldTag(field);

        // Optionally, use the tag value to prevent optimization out
        (void)tag;
    }

    // Free the allocated memory
    free(field);

    return 0;
}