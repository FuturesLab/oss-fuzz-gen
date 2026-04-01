#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to create a TIFFFieldInfo
    if (size < sizeof(TIFFFieldInfo)) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("dummy.tif", "w");
    if (tiff == nullptr) {
        return 0;
    }

    // Use part of the input data to create a TIFFFieldInfo
    const TIFFFieldInfo *fieldInfo = reinterpret_cast<const TIFFFieldInfo *>(data);

    // Use the remaining data size as the count parameter
    uint32_t count = static_cast<uint32_t>((size - sizeof(TIFFFieldInfo)) / sizeof(TIFFFieldInfo));

    // Call the function-under-test
    TIFFMergeFieldInfo(tiff, fieldInfo, count);

    // Clean up
    TIFFClose(tiff);

    return 0;
}