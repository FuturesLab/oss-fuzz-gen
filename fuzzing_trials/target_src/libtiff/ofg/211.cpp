#include <cstddef>
#include <cstdint>
#include <cstring>  // Include for strlen

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h"  // Correct path for the definition of TIFFField
}

extern "C" int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Create a TIFFField object from the input data
    TIFFField tiffField;
    memcpy(&tiffField, data, sizeof(TIFFField));

    // Call the function-under-test
    const char *fieldName = TIFFFieldName(&tiffField);

    // Use the fieldName in some way to prevent compiler optimizations
    if (fieldName != nullptr) {
        // Print the field name length
        volatile size_t length = strlen(fieldName);
    }

    return 0;
}