#include <cstdint>
#include <cstdlib>

extern "C" {
    #include <tiffio.h> // Include the necessary header for TIFFField
    #include <tiff.h>   // Include additional TIFF header for complete type definitions
}

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a TIFFFieldInfo
    if (size < sizeof(TIFFFieldInfo)) {
        return 0;
    }

    // Create a TIFFFieldInfo object from the input data
    TIFFFieldInfo *fieldInfo = reinterpret_cast<TIFFFieldInfo*>(const_cast<uint8_t*>(data));

    // Call the function-under-test
    int result = TIFFFieldIsAnonymous(reinterpret_cast<TIFFField*>(fieldInfo));

    // Use the result in some way to avoid compiler optimizations
    if (result) {
        // Do something if the field is anonymous
    }

    return 0;
}