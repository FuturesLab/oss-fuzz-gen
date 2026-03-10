#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    gzFile file;
    unsigned int buffer_size;

    // Ensure the size is sufficient to extract an unsigned int
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Open a temporary gzipped file for the purpose of fuzzing
    file = gzopen("/dev/null", "wb");
    if (file == NULL) {
        return 0;
    }

    // Extract an unsigned int from the data
    buffer_size = *((unsigned int*)data);

    // Call the function-under-test
    gzbuffer(file, buffer_size);

    // Close the gzFile
    gzclose(file);

    return 0;
}