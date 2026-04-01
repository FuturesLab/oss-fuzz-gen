#include <sndfile.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // Include for 'write' and 'close' functions

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *data, size_t size) {
    // Create a temporary file to use with SNDFILE
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file with libsndfile in read mode
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(sfinfo));
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (!sndfile) {
        remove(tmpl);
        return 0;
    }

    // Prepare a buffer to read data into
    int int_data[10];
    
    // Attempt to read from the file
    sf_count_t result = sf_read_int(sndfile, int_data, 10);

    // Clean up
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}