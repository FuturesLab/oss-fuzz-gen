#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
    // Ensure there is enough data to proceed
    if (size < sizeof(tdir_t)) {
        return 0;
    }

    // Initialize TIFF structure
    TIFF *tif = TIFFOpen("/tmp/fuzz.tiff", "w");
    if (tif == NULL) {
        return 0;
    }

    // Extract tdir_t from the input data
    tdir_t directory = *(const tdir_t *)data;

    // Call the function-under-test
    TIFFSetDirectory(tif, directory);

    // Clean up
    TIFFClose(tif);

    return 0;
}