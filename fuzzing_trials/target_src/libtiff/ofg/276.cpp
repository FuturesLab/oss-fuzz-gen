#include <cstdint>
#include <tiffio.h>

extern "C" {
    int LLVMFuzzerTestOneInput_276(const uint8_t *data, size_t size) {
        // Ensure there's enough data to extract a TIFFDataType
        if (size < sizeof(TIFFDataType)) {
            return 0;
        }

        // Cast the first bytes of data to TIFFDataType
        TIFFDataType tiffDataType = static_cast<TIFFDataType>(data[0]);

        // Call the function-under-test
        int result = TIFFDataWidth(tiffDataType);

        // Use the result to prevent compiler optimizations from removing the function call
        (void)result;

        return 0;
    }
}