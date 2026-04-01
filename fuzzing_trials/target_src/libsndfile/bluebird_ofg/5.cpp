#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sf_error with sf_perror
        int ret_sf_error_jtfbt = sf_perror(NULL);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        if (ret_sf_error_jtfbt < 0){
        	return 0;
        }
        int ret_sf_current_byterate_zxdjs = sf_current_byterate(sndfile);
        if (ret_sf_current_byterate_zxdjs < 0){
        	return 0;
        }

        sf_count_t ret_sf_seek_pvfys = sf_seek(sndfile, (int64_t )ret_sf_error_jtfbt, ret_sf_current_byterate_zxdjs);
        if (ret_sf_seek_pvfys < 0){
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