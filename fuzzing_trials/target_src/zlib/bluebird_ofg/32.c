#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Initialize variables for gzfwrite
    voidpc void_data = (voidpc)data; // Cast data to voidpc
    z_size_t item_size = 1; // Set item size to 1 byte
    z_size_t item_count = size; // Set item count to the size of the input data

    // Create a temporary file to use with gzopen
    const char *filename = "/tmp/fuzz_gzfile.gz";
    gzFile gzfile = gzopen(filename, "wb"); // Open a gzFile in write mode

    if (gzfile == NULL) {
        return 0; // If gzopen fails, return early
    }

    // Call the function-under-test
    z_size_t result = gzfwrite(void_data, item_size, item_count, gzfile);

    // Clean up
    gzclose(gzfile);

    return 0;
}