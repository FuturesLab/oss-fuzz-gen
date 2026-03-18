#include <zlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for two null-terminated strings
    if (size < 3) {
        return 0;
    }

    // Allocate memory for file name and mode strings
    char filename[256];
    char mode[256];

    // Find the position of the first null character to separate filename and mode
    size_t filename_length = 0;
    while (filename_length < size && data[filename_length] != '\0') {
        filename_length++;
    }

    // Ensure there is enough data for both filename and mode
    if (filename_length >= size - 1) {
        return 0;
    }

    // Copy data into filename and mode, ensuring they are null-terminated
    if (filename_length >= sizeof(filename)) {
        return 0; // Prevent buffer overflow
    }
    memcpy(filename, data, filename_length);
    filename[filename_length] = '\0';

    size_t mode_length = 0;
    size_t mode_start = filename_length + 1;
    while (mode_start + mode_length < size && data[mode_start + mode_length] != '\0') {
        mode_length++;
    }

    // Ensure mode_length does not exceed buffer size
    if (mode_length >= sizeof(mode)) {
        return 0; // Prevent buffer overflow
    }

    // Copy mode data and ensure null termination
    memcpy(mode, data + mode_start, mode_length);
    mode[mode_length] = '\0';

    // Call the function-under-test
    gzFile file = gzopen64(filename, mode);

    // If the file was successfully opened, close it
    if (file != NULL) {
        gzclose(file);
    }

    return 0;
}