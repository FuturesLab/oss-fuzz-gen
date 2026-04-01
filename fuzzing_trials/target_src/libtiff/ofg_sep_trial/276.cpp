#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_276(const uint8_t *data, size_t size) {
    if (size < sizeof(TIFFDataType)) {
        return 0;
    }

    // Extract a TIFFDataType from the input data
    TIFFDataType tiffDataType = static_cast<TIFFDataType>(data[0]);

    // Call the function-under-test
    int width = TIFFDataWidth(tiffDataType);

    // Use the result to prevent any compiler optimizations that might skip the function call
    volatile int result = width;
    (void)result;

    return 0;
}