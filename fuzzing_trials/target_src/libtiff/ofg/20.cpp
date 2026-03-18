#include <cstdint>
#include <cstdlib>
#include <cstring>  // Include the header for memcpy
#include <tiffio.h>  // Ensure you have the appropriate TIFF library headers

extern "C" {
    #include <tiffio.h>  // Wrap the TIFF library header in extern "C"
}

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *data, size_t size) {
    // Ensure that the size is a multiple of the size of uint32_t
    if (size < sizeof(uint32_t) || size % sizeof(uint32_t) != 0) {
        return 0;
    }

    tmsize_t num_elements = size / sizeof(uint32_t);
    uint32_t *longArray = static_cast<uint32_t *>(malloc(size));

    if (longArray == NULL) {
        return 0;
    }

    // Copy the data into the longArray
    memcpy(longArray, data, size);

    // Call the function-under-test
    TIFFSwabArrayOfLong(longArray, num_elements);

    // Clean up
    free(longArray);

    return 0;
}