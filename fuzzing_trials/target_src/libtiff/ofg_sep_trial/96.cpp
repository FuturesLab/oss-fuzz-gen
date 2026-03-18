#include <cstdint>
#include <cstdlib>
#include <cstring>  // For memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h"  // Correct path for TIFFField definition
}

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a TIFFField object
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Allocate memory for a TIFFField object
    TIFFField *field = static_cast<TIFFField *>(malloc(sizeof(TIFFField)));
    if (field == nullptr) {
        return 0;
    }

    // Copy data into the TIFFField object
    memcpy(field, data, sizeof(TIFFField));

    // Call the function-under-test
    TIFFDataType dataType = TIFFFieldDataType(field);

    // Clean up
    free(field);

    return 0;
}