#include <cstdint>
#include <cstdlib>
#include <cstring> // For memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for the header file
}

extern "C" int LLVMFuzzerTestOneInput_294(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Allocate memory for a TIFFField structure
    TIFFField *field = (TIFFField *)malloc(sizeof(TIFFField));
    if (field == NULL) {
        return 0;
    }

    // Copy the data into the TIFFField structure
    memcpy(field, data, sizeof(TIFFField));

    // Call the function-under-test
    int readCount = TIFFFieldReadCount(field);

    // Free the allocated memory
    free(field);

    return 0;
}