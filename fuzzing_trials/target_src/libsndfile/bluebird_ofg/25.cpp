#include "sndfile.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // Include for 'write' and 'close' functions

extern "C" {
    // Include necessary C headers, source files, functions, and code here.
}

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_open to sf_read_int
    int ret_sf_perror_glsqj = sf_perror(NULL);
    if (ret_sf_perror_glsqj < 0){
    	return 0;
    }

    sf_count_t ret_sf_read_int_iqsch = sf_read_int(sndfile, &ret_sf_perror_glsqj, 0);
    if (ret_sf_read_int_iqsch < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sf_read_int to sf_write_raw
    int ret_sf_current_byterate_mgbwm = sf_current_byterate(sndfile);
    if (ret_sf_current_byterate_mgbwm < 0){
    	return 0;
    }
    int ret_sf_error_fekls = sf_error(NULL);
    if (ret_sf_error_fekls < 0){
    	return 0;
    }

    sf_count_t ret_sf_write_raw_mwona = sf_write_raw(sndfile, (const void *)sndfile, (int64_t )ret_sf_error_fekls);
    if (ret_sf_write_raw_mwona < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    sf_count_t result = sf_read_int(sndfile, int_data, 10);

    // Clean up
    sf_close(sndfile);
    remove(tmpl);

    return 0;
}