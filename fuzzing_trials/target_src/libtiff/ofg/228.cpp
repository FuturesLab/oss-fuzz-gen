#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for the definition of TIFFField
}

extern "C" int LLVMFuzzerTestOneInput_228(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFField)) {
        return 0; // Not enough data to create a TIFFField
    }

    // Allocate memory for TIFFField and copy data into it
    TIFFField* field = (TIFFField*)malloc(sizeof(TIFFField));
    if (field == nullptr) {
        return 0; // Failed to allocate memory
    }

    // Copy data into the allocated TIFFField structure
    memcpy(field, data, sizeof(TIFFField));

    // Call the function-under-test
    uint32_t tag = TIFFFieldTag(field);

    // Clean up
    free(field);

    return 0;
}