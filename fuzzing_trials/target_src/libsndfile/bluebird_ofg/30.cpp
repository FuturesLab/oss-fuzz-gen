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

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
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
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        // Remove the temporary file if opening fails
        remove(tmpl);
        return 0;
    }

    // Prepare buffer for reading samples
    sf_count_t frames = 1024; // Number of frames to read

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_read_raw

    sf_count_t ret_sf_read_raw_agykn = sf_read_raw(NULL, (void *)sndfile, 64);
    if (ret_sf_read_raw_agykn < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

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