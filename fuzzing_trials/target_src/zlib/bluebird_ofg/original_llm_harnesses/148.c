#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include stdlib.h for malloc and free

int LLVMFuzzerTestOneInput_148(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to split data into two non-empty strings
    if (size < 2) {
        return 0;
    }

    // Find a position to split the data into two strings
    size_t split_pos = size / 2;

    // Allocate memory for the file name and mode strings
    char *filename = (char *)malloc(split_pos + 1);
    char *mode = (char *)malloc(size - split_pos + 1);

    if (filename == NULL || mode == NULL) {
        // Memory allocation failed
        free(filename);
        free(mode);
        return 0;
    }

    // Copy data into the filename and mode strings
    memcpy(filename, data, split_pos);
    filename[split_pos] = '\0';

    memcpy(mode, data + split_pos, size - split_pos);
    mode[size - split_pos] = '\0';

    // Call the function-under-test
    gzFile file = gzopen(filename, mode);

    // Clean up
    if (file != NULL) {
        gzclose(file);
    }

    free(filename);
    free(mode);

    return 0;
}