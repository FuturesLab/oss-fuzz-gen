#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    voidp buffer;
    z_size_t itemSize;
    z_size_t itemCount;
    gzFile file;

    // Initialize the parameters
    buffer = malloc(size > 0 ? size : 1); // Ensure buffer is not NULL
    itemSize = size > 0 ? size : 1;       // Ensure itemSize is not zero
    itemCount = 1;                        // Read one item for simplicity

    // Open a gzFile from the input data
    file = gzdopen(fileno(tmpfile()), "wb+");
    if (file == NULL) {
        free(buffer);
        return 0;
    }

    // Write the data to the gzFile to simulate a valid gzFile
    gzwrite(file, data, size);
    gzrewind(file); // Rewind to the beginning for reading

    // Call the function-under-test
    gzfread(buffer, itemSize, itemCount, file);

    // Clean up
    gzclose(file);
    free(buffer);

    return 0;
}