#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    gzFile file;
    int byteToWrite;

    // Ensure that data and size are sufficient for our needs
    if (size < 2) {
        return 0;
    }

    // Open a temporary gzipped file in memory
    file = gzopen("/dev/null", "wb");
    if (file == NULL) {
        return 0;
    }

    // Use the first byte of data as the byte to write
    byteToWrite = (int)data[0];

    // Call the function-under-test
    gzputc(file, byteToWrite);

    // Close the gzFile
    gzclose(file);

    return 0;
}