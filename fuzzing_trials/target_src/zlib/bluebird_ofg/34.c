#include <stdint.h>
#include <stdlib.h>
#include "zlib.h"
#include <stdio.h>
#include "unistd.h"   // Include this for `close` and `unlink`
#include "fcntl.h"    // Include this for `mkstemp`
#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"

int LLVMFuzzerTestOneInput_34(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char filename[] = "/tmp/fuzz_gzrewind_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(filename);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the file with gzopen
    gzFile gzfile = gzopen(filename, "rb");
    if (gzfile == NULL) {
        unlink(filename);
        return 0;
    }

    // Call the function-under-test
    int result = gzrewind(gzfile);

    // Clean up
    gzclose(gzfile);
    unlink(filename);

    return 0;
}