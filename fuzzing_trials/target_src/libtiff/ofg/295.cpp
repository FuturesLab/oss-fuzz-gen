#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include for memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for the definition of TIFFField

    int TIFFFieldReadCount(const TIFFField *);
}

extern "C" int LLVMFuzzerTestOneInput_295(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFField)) {
        return 0; // Not enough data to create a valid TIFFField
    }

    // Create a TIFFField object from the input data
    TIFFField field;
    // Copy data into the TIFFField object, ensuring we don't exceed bounds
    memcpy(&field, data, sizeof(TIFFField));

    // Fuzz the TIFFFieldReadCount function
    int readCount = TIFFFieldReadCount(&field);

    // Use the readCount in some way to avoid compiler optimizations
    if (readCount < 0) {
        // Handle error case
    }

    return 0;
}