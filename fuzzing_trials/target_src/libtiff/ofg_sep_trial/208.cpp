#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

extern "C" {
    #include <tiffio.h>
    #include <tiff.h>
}

extern "C" int LLVMFuzzerTestOneInput_208(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to create a TIFFFieldInfo object
    if (size < sizeof(TIFFFieldInfo)) {
        return 0;
    }

    // Cast the input data to a TIFFFieldInfo pointer
    const TIFFFieldInfo *fieldInfo = reinterpret_cast<const TIFFFieldInfo *>(data);

    // Open a dummy TIFF file in memory
    TIFF *tif = TIFFOpen("dummy", "r");
    if (!tif) {
        return 0;
    }

    // Call the function-under-test
    const TIFFField *field = TIFFFindField(tif, fieldInfo->field_tag, fieldInfo->field_type);

    // Use the fieldName in some way to avoid compiler optimizations
    if (field) {
        const char *fieldName = TIFFFieldName(field);
        if (fieldName) {
            // Print the field name (this is just for demonstration and can be removed)
            printf("Field Name: %s\n", fieldName);
        }
    }

    // Close the TIFF file
    TIFFClose(tif);

    return 0;
}