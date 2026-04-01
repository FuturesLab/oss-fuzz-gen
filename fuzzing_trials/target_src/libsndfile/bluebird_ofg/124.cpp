#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // Include for write, close, and other POSIX functions

extern "C" {
    // Wrap C headers and functions with extern "C"
    #include <fcntl.h>  // Include for mkstemp
}

extern "C" int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sf_open
    SNDFILE *sndfile = sf_open(tmpl, size, &sfinfo);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (sndfile == NULL) {
        // Remove the temporary file if opening fails
        remove(tmpl);
        return 0;
    }

    // Prepare buffer for reading samples
    sf_count_t frames = 1024; // Number of frames to read
    short *buffer = (short *)malloc(frames * sfinfo.channels * sizeof(short));
    if (buffer == NULL) {
        sf_close(sndfile);
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    sf_count_t read_frames = sf_readf_short(sndfile, buffer, frames);

    // Clean up
    free(buffer);
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}