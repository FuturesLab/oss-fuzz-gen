#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for close() and remove()

int LLVMFuzzerTestOneInput_100(const uint8_t *data, size_t size) {
    // Create a temporary file to write the data
    char filename[] = "/tmp/fuzz_gzfile_XXXXXX";
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

    // Open the temporary file as a gzFile
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        remove(filename);
        return 0;
    }

    // Call the function-under-test
    off_t position = gztell(gzfile);

    // Clean up
    gzclose(gzfile);
    remove(filename);

    return 0;
}