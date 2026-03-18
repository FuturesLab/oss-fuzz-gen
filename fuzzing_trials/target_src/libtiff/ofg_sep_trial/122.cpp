#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <tiffio.h>

extern "C" {
    // Include the TIFFField structure definition
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path to the header file

    // Function to be fuzzed
    int TIFFFieldWriteCount(const TIFFField *);
}

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFField)) {
        return 0; // Not enough data to form a valid TIFFField
    }

    // Allocate memory for a TIFFField structure
    TIFFField *field = (TIFFField *)malloc(sizeof(TIFFField));
    if (field == nullptr) {
        return 0; // Memory allocation failed
    }

    // Copy data into the TIFFField structure
    memcpy(field, data, sizeof(TIFFField));

    // Call the function-under-test
    int result = TIFFFieldWriteCount(field);

    // Clean up
    free(field);

    return 0;
}