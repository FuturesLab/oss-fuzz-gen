#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Ensure size is not zero to avoid division by zero
    if (size == 0) {
        return 0;
    }

    // Initialize parameters for gzfwrite
    const void *voidpc = (const void *)data;
    size_t item_size = 1;  // Use a non-zero item size
    size_t item_count = size;  // Use the size of data as item count

    // Create a temporary file to use with gzFile
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Open the temporary file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "wb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    size_t result = gzfwrite(voidpc, item_size, item_count, gzfile);

    // Clean up
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}