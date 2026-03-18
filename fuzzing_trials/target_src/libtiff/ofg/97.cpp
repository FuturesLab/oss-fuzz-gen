#include <cstdint>
#include <cstdlib>
#include <cstring> // Include for memcpy

extern "C" {
    #include <tiffio.h>
    #include <tiff.h> // Include for TIFFField definition
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for the full definition of TIFFField
}

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Ensure there is enough data to form a TIFFFieldInfo structure
    if (size < sizeof(TIFFFieldInfo)) {
        return 0;
    }

    // Allocate memory for a TIFFFieldInfo structure
    TIFFFieldInfo *fieldInfo = (TIFFFieldInfo *)malloc(sizeof(TIFFFieldInfo));
    if (fieldInfo == NULL) {
        return 0;
    }

    // Copy data into the TIFFFieldInfo structure
    memcpy(fieldInfo, data, sizeof(TIFFFieldInfo));

    // Create a dummy TIFFField structure to pass to the function
    TIFFField field;
    field.field_tag = fieldInfo->field_tag;
    field.field_type = fieldInfo->field_type;
    field.field_readcount = fieldInfo->field_readcount;
    field.field_writecount = fieldInfo->field_writecount;
    field.field_passcount = fieldInfo->field_passcount;
    field.field_name = fieldInfo->field_name;
    // field.field_subfields = fieldInfo->field_subfields; // Remove this line as field_subfields is not part of TIFFFieldInfo

    // Call the function-under-test
    TIFFDataType dataType = TIFFFieldDataType(&field);

    // Clean up
    free(fieldInfo);

    return 0;
}