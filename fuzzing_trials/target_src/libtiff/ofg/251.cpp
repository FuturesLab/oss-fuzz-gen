#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include <tiffio.h>
    #include "/src/libtiff/libtiff/tif_dir.h" // Correct path for the header where TIFFField is fully defined
}

extern "C" int LLVMFuzzerTestOneInput_251(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFFieldInfo)) {
        return 0; // Not enough data to form a valid TIFFFieldInfo
    }

    // Create a TIFFFieldInfo object from the input data
    const TIFFFieldInfo *tiffFieldInfo = reinterpret_cast<const TIFFFieldInfo *>(data);

    // Call the function-under-test
    int result = TIFFFieldPassCount(reinterpret_cast<const TIFFField *>(tiffFieldInfo));

    // Use the result in some way to prevent optimization out
    if (result < 0) {
        return 0;
    }

    return 0;
}