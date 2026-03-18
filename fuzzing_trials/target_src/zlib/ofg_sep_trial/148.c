#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to split into two strings
    if (size < 2) {
        return 0;
    }

    // Split the input data into two parts for the file name and mode
    size_t filename_size = size / 2;
    size_t mode_size = size - filename_size;

    // Allocate memory for the file name and mode strings
    char *filename = (char *)malloc(filename_size + 1);
    char *mode = (char *)malloc(mode_size + 1);

    if (filename == NULL || mode == NULL) {
        // Handle memory allocation failure
        free(filename);
        free(mode);
        return 0;
    }

    // Copy data into the allocated memory and null-terminate
    memcpy(filename, data, filename_size);
    filename[filename_size] = '\0';

    memcpy(mode, data + filename_size, mode_size);
    mode[mode_size] = '\0';

    // Call the function-under-test
    gzFile file = gzopen(filename, mode);

    // Cleanup
    if (file != NULL) {
        gzclose(file);
    }
    free(filename);
    free(mode);

    return 0;
}