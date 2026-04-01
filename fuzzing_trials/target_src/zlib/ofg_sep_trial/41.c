#include <stdint.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>

// Remove 'extern "C"' as it is not needed in C code
int LLVMFuzzerTestOneInput_41(const uint8_t *data, size_t size) {
    gzFile file;
    unsigned int buffer_size;

    // Ensure data is large enough to extract a meaningful buffer size
    if (size < sizeof(unsigned int)) {
        return 0;
    }

    // Open a temporary file to get a valid gzFile handle
    file = gzopen("/dev/null", "wb");
    if (file == NULL) {
        return 0;
    }

    // Extract an unsigned int from the data for buffer size
    buffer_size = *((unsigned int *)data);

    // Call the function-under-test
    gzbuffer(file, buffer_size);

    // Clean up
    gzclose(file);

    return 0;
}