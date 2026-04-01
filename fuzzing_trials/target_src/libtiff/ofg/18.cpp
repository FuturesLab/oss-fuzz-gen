#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h"  // Correct path for the definition of TIFFField

    // Function prototype for the function-under-test
    int TIFFFieldSetGetSize(const TIFFField *);
}

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a TIFFField object
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Create a TIFFField object from the input data
    TIFFField *tiffField = reinterpret_cast<TIFFField *>(malloc(sizeof(TIFFField)));
    if (tiffField == nullptr) {
        return 0;
    }

    // Copy data into the TIFFField object
    memcpy(tiffField, data, sizeof(TIFFField));

    // Call the function-under-test
    int result = TIFFFieldSetGetSize(tiffField);

    // Clean up
    free(tiffField);

    return 0;
}