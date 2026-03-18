#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    // Include necessary C headers and functions
    #include <tiff.h>
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for the definition of TIFFField
}

// Fuzzing harness for TIFFFieldWriteCount function
extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFField)) {
        return 0; // Not enough data to create a valid TIFFField
    }

    // Allocate memory for a TIFFField object
    TIFFField* field = (TIFFField*)malloc(sizeof(TIFFField));
    if (field == NULL) {
        return 0; // Memory allocation failed
    }

    // Copy data into the TIFFField object
    memcpy(field, data, sizeof(TIFFField));

    // Call the function-under-test
    int result = TIFFFieldWriteCount(field);

    // Free the allocated memory
    free(field);

    return 0;
}