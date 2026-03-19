#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sf_open
    SNDFILE *sndfile = sf_open(tmpl, size, &sfinfo);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (sndfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Prepare buffer to read samples into
    sf_count_t frames = 1024;  // Arbitrary number of frames to read
    double *buffer = (double *)malloc(frames * sfinfo.channels * sizeof(double));
    if (buffer == NULL) {
        sf_close(sndfile);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_close to sf_readf_double
        int ret_sf_format_check_rhwao = sf_format_check(&sfinfo);
        if (ret_sf_format_check_rhwao < 0){
        	return 0;
        }

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_format_check to sf_write_int
        const char* ret_sf_strerror_xywyt = sf_strerror(sndfile);
        if (ret_sf_strerror_xywyt == NULL){
        	return 0;
        }

        sf_count_t ret_sf_write_int_aaugu = sf_write_int(sndfile, &ret_sf_format_check_rhwao, 0);
        if (ret_sf_write_int_aaugu < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int ret_sf_error_czgun = sf_error(sndfile);
        if (ret_sf_error_czgun < 0){
        	return 0;
        }

        sf_count_t ret_sf_readf_double_flnnu = sf_readf_double(sndfile, (double *)&ret_sf_format_check_rhwao, (int64_t )ret_sf_error_czgun);
        if (ret_sf_readf_double_flnnu < 0){
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