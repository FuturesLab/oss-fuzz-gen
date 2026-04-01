#include <cstdint>
#include <cstdlib>
#include <cstring> // For memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path to include the definition of TIFFField
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Allocate memory for a TIFFField object
    TIFFField *field = (TIFFField *)malloc(sizeof(TIFFField));
    if (field == nullptr) {
        return 0;
    }

    // Copy data into the TIFFField object
    memcpy(field, data, sizeof(TIFFField));

    // Call the function-under-test
    int result = TIFFFieldIsAnonymous(field);

    // Free allocated memory
    free(field);

    return 0;
}