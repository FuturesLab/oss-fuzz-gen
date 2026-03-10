#include <stdint.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    gzFile file;
    z_off64_t offset;
    int whence;

    // Ensure the size is sufficient to extract necessary parameters
    if (size < sizeof(z_off64_t) + sizeof(int)) {
        return 0;
    }

    // Open a temporary gzipped file for writing
    file = gzopen("temp.gz", "wb");
    if (file == NULL) {
        return 0;
    }

    // Write data to the temporary gzipped file
    gzwrite(file, data, size);
    gzclose(file);

    // Reopen the file for reading
    file = gzopen("temp.gz", "rb");
    if (file == NULL) {
        return 0;
    }

    // Extract offset and whence from data
    offset = *(z_off64_t *)(data);
    whence = *(int *)(data + sizeof(z_off64_t));

    // Call the function-under-test
    gzseek(file, offset, whence);

    // Close the file
    gzclose(file);

    return 0;
}