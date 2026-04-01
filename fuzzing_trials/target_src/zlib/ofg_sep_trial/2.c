#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    gzFile file;
    const char *filename = "/dev/null"; // Use a null device for safe writing
    unsigned int len;

    // Open the file for writing in binary mode
    file = gzopen(filename, "wb");
    if (file == NULL) {
        return 0; // Exit if file cannot be opened
    }

    // Ensure the length does not exceed the size
    len = (unsigned int)(size > UINT_MAX ? UINT_MAX : size);

    // Call the function-under-test
    gzwrite(file, (const void *)data, len);

    // Close the file
    gzclose(file);

    return 0;
}