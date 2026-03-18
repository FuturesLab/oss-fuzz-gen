#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" {
    #include <tiffio.h>
    #include <tiff.h>
    #include "/src/libtiff/libtiff/tif_dir.h" // Corrected path for the definition of TIFFFieldArray
}

extern "C" int LLVMFuzzerTestOneInput_344(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/tmp/fuzzfile.tiff", "w+");
    if (tiff == nullptr) {
        return 0;
    }

    // Write the fuzz data to the TIFF file
    // Cast 'data' to 'void *' to match the function signature
    if (TIFFWriteRawStrip(tiff, 0, (void *)data, size) == -1) {
        TIFFClose(tiff);
        return 0;
    }

    // Define a non-null TIFFFieldArray
    TIFFFieldArray fieldArray;
    fieldArray.type = tfiatImage; // Ensure this constant is defined in the included headers
    fieldArray.count = 0;
    fieldArray.fields = nullptr;

    // Call the function-under-test
    toff_t offset = 0;
    TIFFReadCustomDirectory(tiff, offset, &fieldArray);

    // Cleanup
    TIFFClose(tiff);

    return 0;
}