#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Define and initialize variables for gzfread parameters
    voidp buf = malloc(size);
    if (buf == NULL) {
        return 0; // Exit if memory allocation fails
    }
    
    z_size_t buf_size = size > 0 ? size : 1; // Ensure buf_size is not zero
    z_size_t count = 1; // Read one block of buf_size

    // Create a temporary file to simulate input for gzdopen
    FILE *tmpFile = tmpfile();
    if (tmpFile == NULL) {
        free(buf);
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tmpFile);
    rewind(tmpFile);

    // Open the temporary file as a gzFile
    gzFile file = gzdopen(fileno(tmpFile), "rb");
    if (file != NULL) {
        // Call the function-under-test
        gzfread(buf, buf_size, count, file);
        gzclose(file); // Close the gzFile
    }

    fclose(tmpFile); // Close the temporary file
    free(buf); // Free allocated memory

    return 0;
}