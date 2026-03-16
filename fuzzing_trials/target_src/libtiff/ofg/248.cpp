#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy

extern "C" {
    #include <tiff.h>
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h"  // Correct path for TIFFField structure
}

// Fuzzing harness
extern "C" int LLVMFuzzerTestOneInput_248(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a TIFFField
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Create a TIFFField object from the input data
    TIFFField tiffField;
    const TIFFField *fieldPtr = &tiffField;

    // Copy data into the TIFFField object, ensuring no overflow
    memcpy(&tiffField, data, sizeof(TIFFField));

    // Call the function-under-test
    int result = TIFFFieldPassCount(fieldPtr);

    // Use the result in some way to avoid compiler optimizations
    (void)result;

    return 0;
}