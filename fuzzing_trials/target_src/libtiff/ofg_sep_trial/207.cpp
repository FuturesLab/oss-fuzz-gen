#include <cstdint>
#include <cstdlib>
#include <cstring>  // For memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h"  // Correct path for tif_dir.h
}

extern "C" int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a TIFFField structure
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Initialize a TIFFField structure from the input data
    TIFFField field;
    memcpy(&field, data, sizeof(TIFFField));

    // Call the function-under-test
    const char *fieldName = TIFFFieldName(&field);

    // Optionally, you can add checks or use the fieldName
    // For this example, we just ensure it's not null
    if (fieldName != nullptr) {
        // Do something with fieldName if needed
    }

    return 0;
}