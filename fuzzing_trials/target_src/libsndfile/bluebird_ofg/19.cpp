#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
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

    // Close the file descriptor so that libsndfile can open it
    close(fd);

    // Open the temporary file with libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Prepare buffer to read samples into
    sf_count_t frames = 1024;  // Arbitrary number of frames to read
    double *buffer = (double *)malloc(frames * sfinfo.channels * sizeof(double));
    if (buffer == NULL) {
        sf_close(sndfile);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_close to sf_seek


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_close to sf_write_raw
        sf_write_sync(sndfile);

        sf_count_t ret_sf_write_raw_wyree = sf_write_raw(sndfile, (const void *)sndfile, 1);
        if (ret_sf_write_raw_wyree < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        sf_count_t ret_sf_seek_psjmn = sf_seek(sndfile, size, 0);
        if (ret_sf_seek_psjmn < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    sf_count_t read_frames = sf_readf_double(sndfile, buffer, frames);

    // Clean up
    free(buffer);
    sf_close(sndfile);
    unlink(tmpl);

    return 0;
}