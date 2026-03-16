#include <cstdint>
#include <cstdlib>
#include <cstring> // For memcpy

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for TIFFField definition

    TIFFDataType TIFFFieldDataType(const TIFFField *);
}

extern "C" int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Allocate memory for TIFFField and copy data
    TIFFField* field = reinterpret_cast<TIFFField*>(malloc(sizeof(TIFFField)));
    if (field == nullptr) {
        return 0;
    }

    // Copy data into field, ensuring not to exceed the size of TIFFField
    memcpy(field, data, sizeof(TIFFField));

    // Call the function-under-test
    TIFFDataType result = TIFFFieldDataType(field);

    // Free allocated memory
    free(field);

    return 0;
}