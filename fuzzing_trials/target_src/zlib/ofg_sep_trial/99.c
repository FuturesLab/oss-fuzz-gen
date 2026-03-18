#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // Include for close() and remove()

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzz_gzfile.XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file with gzopen
    gzFile gz_file = gzopen(filename, "rb");
    if (gz_file == NULL) {
        remove(filename);
        return 0;
    }

    // Call the function-under-test
    off_t position = gztell(gz_file);

    // Close the gzFile
    gzclose(gz_file);

    // Clean up the temporary file
    remove(filename);

    return 0;
}