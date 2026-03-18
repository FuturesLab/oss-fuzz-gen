#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>
#include <unistd.h> // Include this for STDIN_FILENO

int LLVMFuzzerTestOneInput_85(const uint8_t *data, size_t size) {
    // Initialize the gzFile pointer
    gzFile file = gzdopen(STDIN_FILENO, "rb");
    if (file == NULL) {
        return 0;
    }

    // Allocate a buffer for reading
    voidp buffer = malloc(size);
    if (buffer == NULL) {
        gzclose(file);
        return 0;
    }

    // Ensure the buffer is non-NULL and has a valid size
    unsigned int read_size = size > 0 ? (unsigned int)size : 1;

    // Call the function-under-test
    gzread(file, buffer, read_size);

    // Clean up
    free(buffer);
    gzclose(file);

    return 0;
}