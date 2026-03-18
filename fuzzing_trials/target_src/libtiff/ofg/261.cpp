#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h"  // Correct path for the internal header where _TIFFField is defined

    // Function signature
    int TIFFFieldSetGetCountSize(const TIFFField *);
}

extern "C" int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    // Ensure there's enough data to create a TIFFField object
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Allocate memory for a TIFFField object
    TIFFField* tiffField = (TIFFField*)malloc(sizeof(TIFFField));
    if (tiffField == NULL) {
        return 0;
    }

    // Copy data into the TIFFField object
    memcpy(tiffField, data, sizeof(TIFFField));

    // Call the function-under-test
    int result = TIFFFieldSetGetCountSize(tiffField);

    // Clean up
    free(tiffField);

    return 0;
}