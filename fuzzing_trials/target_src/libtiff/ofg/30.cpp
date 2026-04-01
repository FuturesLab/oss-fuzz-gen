#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" {
#include <tiffio.h>
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to extract necessary values
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Write the input data to a temporary file
    FILE *file = fopen("/tmp/fuzzfile.tiff", "wb");
    if (!file) {
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Initialize variables
    TIFF *tiff = TIFFOpen("/tmp/fuzzfile.tiff", "r");
    if (tiff == nullptr) {
        return 0;
    }

    uint32_t tag = *(reinterpret_cast<const uint32_t *>(data));
    
    // Prepare a buffer for TIFFVGetField
    int value; // Assuming the value is of type int for demonstration purposes

    // Call the function-under-test
    TIFFGetField(tiff, tag, &value);

    // Clean up
    TIFFClose(tiff);

    return 0;
}