#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    gzFile file;
    voidp buffer;
    unsigned int length;
    int result;

    // Initialize the buffer with some data
    buffer = malloc(size > 0 ? size : 1); // Ensure buffer is not NULL
    if (buffer == NULL) {
        return 0;
    }

    // Open a memory buffer as a gzFile
    FILE *tmp = tmpfile();
    if (tmp == NULL) {
        free(buffer);
        return 0;
    }
    file = gzdopen(dup(fileno(tmp)), "rb");
    if (file == NULL) {
        fclose(tmp);
        free(buffer);
        return 0;
    }

    // Write the input data to the gzFile
    fwrite(data, 1, size, tmp);
    rewind(tmp);

    // Set a length to read
    length = size > 0 ? size : 1; // Ensure length is not zero

    // Call the function-under-test
    result = gzread(file, buffer, length);

    // Clean up
    gzclose(file);
    fclose(tmp);
    free(buffer);

    return 0;
}