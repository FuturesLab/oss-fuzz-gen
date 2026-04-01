#include <cstdint>
#include <cstdlib>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFFieldInfo)) {
        return 0; // Not enough data to proceed
    }

    // Initialize TIFF structure
    TIFF *tiff = TIFFOpen("/dev/null", "w");
    if (tiff == nullptr) {
        return 0; // Failed to open TIFF
    }

    // Cast data to TIFFFieldInfo
    const TIFFFieldInfo *fieldInfo = reinterpret_cast<const TIFFFieldInfo *>(data);

    // Ensure there's enough data for at least one TIFFFieldInfo element
    uint32_t fieldInfoCount = size / sizeof(TIFFFieldInfo);

    // Call the function-under-test
    TIFFMergeFieldInfo(tiff, fieldInfo, fieldInfoCount);

    // Cleanup
    TIFFClose(tiff);

    return 0;
}