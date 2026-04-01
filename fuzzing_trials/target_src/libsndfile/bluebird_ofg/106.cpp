#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> // Include for unlink, close, and write

extern "C" {
    #include "sndfile.h"
}

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    memset(&sfinfo, 0, sizeof(SF_INFO));
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Define a position and whence for sf_seek
    sf_count_t position = 0; // Start from the beginning
    int whence = SF_SEEK_SET; // Seek from the start of the file

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of sf_seek
    sf_count_t result = sf_seek(sndfile, position, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}