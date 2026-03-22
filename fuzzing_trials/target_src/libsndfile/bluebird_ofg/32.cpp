#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
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

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_close to sf_write_int
        int ret_sf_format_check_mdaem = sf_format_check(NULL);
        if (ret_sf_format_check_mdaem < 0){
        	return 0;
        }

        sf_count_t ret_sf_write_int_rjhwc = sf_write_int(sndfile, &ret_sf_format_check_mdaem, 64);
        if (ret_sf_write_int_rjhwc < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_write_int to sf_readf_double
        int ret_sf_error_wdfla = sf_error(sndfile);
        if (ret_sf_error_wdfla < 0){
        	return 0;
        }

        sf_count_t ret_sf_readf_double_vlclj = sf_readf_double(sndfile, (double *)&ret_sf_format_check_mdaem, ret_sf_write_int_rjhwc);
        if (ret_sf_readf_double_vlclj < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_readf_double to sf_open
        const char wsyfksgc[1024] = "ikxgt";

        SNDFILE* ret_sf_open_gyumy = sf_open(wsyfksgc, (int )ret_sf_readf_double_vlclj, NULL);
        if (ret_sf_open_gyumy == NULL){
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