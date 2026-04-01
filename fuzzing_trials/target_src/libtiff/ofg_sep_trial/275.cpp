#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_275(const uint8_t *data, size_t size) {
    // Ensure we have enough data to read a TIFFDataType
    if (size < sizeof(TIFFDataType)) {
        return 0;
    }

    // Interpret the first bytes of data as a TIFFDataType
    TIFFDataType dataType = static_cast<TIFFDataType>(data[0]);

    // Call the function-under-test
    int width = TIFFDataWidth(dataType);

    // Optionally, use the result to prevent compiler optimizations
    (void)width;

    return 0;
}