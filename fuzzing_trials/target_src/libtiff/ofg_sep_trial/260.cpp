#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include for memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h"  // Correct path for the definition of TIFFField
}

extern "C" int LLVMFuzzerTestOneInput_260(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a TIFFField object
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Allocate memory for a TIFFField object and copy data into it
    TIFFField *field = (TIFFField *)malloc(sizeof(TIFFField));
    if (field == nullptr) {
        return 0;
    }
    
    // Copy the data into the TIFFField structure
    memcpy(field, data, sizeof(TIFFField));

    // Call the function-under-test
    int result = TIFFFieldSetGetCountSize(field);

    // Clean up
    free(field);

    return 0;
}