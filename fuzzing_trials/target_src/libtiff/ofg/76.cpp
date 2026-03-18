#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    TIFF *tiff = TIFFOpen("temp.tiff", "w");
    if (tiff == NULL) {
        return 0;
    }

    TIFFFieldInfo fieldInfo;
    fieldInfo.field_tag = 0;
    fieldInfo.field_readcount = TIFF_VARIABLE;
    fieldInfo.field_writecount = TIFF_VARIABLE;
    fieldInfo.field_type = TIFF_BYTE;
    fieldInfo.field_bit = 0;
    fieldInfo.field_oktochange = 1;
    fieldInfo.field_passcount = 0;
    fieldInfo.field_name = "TestField";

    uint32_t fieldInfoCount = 1;

    // Call the function-under-test
    TIFFMergeFieldInfo(tiff, &fieldInfo, fieldInfoCount);

    TIFFClose(tiff);
    return 0;
}