#include <cstdint>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_277(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // Ensure there's at least one byte to determine the TIFFDataType
    }

    // Cast the first byte of data to TIFFDataType
    TIFFDataType dataType = static_cast<TIFFDataType>(data[0]);

    // Call the function-under-test
    int width = TIFFDataWidth(dataType);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)width;

    return 0;
}