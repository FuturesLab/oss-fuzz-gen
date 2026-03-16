#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_230(const uint8_t *data, size_t size) {
    // Initialize TIFF structure
    TIFF *tif = TIFFOpen("temp.tiff", "w");
    if (tif == NULL) {
        return 0;
    }

    // Ensure that the input size is sufficient to split into two buffers
    if (size < 2) {
        TIFFClose(tif);
        return 0;
    }

    // Split the input data into two buffers
    size_t half_size = size / 2;
    void *buffer1 = (void *)(data);
    void *buffer2 = (void *)(data + half_size);

    // Define sizes for the buffers
    tmsize_t size1 = (tmsize_t)half_size;
    tmsize_t size2 = (tmsize_t)(size - half_size);

    // Call the function-under-test
    TIFFReadFromUserBuffer(tif, 0, buffer1, size1, buffer2, size2);

    // Clean up
    TIFFClose(tif);

    return 0;
}