#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <tiffio.h>
    #include <tiff.h>
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for tif_dir.h
}

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("temp.tiff", "w");
    if (tiff == NULL) {
        return 0;
    }

    // Initialize TIFFFieldArray structure
    TIFFFieldArray fieldArray;
    fieldArray.type = tfiatImage; // Assuming tfiatImage is a valid type, replace with correct one if needed
    fieldArray.count = 1;
    // Ensure the size of data is appropriate for the fields
    if (size < sizeof(TIFFField)) {
        TIFFClose(tiff);
        return 0;
    }
    fieldArray.fields = (TIFFField *)data;

    // Call the function-under-test
    TIFFCreateCustomDirectory(tiff, &fieldArray);

    // Cleanup
    TIFFClose(tiff);

    return 0;
}