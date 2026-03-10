#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_135(const uint8_t *data, size_t size) {
    // Ensure the size is large enough to split into two strings
    if (size < 2) {
        return 0;
    }

    // Create a buffer for the file name and mode
    char filename[256];
    char mode[10];

    // Copy data into the filename and mode, ensuring null termination
    size_t filename_len = size / 2;
    size_t mode_len = size - filename_len;

    // Limit the filename and mode lengths to their respective buffer sizes
    if (filename_len >= sizeof(filename)) {
        filename_len = sizeof(filename) - 1;
    }
    if (mode_len >= sizeof(mode)) {
        mode_len = sizeof(mode) - 1;
    }

    memcpy(filename, data, filename_len);
    filename[filename_len] = '\0';

    memcpy(mode, data + filename_len, mode_len);
    mode[mode_len] = '\0';

    // Call the function-under-test
    gzFile file = gzopen64(filename, mode);

    // If the file was successfully opened, close it
    if (file != NULL) {
        gzclose(file);
    }

    return 0;
}