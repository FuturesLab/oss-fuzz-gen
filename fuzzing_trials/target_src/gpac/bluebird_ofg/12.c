#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < sizeof(GF_ISOStorageMode)) {
        return 0;
    }

    // Create a new GF_ISOFile using the library's function
    // Provide a temporary file name and a temporary directory
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, "/tmp");
    if (movie == NULL) {
        return 0;
    }

    // Extract GF_ISOStorageMode from the input data
    GF_ISOStorageMode storageMode = *(GF_ISOStorageMode *)data;

    // Call the function-under-test
    gf_isom_set_storage_mode(movie, storageMode);

    // Clean up
    gf_isom_close(movie);

    return 0;
}