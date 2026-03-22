#include "sndfile.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // Include this for close() and write()

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
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

    // Close the file descriptor to flush the data
    close(fd);

    // Open the temporary file using libsndfile
    SF_INFO sfinfo;
    SNDFILE *sndfile = sf_open(tmpl, SFM_READ, &sfinfo);
    if (sndfile == NULL) {
        return 0;
    }

    // Allocate buffer for reading samples
    sf_count_t frames = 1024; // Arbitrary number of frames for testing

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_readf_double
    int ret_sf_error_mqwei = sf_error(sndfile);
    if (ret_sf_error_mqwei < 0){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_error to sf_read_double
    int ret_sf_format_check_szmrw = sf_format_check(&sfinfo);
    if (ret_sf_format_check_szmrw < 0){
    	return 0;
    }

    sf_count_t ret_sf_read_double_alabn = sf_read_double(NULL, (double *)&ret_sf_format_check_szmrw, (int64_t )ret_sf_error_mqwei);
    if (ret_sf_read_double_alabn < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sf_error_sivto = sf_error(NULL);
    if (ret_sf_error_sivto < 0){
    	return 0;
    }

    sf_count_t ret_sf_readf_double_zqdhv = sf_readf_double(sndfile, (double *)&ret_sf_error_mqwei, (int64_t )ret_sf_error_sivto);
    if (ret_sf_readf_double_zqdhv < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int *buffer = (int *)malloc(frames * sfinfo.channels * sizeof(int));
    if (buffer == NULL) {
        sf_close(sndfile);
        return 0;
    }

    // Call the function-under-test
    sf_count_t readcount = sf_readf_int(sndfile, buffer, frames);

    // Clean up
    free(buffer);
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}