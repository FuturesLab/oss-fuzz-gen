#include <cstdint>
#include <tiffio.h>

extern "C" {
    int LLVMFuzzerTestOneInput_47(const uint8_t *data, size_t size) {
        if (size < sizeof(int)) {
            return 0; // Not enough data to extract an integer
        }

        // Create a TIFF structure
        TIFF *tiff = TIFFOpen("/tmp/test.tiff", "w");
        if (!tiff) {
            return 0; // Failed to create a TIFF file
        }

        // Extract an integer from the input data
        int fileDescriptor = *reinterpret_cast<const int*>(data);

        // Call the function-under-test
        TIFFSetFileno(tiff, fileDescriptor);

        // Clean up
        TIFFClose(tiff);

        return 0;
    }
}