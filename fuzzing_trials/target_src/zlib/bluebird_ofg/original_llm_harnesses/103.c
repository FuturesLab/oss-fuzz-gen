#include <stdint.h>
#include <stdlib.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_103(const uint8_t *data, size_t size) {
    gzFile gz_file;
    char buffer[1024];
    int length;

    // Open a temporary gzipped file for writing
    gz_file = gzopen("temp.gz", "wb");
    if (gz_file == NULL) {
        return 0;
    }

    // Write the input data to the gzipped file
    gzwrite(gz_file, data, size);
    gzclose(gz_file);

    // Reopen the gzipped file for reading
    gz_file = gzopen("temp.gz", "rb");
    if (gz_file == NULL) {
        return 0;
    }

    // Set a fixed length for the buffer
    length = sizeof(buffer) - 1;

    // Call the function-under-test
    gzgets(gz_file, buffer, length);

    // Close the gzipped file
    gzclose(gz_file);

    return 0;
}