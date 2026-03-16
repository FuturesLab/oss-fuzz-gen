#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h"  // Corrected path for the definition of TIFFField
}

extern "C" int LLVMFuzzerTestOneInput_227(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a TIFFField object
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Allocate memory for a TIFFField object
    TIFFField *field = (TIFFField *)malloc(sizeof(TIFFField));
    if (field == nullptr) {
        return 0;
    }

    // Copy data into the TIFFField object
    memcpy(field, data, sizeof(TIFFField));

    // Call the function-under-test
    uint32_t tag = TIFFFieldTag(field);

    // Use the tag value in some way to avoid compiler optimizations
    volatile uint32_t use_tag = tag;
    (void)use_tag;

    // Free the allocated memory
    free(field);

    return 0;
}