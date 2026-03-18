#include <cstdint>

extern "C" {
    #include <tiffio.h>  // Include the TIFF library headers within extern "C"
    #include <tiff.h>    // Include this to ensure complete type definition for TIFFField
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for tif_dir.h
    uint32_t TIFFFieldTag(const TIFFField *);
}

extern "C" int LLVMFuzzerTestOneInput_229(const uint8_t *data, size_t size) {
    // Check if the size is sufficient to create a TIFFField
    if (size < sizeof(TIFFField)) {
        return 0;
    }

    // Create a TIFFField from the input data
    const TIFFField *field = reinterpret_cast<const TIFFField *>(data);

    // Call the function-under-test
    uint32_t tag = TIFFFieldTag(field);

    // Use the tag in some way to prevent optimizing out the call
    (void)tag;

    return 0;
}