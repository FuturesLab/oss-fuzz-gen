#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h>
#include <limits.h>  // Include limits.h for UINT_MAX

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    gzFile file;
    int result;
    const char *filename = "/tmp/fuzz_gzwrite.gz";
    unsigned int write_size;

    // Open a gzip file for writing
    file = gzopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }

    // Ensure the write size does not exceed the input size
    write_size = size < UINT_MAX ? (unsigned int)size : UINT_MAX;

    // Call the function-under-test
    result = gzwrite(file, (voidpc)data, write_size);

    // Close the gzip file
    gzclose(file);

    return 0;
}