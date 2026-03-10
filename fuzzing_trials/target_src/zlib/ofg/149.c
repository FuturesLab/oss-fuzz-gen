#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <string.h>

int LLVMFuzzerTestOneInput_149(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for two null-terminated strings
    if (size < 3) {
        return 0;
    }

    // Split the input data into two parts for the file name and mode
    size_t filename_len = size / 2;
    size_t mode_len = size - filename_len;

    // Allocate memory for the filename and mode strings
    char filename[filename_len + 1];
    char mode[mode_len + 1];

    // Copy data into the filename and mode, ensuring null-termination
    memcpy(filename, data, filename_len);
    filename[filename_len] = '\0';

    memcpy(mode, data + filename_len, mode_len);
    mode[mode_len] = '\0';

    // Call the function-under-test
    gzFile file = gzopen(filename, mode);

    // If gzopen returns a valid gzFile, close it
    if (file != NULL) {
        gzclose(file);
    }

    return 0;
}