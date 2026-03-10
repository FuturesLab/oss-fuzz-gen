#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
    gzFile file;
    int flush;

    // Create a temporary file to work with gzFile
    const char *filename = "/tmp/fuzz_gzflush.gz";
    file = gzopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Write some data to the gzFile to set it up for flushing
    if (size > 0) {
        gzwrite(file, data, size);
    }

    // Set the flush parameter to a valid value
    // Possible values for flush are Z_NO_FLUSH, Z_SYNC_FLUSH, Z_FULL_FLUSH, Z_FINISH
    flush = Z_SYNC_FLUSH;

    // Call the function-under-test
    gzflush(file, flush);

    // Close the gzFile
    gzclose(file);

    return 0;
}